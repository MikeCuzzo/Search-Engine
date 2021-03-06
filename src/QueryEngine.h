#ifndef QUERYENGINE_H
#define QUERYENGINE_H

#include <iostream>
#include <vector>
#include <fstream>
#include "../external-libs/porter2_stemmer.h"
#include "data-structures/DataStructures.h"
#include "data-structures/AVLTree.h"
#include "data-structures/wordobject.h"

using namespace std;

class QueryEngine
{
public:
    void run(string,char*);
    void setDS(DataStructures<WordObject>*);
    void searchSingle();
    void searchAnd();
    void searchOr();
    void searchAuthor();
    void print(vector<string>);
    void printFile(string);
private:
    string origQuery;
    vector<string> notWords;
    vector<string> andWords;
    vector<string> orWords;
    string author;
    string singleWord;
    DataStructures<WordObject>* words;
    char* argv;
    fstream currFile;
    string fPath = argv;
    const string quote = "\"";

};///end class

#endif // QUERYENGINE_H
