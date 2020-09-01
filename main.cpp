#include <iostream>
#include <fstream>
#include "interpreter.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Please provide an input file." << endl;
        return 1;
    }
    map<int, Command*> prog;
    ifstream input(argv[1]);
    Interpreter interpreter(input, prog);
   map<int, Command*>::iterator it = prog.begin();
   int check= 0;
    while(check != -1){
    try {
        check = interpreter.execute(it, prog);
    }
    catch(exception &e){
        cout << "Error in line " << to_string(it->first) << e.what() << "." << endl;
        break;
    }
    }

    map<int, Command*>::iterator dealloc;
    for(dealloc = prog.begin(); dealloc != prog.end(); dealloc++)
        delete dealloc->second;
    
    interpreter.write(cout);
    return 0;
}
