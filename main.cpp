#include "Rotor.hpp"
#include "Reflector.hpp"
#include "Enigma.hpp"
#include "Plugboard.hpp"
#include <iostream>
#include <cstring>
#include <string>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

std::mutex vmutex;
std::vector<EnigmaMachine*> possible_solutions;

string cipher_text_full = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

int possible_rotors[] = { 1,2,3,4,5,6,7,8 };

// From chatgpt
float calculate_ic(string str) {
    int len = str.length();
    std::vector<int> freq(26, 0);   // Frequency of each letter
    float ic = 0.0;
    
    // Calculate frequency of each letter
    for (int i = 0; i < len; i++) {
        if (isalpha(str[i])) {
            freq[toupper(str[i]) - 'A']++;
        }
    }
    
    // Calculate index of coincidence
    for (int i = 0; i < 26; i++) {
        ic += (float)freq[i] * (freq[i] - 1);
    }
    ic /= (len * (len - 1));

    return ic;
}



void compute_thread(int i, int reflector) {
  int sols = 0;
  for (int j=0; j<size(possible_rotors); j++) {
    if (i==j) continue;
    for (int k=0; k<size(possible_rotors); k++) {
      if (k==i || k==j) continue;
      int max_rot=26;
      for (int l=0; l<max_rot; l++) {
	for (int m=0; m<max_rot; m++) {
	  for (int n=0; n<max_rot; n++) {
	    int rotors[]          = { possible_rotors[i], possible_rotors[j], possible_rotors[k] };
	    int rotors_pos[]      = { 0,0,0 };//{ l,m,n };
	    int rotors_settings[] = { l,m,n };//
	    string wires[]        = { "AA" }; // at least one fake is needed. Improvement needed.
  		
	    EnigmaMachine* e = new EnigmaMachine(rotors,reflector,rotors_pos,rotors_settings,wires,size(wires));
	    e->init_with_key("ABC", "DEF");
	    string clear = e->cipher(cipher_text_full);
	    
	    float ioc = calculate_ic(clear);
	    if (ioc > 0.043) {
	      vmutex.lock();
	      e->dump_machine_single_line();
	      cout << "IOC: "<< ioc << endl << clear << endl;
	      cout << "--------------------------------------------" << endl;
	      possible_solutions.push_back(e);
	      vmutex.unlock();
	    }
	    else 
	      delete(e);
	  }
	}
      }
    }
  }
}

int main (int argc, char** argv) {
  EnigmaMachine::self_test();

  thread th[2*size(possible_rotors)];
  int z=0;
  for (int r=1; r<2; r++) {
    for (int i=0; i<size(possible_rotors); i++) {
      th[z] = std::thread (compute_thread, i, r);
      z++;
    }
  }
  
  cout << "Now joining" << endl;
  for (int join = 0; join<z; join++){
    th[join].join();
  }

  cout << "Possible solutions :" << endl;
  z=0;
  for (vector<EnigmaMachine*>::iterator i=possible_solutions.begin(); i!=possible_solutions.end(); ++i) {
    EnigmaMachine *em = *i;
    em->dump_machine_single_line();
  }  
}
