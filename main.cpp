#include <iostream>
#include "SyntaxAnalyzer.h"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    SyntaxAnalyzer::CheckingResult res;
    res = SyntaxAnalyzer::isIdentifier("_Asda2318asdasd213", 0);
    cout << res.result;
    return 0;
}