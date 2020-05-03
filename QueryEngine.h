#ifndef QUERYENGINE_H
#define QUERYENGINE_H

#include <iostream>
#include <vector>
#include <fstream>
#include "porter2_stemmer.h"
#include "DataStructures.h"
#include "AVLTree.h"
#include "wordobject.h"

using namespace std;

class QueryEngine
{
public:
    void run(string query,char* CLAPath);
    void setDS(DataStructures<WordObject>* x);
    void searchSingle();
    void searchAnd();
    void searchOr();
    void searchAuthor();
    void print(vector<string> toPrint);
    int printFile(string file);
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
