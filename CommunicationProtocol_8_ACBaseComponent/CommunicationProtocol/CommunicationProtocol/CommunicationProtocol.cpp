#include <iostream>
#include <bitset>
#include <string>
using namespace std;

#include <fstream>
#include "Tests.h"

int main()
{
    ofstream test_file;
    test_file.open("test_file.CSV");

    testBaseComponent(std::cout);
}