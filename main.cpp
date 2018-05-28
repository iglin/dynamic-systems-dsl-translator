
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "SyntaxAnalyzer.h"
#include "StringUtils.h"
#include "Translator.h"

using namespace std;

int main() {
    Translator().translateToCpp("../source.ds");
    return 0;
}