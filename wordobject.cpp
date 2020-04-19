#include "wordobject.h"

WordObject::WordObject()
{
    word = "";
    numOfIDs = 0;
}///end construcor

WordObject::WordObject(string& wordToSet)
{
    word = wordToSet;
    numOfIDs = 0;
}///end construcor

WordObject::WordObject(string& wordToSet, string& idNum)
{
    word = wordToSet;
    idNums.push_back(idNum);
    numOfIDs = 1;
    occurs.push_back(1);
}///end copy constructor

WordObject::WordObject(string& wordToSet, vector<string>& idNumsToSet)
{
    word = wordToSet;
    idNums = idNumsToSet;
    numOfIDs = idNumsToSet.size();
}///end copy constructor

void WordObject::setWord(string& wordToSet)
{
    word = wordToSet;
}///end setWord

string& WordObject::getWord()
{
    return word;
}///end getWord

void WordObject::addID(string& idNum)
{
    idNums.push_back(idNum);
    numOfIDs++;
    occurs.push_back(1);
}///end addID

vector<string>& WordObject::getIDs()
{
    return idNums;
}///end getIDs

bool WordObject::containsID(string& str)
{
    for(int i=0;i<idNums.size();i++)
    {
        if(str == idNums[i])
            return true;
    }///end for
    return false;
}///end containsID

void WordObject::incrimentOccurs(string& id)
{
    for(int i=0;i<idNums.size();i++)
    {
        if(id == idNums[i])
            occurs[i]++;
    }///end for
}///end idPos

vector<int>& WordObject::getOccurs()
{
    return occurs;
}///end getOccurs

WordObject& WordObject::operator=(const WordObject& rhs)
{
    word = rhs.word;
    numOfIDs = rhs.numOfIDs;
    idNums = rhs.idNums;
    occurs = rhs.occurs;
    return *this;
}///end = operator

bool WordObject::operator<(const WordObject& rhs) const
{
    if(word<rhs.word)
        return true;

    return false;
}///end < operator

bool WordObject::operator<(const string& rhs) const
{
    if(word < rhs)
        return true;

    return false;
}///end < operator

bool WordObject::operator>(WordObject& rhs)
{
    if(word > rhs.word)
        return true;

    return false;
}///end > operator

bool WordObject::operator>(string& rhs)
{
    if(word > rhs)
        return true;

    return false;
}///end > operator

bool WordObject::operator==(WordObject& rhs)
{
    if(word == rhs.word)
        return true;

    return false;
}///end == operator

bool WordObject::operator==(string& rhs)
{
    if(word == rhs)
        return true;

    return false;
}///end == operator

WordObject& WordObject::operator+(const WordObject& rhs)
{
    //if same word, different id numbers
    if(idNums[numOfIDs-1] != rhs.idNums[0])
    {
        idNums.push_back(rhs.idNums[0]);
        occurs.push_back(rhs.occurs[0]);
        numOfIDs++;
    }///end if
    return *this;
}///end + operator

ostream& operator<<(ostream& output, WordObject& object)
{
    output << object.word << "\n";
    for (int i = 0; i < object.numOfIDs; i++)
        output << object.idNums[i] << "\n";

    return output;
}///end ostream operator
