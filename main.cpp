
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "SyntaxAnalyzer.h"
#include "StringUtils.h"
#include "Translator.h"

using namespace std;

int main() {
    CheckingResult res;
    SyntaxAnalyzer syntaxAnalyzer;
    res = syntaxAnalyzer.isFirstDerivativeX("  2 * (sin(x) + x^2 + (2 - 4 *x)) ", 0);
    if (res.isSuccessful()) cout << "yes" << endl;
    else cout << "no " << res.getMessage() << " at " << res.getPosition() << endl;

    Translator().translateToCpp("../example.ds");

    string str = "   waaat ";
    cout << str << endl;
    StringUtils::trim(str);
    cout << str << endl;
    return 0;
}