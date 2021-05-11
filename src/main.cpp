#include <iostream>
#include "ui.h"

using namespace std;

//argv[1] = filepath

int main(int argc, char** argv)
{
    UI ui;
    ui.run(argv[1]);
    return 0;
}///end main
