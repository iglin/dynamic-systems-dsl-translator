
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "SyntaxAnalyzer.h"
#include "StringUtils.h"

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
    res = syntaxAnalyzer.isOperand("  sin(+33.44 -cos(22*5 * (e - 2)) ) ", 0);
    if (res.isSuccessful()) cout << "yes" << endl;
    else cout << "no " << res.getMessage() << " at " << res.getPosition() << endl;

    string str = "   5 ^ 3   ";
    cout << StringUtils::indexOf("   5 ^ 3   ", "!") << endl;

    cout << str << endl;
    str = syntaxAnalyzer.translatePow(str);
    cout << str << endl;
   // readFile("../example.ds");
    return 0;
}