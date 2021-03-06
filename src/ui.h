#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include <iomanip>
#include "parser.h"
#include "QueryEngine.h"
#include "data-structures/DataStructures.h"

using namespace std;

class UI
{
public:
    void run(char* CLAPath);
    void maintenenceMode();
    void interactiveMode(string CLAPath);
    void takeQuery(DataStructures<WordObject>* x);
    char * argv;
};///end class

#endif // UI_H
