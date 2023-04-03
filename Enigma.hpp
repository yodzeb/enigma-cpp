#ifndef ENIG_H
#define ENIG_H

#include <string>
#include <iostream>
#include "Rotor.hpp"
#include "Reflector.hpp"
#include "Plugboard.hpp"

using namespace std;

class EnigmaMachine {
private:
  Rotor* left;
  Rotor* middle;
  Rotor* right;
  Reflector* reflector;
  Plugboard* plugboard;
  string * original_plugboard;
  int original_plugboard_size;
  
  void rotate() {
    if (middle->is_at_notch() ) {
      middle->turn_over();
      left->turn_over();
    }

    else if (right->is_at_notch()) {
      middle->turn_over();
    }

    right->turn_over();
  }

public:
  EnigmaMachine(int _rotors[], int _reflector, int _rotors_positions[], int _ring_settings[], string _plugboard[], int _pb_size){
    left   = Rotor::get_rotor(_rotors[0], _rotors_positions[0], _ring_settings[0]);
    middle = Rotor::get_rotor(_rotors[1], _rotors_positions[1], _ring_settings[1]);
    right  = Rotor::get_rotor(_rotors[2], _rotors_positions[2], _ring_settings[2]);
    reflector = Reflector::get_reflector(_reflector);
    plugboard = new Plugboard(_plugboard, _pb_size);
    original_plugboard = _plugboard;
    original_plugboard_size = _pb_size;
  }

  EnigmaMachine(string _rotors[], int _reflector, int _rotors_positions[], int _ring_settings[], string _plugboard[], int _pb_size){
    left   = Rotor::get_rotor(_rotors[0], _rotors_positions[0], _ring_settings[0]);
    middle = Rotor::get_rotor(_rotors[1], _rotors_positions[1], _ring_settings[1]);
    right  = Rotor::get_rotor(_rotors[2], _rotors_positions[2], _ring_settings[2]);
    reflector = Reflector::get_reflector(_reflector);
    plugboard = new Plugboard(_plugboard, _pb_size);
    original_plugboard = _plugboard;
  }

  
  ~EnigmaMachine() {
    delete(right);
    delete(middle);
    delete(left);
    delete(reflector);
    delete(plugboard);
  }

