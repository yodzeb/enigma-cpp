#ifndef REF_H
#define REF_H
#include <string>
#include <iostream>

using namespace std;

class Reflector {
private:
  int forwardWiring[26];
  string name;
  int type;

  void decodeWiring(string encoding) {
    for (int i=0; i<WIRING_SIZE; i++) {
      forwardWiring[i] = encoding[i]-65;
    }
  }
  
public:
  Reflector(string _name, string _encoding, int _type) {
    decodeWiring(_encoding);
    name = _name;
    type = _type;
  }
  
  static Reflector* get_reflector(int model) {
    switch (model) {
    case 1:
      return new Reflector("B", "YRUHQSLDPXNGOKMIEBFZCWVJAT", 1); break;
    case 2:
      return new Reflector("C", "FVPJIAOYEDRZXWGCTKUQSBNMHL", 2); break;
    default:
      return new Reflector("D", "ZYXWVUTSRQPONMLKJIHGFEDCBA", 3); break;
    }
  }

  int forward(int c) {
    return forwardWiring[c];
  }

  string get_name() {
    return name;
  }

  int get_type() {
    return type;
  }

		  
};

#endif
