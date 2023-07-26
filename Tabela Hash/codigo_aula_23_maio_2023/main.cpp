#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <iomanip>
#include "Codification.h"
#include "HashTable.h"
using namespace std;

int main() 
{
    HashTable<std::string, unsigned long int> ht (2, 1.0, 2.0, code_std_string);

    ht.add("atilio", 13);

    ht["atilio"] = 13131313;

    cout << fixed << ht.at("atilio") << endl;


}
