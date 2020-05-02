#ifndef WORDOBJECT_H
#define WORDOBJECT_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class WordObject
{
public:
    //CONSTRUCTORS
    WordObject();
    WordObject(string&);
    WordObject(WordObject&);
    WordObject(string&, string&);
    WordObject(string&, vector<string>&);
    //FUNCTIONS
    void setWord(string&);
    string& getWord();
    void addID(string&);
    vector<string>& getIDs();
    bool containsID(string&);
    void incrimentOccurs(string&);
    vector<int>& getOccurs();
    //OPERATORS
    WordObject& operator=(const WordObject&);
    bool operator<(const WordObject&) const;
    bool operator<(const string&) const;
    bool operator>(WordObject&);
    bool operator>(string&);
    bool operator==(WordObject&);
    bool operator==(string&);
    bool operator!=(WordObject&);
    bool operator!=(string&);
    WordObject& operator+(const WordObject&);
    friend ostream& operator<<(ostream&, WordObject&);
private:
    string word;
    vector<string> idNums;
    vector<int> occurs;
    int numOfIDs;
};///end class

#endif // WORDOBJECT_H
