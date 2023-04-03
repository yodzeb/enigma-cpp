#ifndef PLUG_H
#define PLUG_H

#include <string>
#include <iostream>

using namespace std;

class Plugboard {
private:
  int wiring[26];
  string alphabet   = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  void decode_wiring(string* wires, int nb) {
    for (int i=0; i<26; i++) {
      wiring[i] = i;
    }
    for (int i=0; i<nb; i++) {
      int src = (int)wires[i][0] - 65;
      int dst = (int)wires[i][1] - 65;
      //cout << src << endl;

      if (wiring[src] != (alphabet[src] - 65) ||
	  wiring[dst] != (alphabet[dst] - 65)) {
	//cout << "Already wired !" << wires[i] << "---" <<  endl;
	//exit(-1);
      }
      else {
	wiring[src] = dst;
	wiring[dst] = src;
      }
    }
  }
  
public:
  Plugboard(string wires[], int nb) {
    decode_wiring(wires, nb);
  }

  int forward(int c) {
    return wiring[c];
  }

};

#endif
