#ifndef ROTOR_H
#define ROTOR_H

#define WIRING_SIZE 26
#include <string>
#include <iostream>

using namespace std;


class Rotor {
private:
  string name;
  int forwardWiring[WIRING_SIZE];
  int backwardWiring[WIRING_SIZE];
  int rotorPosition;
  int notchPosition;
  int notchPosition2;
  int ringSetting;
  int initialPosition;

  void decodeWiring(string encoding) {
    for (int i=0; i<WIRING_SIZE; i++) {
      forwardWiring[i] = encoding[i]-65;
      backwardWiring[encoding[i]-65] = i;
    }
  }
  
public:
  static Rotor* get_rotor(int model, int _rotorPosition, int _ringSetting) {
    switch(model) {
    case 1:
      return new Rotor ("I",  "EKMFLGDQVZNTOWYHXUSPAIBRCJ", _rotorPosition, _ringSetting, 16, -10); break;
    case 2:
      return new Rotor ("II", "AJDKSIRUXBLHWTMCQGZNPYFVOE", _rotorPosition, _ringSetting, 4,  -10); break;
    case 3:
      return new Rotor ("III","BDFHJLCPRTXVZNYEIWGAKMUSQO", _rotorPosition, _ringSetting, 21, -10); break;
    case 4:
      return new Rotor ("IV", "ESOVPZJAYQUIRHXLNFTGKDCMWB", _rotorPosition, _ringSetting, 9, -10); break;
    case 5:
      return new Rotor ("V" , "VZBRGITYUPSDNHLXAWMJQOFECK", _rotorPosition, _ringSetting, 25, -10); break;
    case 6:
      return new Rotor ("VI", "JPGVOUMFYQBENHZRDKASXLICTW", _rotorPosition, _ringSetting, 12, 25 ); break;
    case 7:
      return new Rotor ("VII","NZJHGRCXMYSWBOUFAIVLPEKQDT", _rotorPosition, _ringSetting, 12, 25); break;
    case 8:
      return new Rotor("VIII","FKQHTLXOCBJSPDZRAMEWNIUYGV", _rotorPosition, _ringSetting, 12, 25); break;
    default:
      return new Rotor ("O",  "ABCDEFGHIJKLMNOPQRSTUVWXYZ", _rotorPosition, _ringSetting, 16, -10); break;
    }
    return new Rotor   ("O",  "ABCDEFGHIJKLMNOPQRSTUVWXYZ", _rotorPosition, _ringSetting, 16, -10); 
  }

  static Rotor* get_rotor(string model, int _rotorPosition, int _ringSetting) {
    if (model == "I") 
      return Rotor::get_rotor (1, _rotorPosition, _ringSetting);
    else if (model=="II")
      return Rotor::get_rotor (2, _rotorPosition, _ringSetting);
    else if (model=="III")
      return Rotor::get_rotor (3, _rotorPosition, _ringSetting);
    else if (model=="IV")
      return Rotor::get_rotor (4, _rotorPosition, _ringSetting);
    else if (model=="V")
      return Rotor::get_rotor (5, _rotorPosition, _ringSetting);
    else if (model=="VI")
      return Rotor::get_rotor (6, _rotorPosition, _ringSetting);
    else if (model=="VII")
      return Rotor::get_rotor (7, _rotorPosition, _ringSetting);
    else if (model=="VIII")
      return Rotor::get_rotor (8, _rotorPosition, _ringSetting);
    else
      return Rotor::get_rotor ("ZZ", _rotorPosition, _ringSetting);
  }
  
  Rotor(string _name, string encoding, int _rotorposition, int _ringsettings, int _notchposition, int _notchposition2) {
    notchPosition = _notchposition;
    notchPosition2 = _notchposition2;
    decodeWiring(encoding);
    ringSetting = _ringsettings;
    rotorPosition = _rotorposition;
    initialPosition = _rotorposition;
    name = _name;
  }

  int encipher(int k, int pos, int ring, int* mapping ) {
    int shift = pos - ring;
    return (mapping[(k + shift + 26) % 26] - shift + 26) % 26;
  }

  int forward(int k) {
    return encipher(k, rotorPosition, ringSetting, forwardWiring);
  }

  void set_position(int p) {
    rotorPosition = p;
  }
  
  void dump_wiring() {
    for (int i=0; i<26; i++) {
      cout << forwardWiring[i] << " ";
    }
    cout << endl;
  }

  int backward(int k) {
    return encipher(k, rotorPosition, ringSetting, backwardWiring);
  }

  bool is_at_notch() {
    return (rotorPosition == notchPosition || rotorPosition == notchPosition2);
  }

  string get_name() {
    return name;
  }
  
  void turn_over() {
    rotorPosition = (rotorPosition+1)%26;
  }
  
  int getPosition() {
    return rotorPosition;
  }

  int get_initial() {
    return initialPosition;
  }

  int get_settings() {
    return ringSetting;
  }

  int * getFwd() {
    return forwardWiring;
  }

  int * getBwd() {
    return backwardWiring;
  }
};
  
#endif
