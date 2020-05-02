#include "ui.h"

void UI::run(char* CLAPath)
{
    //runs ui
    bool running = true;
    while(running)
    {
        cout << "What would you like to do? \na) Maintenence Mode \n"
                "b) Interactive Mode \nc) Exit Program" << endl;
        char input;
        cin >> setw(1) >> input;
        switch(input)
        {
            case 'a':
                maintenenceMode(); break;
            case 'b':
                interactiveMode(CLAPath); break;
            case 'c':
                running = false; break;
            default:
                cout << "\nNot a valid input, please select from the menu" << endl; break;
        }///end switch
    }///end while running
    cout << "\nProgram terminated. Have a great day!" << endl;
}///end run

void UI::maintenenceMode()
{
    cout << "\nPlease enter a file path (enter '9' to cancel): " << endl;
    string usrFilePath;
    cin >> usrFilePath;
    if(usrFilePath != "9")
    {
        Parser newFiles;
        newFiles.run(usrFilePath);
        takeQuery(newFiles.getDS());
    }///end if
    else
        cout << endl;
}///end maintenenceMode

void UI::interactiveMode(string CLAPath)
{
    cout << "\nHow would you like the index stored? \na) AVLTree \nb) HashTable \nc) Cancel" << endl;
    char usrChoice;
    cin >> setw(1) >> usrChoice;
    switch(usrChoice)
    {
        case 'a':
        {
            //parse data set in the CLA
            Parser parser;
            parser.setAVL();
            parser.run(CLAPath);
            takeQuery(parser.getDS());
            break;
        }///end case a
        case 'b':
        {
            //parse data set in the CLA
            Parser parser;
            parser.setHash();
            parser.run(CLAPath);
            takeQuery(parser.getDS());
            break;
        }///end case b
        case 'c':
            cout << endl; break;
        default:
            cout << "\nNo valid choice selected" << endl; break;
    }///end switch
}///end interactiveMode

void UI::takeQuery(DataStructures<WordObject>* x)
{
    //flushes the stream
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    //loops so the files do not need to be reparsed
    while(true)
    {
        cout << "Please enter a search query (enter '@' to exit): " << endl;
        string query;
        getline(cin,query);
        //exit condition
        if(query == "@")
        {
            cout << endl;
            break;
        }///end if

        QueryEngine q;
        q.setDS(x);
        q.run(query);
    }///end while
}///end takeQuery