  static bool self_test() {
    string text="THEENIGMAMACHINEISACIPHERDEVICEDEVELOPEDANDUSEDINTHEEARLYTOMIDTHCENTURYTOPROTECTCOMMERCIALDIPLOMATICANDMILITARYCOMMUNICATIONITWASEMPLOYEDEXTENSIVELYBYNAZIGERMANYDURINGWORLDWARIIINALLBRANCHESOFTHEGERMANMILITARYTHEENIGMAMACHINEWASCONSIDEREDSOSECURETHATITWASUSEDTOENCIPHERTHEMOSTTOPSECRETMESSAGESTHEENIGMAHASANELECTROMECHANICALROTORMECHANISMTHATSCRAMBLESTHELETTERSOFTHEALPHABETINTYPICALUSEONEPERSONENTERSTEXTONTHEENIGMASKEYBOARDANDANOTHERPERSONWRITESDOWNWHICHOFTHELIGHTSABOVETHEKEYBOARDILLUMINATEDATEACHKEYPRESSIFPLAINTEXTISENTEREDTHEILLUMINATEDLETTERSARETHECIPHERTEXTENTERINGCIPHERTEXTTRANSFORMSITBACKINTOREADABLEPLAINTEXTTHEROTORMECHANISMCHANGESTHEELECTRICALCONNECTIONSBETWEENTHEKEYSANDTHELIGHTSWITHEACHKEYPRESSTHESECURITYOFTHESYSTEMDEPENDSONMACHINESETTINGSTHATWEREGENERALLYCHANGEDDAILYBASEDONSECRETKEYLISTSDISTRIBUTEDINADVANCEANDONOTHERSETTINGSTHATWERECHANGEDFOREACHMESSAGETHERECEIVINGSTATIONWOULDHAVETOKNOWANDUSETHEEXACTSETTINGSEMPLOYEDBYTHETRANSMITTINGSTATIONTOSUCCESSFULLYDECRYPTAMESSAGEWHILENAZIGERMANYINTRODUCEDASERIESOFIMPROVEMENTSTOTHEENIGMAOVERTHEYEARSANDTHESEHAMPEREDDECRYPTIONEFFORTSTHEYDIDNOTPREVENTPOLANDFROMCRACKINGTHEMACHINEASEARLYASDECEMBERANDREADINGMESSAGESPRIORTOANDINTOTHEWARPOLANDSSHARINGOFHERACHIEVEMENTSENABLEDTHEWESTERNALLIESTOEXPLOITENIGMANCIPHEREDMESSAGESASAMAJORSOURCEOFINTELLIGENCEMANYCOMMENTATORSSAYTHEFLOWOFULTRACOMMUNICATIONSINTELLIGENCEFROMTHEDECRYPTINGOFENIGMALORENZANDOTHERCIPHERSSHORTENEDTHEWARSUBSTANTIALLYANDMAYEVENHAVEALTEREDITSOUTCOME";
    
    string expected_ciphered1 = "OZXYTOOOTKZUZBSSGVSDZSEGXRUSQKIBRUWFUGQWMIRBYLSYQIUDPPUDGBFQRNFFGXZUQZAYYOEQSDQDNXNSAWKAYPMWDUMKJYMRMJGKAZXSEGIPZETZZWXTHAGFABRZLWAXNVCCMDSKYEAYPZWLIFGFERRQOFWEZCKWJUWOHUQQHKAZRNHUORZWJQISBCSWHBFXOENBMUQGBBMEWWYRWAAVBEABAPHLZSIQAXDXTAOMOHCQDJVAPBIFOWBVRFZVGJSHDWMPZMXUYUWVWAXEQRZAPLOACWSXBMHGELTXQUSFNTEMHCDGXKWULRVVETXGCEVOXFQJJFIUPYILVVORBGBJYIJDVAJMJYCHGJUOZHQQGJMXJGSQBZYMJQOSGQOACPWKQOKCXVMLKBDWJGKUGCTUBDLBRBASZNYXDKIHVHXEBQTCGKYYAHETJRWGSXXVJMRATBIMZMZFIFZCKDYNINRIQCWFWRRSIXJNQNKKAHEKCNEOFNRGQSTUHRTDJCKUQCOWHMODMKJOGVRVKCCMDAFAJSMQRQCZHXKKHEYTLWGSVKBZWLMBCZQYQKGQKQTEWTVMGEYDSIQFCSTRAJOPRZNHIRHNYMSNCAIOCYLVZGUPYQWOVNXIIRROIBYASXKLLMRHXXLZBVDUKMLIZNGTGLJHEVIANUKFJLZABSCTHTLTGSRBCJATNWZTEQKUIGQVSBHLKLIXAAMXSHKNRNKSOHHZGAZRTWQGGNZGUHCMIERGGHNOUKNNVYYJILUITCDFYCIGIDUQLDQFSMNSUIVKDJVANQNIZDMXCXTWNVMSXAEPIEDZPWFFXBETMDRFLVRRAOWZXDWGFHAVYTRIBZXAESYTEAUSFDKXWDZGWONYCFJPHTXNRXJXPXLLEPKCYTRRRTMQZXDDMPJDDCEYVETGTSUQODVYPOKOBQENRQPLXSXQJIFBMBJIEOABXTLLIFMCCJURTRWRDBDCYWTIJUFFZVLLOHHRSNSAAZHJOGLEPAFXYPNIXKJSPXPCYHONDTTJYRYDWZMYPZIVQCIRTNSKBFDDEOBNKNLIVDBRULIIBDKHTUZHXMLEBNRNNOGTWZLJGPWHEHWGMWCZVDCJXLEJFXATVSEYPXTWOUVPZWTIIOQFEIBBWFZJSTZOSIEUVDDKPSFSGJIUGMFWQDAAFVLGPUHRHHVUFVEWWQGDMKRIIRZREVZOJFSGCMMQEWUVFDRSASGOPHMDITZACXJYDWPXGPRTDNGJDPRLFRYHJLPANPSSRSYZQUDRFVBTYVFRXZVSZKUJCSQOYDWJHPYMFDDFZKOUOYIUJUEWPJFKSYRSNMFISBPXUYIZSPLSJEIOATWLIPNJQCOWXJVFDWUCNYPGLZSQDCUWMULOIXLUFJJIOFOJULNMBHVOKVXNWPNLWFEDYLOTWQDYEZWTOUMKNSWXAMOUDXLNFSKNBLVJITCXAINOCBUKCTIJTDDKPRIHPJD";

    string expected_ciphered2 = "VMFLIMEZZHOMULDGPUEXAVVRLSRNOBIZYAHBSTBXOOFWOMKAVVLZTBVUXOGIQVAZYOIXMEIEBLWQRTQNNEQCVUSARJPLGXHIDYKFZIIZGERODBKPXINFRHSQLFZZCULNOAIEKLQJUKWKXAAKHIADSRCDHWRALSKTVSCLFHRCZBUYRWNSXDYKCQKOIMLCSBPEJNMIMCQBLZXAUIFJRVVXHKEXIVZHHEOTDNBPIAILDQAZBGBHUQNBKLJJMQRZRLUQMLUUSOVXFFNIUELSUFDKBKEIKTAUBSVBNWDGLMWTYDJZUJZMFLKLOANUHJEGFWRHCBEZAJGFPWSMKTGGFJSJYHLMGXFZANKSNVTXOIGIHDENOWFZCSMAZYPGUZSYZFKBFUPGRQRFFFPIAFUGVLZSKWPRKJVLQQXMEYSRJLMBHJIXDXBDYIQBZHTKSQXVSUWBUNZZJSKQXUWNBWMAJXJMDVKHUYSUFCHNOMTOICKXKRTFSYPIQNXTLJGWHRIWPGLCNZSQYCDMYFMCCZFFBBCGTBSTYHNWKYJLXYINEQQOHNIHTJDXQUROOTIMKKDAMWKOTCGMUPBCILUZRUDFNXQIMWUTFOSAUFBESJKHUIMPNATXFYLTGBKJXZJZQBZCIKMPQHBRANAAHJNADKDEULRMQLQEPESLFFRAMRRNUGBDTQUPGQSHFZCNRCXLSKHHMAIJAXJXIPHBGUIYGFYNIHIRSSPITBZXYNRUVLPYSXQUOCXRGOLCRIWCZQJPUKEOZTGPDPUSKXSPQAMZFSNTQCZVWYDZHTIVWKGKDJOAGYRCMNDBNCQBACARLYGVTYOYNYXBNWGKHAUYXAYQEWGJFTHOOEERQZFWEYUDIMUTLQLZRVGSPSGVQMYRABZFYBIRBJGUYOKXBOWCPPJUFTOAXLCOOMBUQMLBCZZZBIGFTILVIPQNWIVESSLEWIHOTMCXWJTIDPYJDXMYYHMZPWHLBDJECXWQIPJJHJKUVFJOCSWKWUFDDNQCZYJMVSNGWKIUENWRVUBKPPGTBHLYNHMJRSUXLPCBENWBPPGIMOTXVEOLLBMQTTDEGWILVIYZZFIQGCYVSZXPEZKQFLNFMMRCXVUKCCOSVCHMNWLSENBZRUSBJGBPNQALZBFYIHZNXKTMWYPJZKFPVIYAXAQXNLWBRNSGXQTYLQMNYKNXXNGNKKGBOCNTDKIANIHMXJIUHEMCVKBDFRYTXDPKJVZOCQUBZWKZNOXILIXNQIZOJHCJZQZUSGBNGYIJFHFNBQGNVGUJHBECZDYNHQZZSFNEMSTDYPIRZNNFZFGZLUDTAIXXBLIIZHFMZOKLFZIKNJOREIJXLXEBVBWWXQVNDACMCSVSLEQEYOBHNASZNVHUYFXUELCWBDEKPSFCAUQVQOYBQQFFLZTYQNSCGUPQRUAIQIKSTVTQSYEDBSCQRCDHEAUHHRNASXITWQGBZPNAXZBYTQERCLL";

    int rotors[]          = { 1, 2, 3 };
    int rotors_settings[] = { 5,10,15 };
    int pos[]             = { 0, 0, 0 };
    int reflector         = 1;
    string plugboard[]    = {"JU","NK","FO","DS"};
    EnigmaMachine * e = new EnigmaMachine(rotors, reflector, pos, rotors_settings, plugboard, size(plugboard) );
    e->init_with_key("ABC","DEF");
    string cipher1 = e->cipher(text);

    int rotors2[]          = { 4 , 5 ,6 };
    int rotors2_settings[] = { 12, 25, 6 };
    int pos2[]             = { 0, 0, 0 };
    int reflector2         = 2;
    string plugboard2[]    = {"DE","AB","OY","ZK"};

    EnigmaMachine * e2 = new EnigmaMachine(rotors2, reflector2, pos2, rotors2_settings, plugboard2, size(plugboard2) );
    e2->init_with_key("ZTU","PRK");
    string cipher2 = e2->cipher(text);
    if (cipher1 == expected_ciphered1 && cipher2==expected_ciphered2){
      cout << "[+] Machine seems to be valid" << endl;
      return true;
    }
    else 
      cout << "[!] Machine is invalid !!!!!!" << endl;
    return false;
  }

