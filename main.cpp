
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "SyntaxAnalyzer.h"

using namespace std;

int readFile(const string &fileName) {
    ifstream file(fileName);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            cout << line << endl;
            //istringstream iss(line);
            //int a, b;
            //if (!(iss >> a >> b)) { break; } // error
        }
        file.close();
    } else {
        string errorMessage;
        errorMessage = "Could not read source file " + fileName;
        throw runtime_error(errorMessage);
    }
}

int main() {
    CheckingResult res;
    SyntaxAnalyzer syntaxAnalyzer;
    res = syntaxAnalyzer.isIdentifier("dx", 0);
    if (res.isSuccessful()) cout << "yes";
    else cout << "no " << res.getMessage() << " at " << res.getPosition() << endl;

    double x = -5*+-2;
    cout <<x ;
   // readFile("../example.ds");
    return 0;
}