  void set_position(int l, int m, int r) {
    left->set_position(l-65);
    middle->set_position(m-65);
    right->set_position(r-65);
  }

  void set_position(string pos) {
    set_position(pos[0],pos[1],pos[2]);
  }

  void init_with_key(string pos, string key) {
    set_position(pos);
    key = cipher(key);
    //cout << "Key: " << key << endl;
    set_position(key);      
  }
  
  string cipher(string clear_text) {
    string cipher_text = "";
    for (int i = 0; i<clear_text.length(); i++) {
      int c = (int) clear_text[i];
      cipher_text += char(cipher_turn(c-65)+65) ;
    }
    //cout << cipher_text;
    return cipher_text;
  }

  void dump_machine() {
    cout << "ROTOR-L: " << left->get_name() << " -- \t"; left->dump_wiring() ;
    cout << "ROTOR-M: " << middle->get_name() << " -- \t"; middle->dump_wiring();
    cout << "ROTOR-R: " << right->get_name() << " --\t"; right->dump_wiring();
    cout << "REFLECTOR: "<< reflector->get_name() << endl;
  }

  void dump_machine_single_line() {
    cout << "Pos: [" << left->get_name()     << "," << middle->get_name()     << "," << right->get_name() << "] ";
    cout << "Ref: [" << reflector->get_name() << "] ";
    cout << "Set: [" << left->get_settings() << "," << middle->get_settings() << "," << right->get_settings() << "] ";
    cout << "Ini: [" << left->get_initial() << "," << middle->get_initial() << "," << right->get_initial() << "] ";
    cout << "PB:  [";
    for (int i=0; i<original_plugboard_size; i++)
      cout << original_plugboard[i] << ", ";
    cout << " ] " << endl;
  }

  int get_reflector_type() {
    return reflector->get_type();
  }
  
  string * get_rotors() {
    string * rnames = new string[3];
    rnames[0] = left->get_name();
    rnames[1] = middle->get_name();
    rnames[2] = right->get_name() ;
    return rnames;
  }

  int * get_rotors_settings() {
    int * rset = new int[3];
    rset[0] = left->get_settings();
    rset[1] = middle->get_settings();
    rset[2] = right->get_settings() ;
    return rset;
  }
  
  int cipher_turn(int c) {
    rotate();
    c = plugboard->forward(c);
    c = right->forward(c);
    c = middle->forward(c);
    c = left->forward(c);

    c = reflector->forward(c);

    c = left->backward(c);
    c = middle->backward(c);
    c = right->backward(c);
    c = plugboard->forward(c);

    return c;
  }


  
};


#endif
