#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "AVLTree.h"
#include "DataStructures.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;

template<class T>
class HashTable : public DataStructures<T>
{
    //HASHNODE CLASS
    template <class K, class string>
    class HashNode
            {
    public:
        template <class U> friend class HashTable;
       HashNode(K& setKey, string& setValue)
       {
            key = setKey;
            values.push_back(setValue);
            next = nullptr;
       }//end constructor

        HashNode(K& setKey, vector<string>& setVector)
        {
            key = setKey;
            values = setVector;
            next = nullptr;
        }//end constructor

    private:
        K key;
        vector<string> values;
        HashNode* next;
    };//end hashnode class

public:
    template <class U, class Y> friend class HashNode;
    void print()
    {
        if (table == nullptr)
            cout << "Empty Table" << endl;
        else
            cout << "stuff in table" << endl;
    }//end print

    HashTable()
    {
        capacity = 5000; //choose default table size
        size = 0;
        table = new HashNode<T,string>*[capacity];
        //iterate thru table, set each row to nullptr
        for (int i = 0; i < capacity; i++)
            table[i] = nullptr;
    }//end constructor

    ~HashTable()
    {
        clear();
    }//end destructor

    vector<string>& getValuesForKey(T& w)
    {
        //make sure in lowercase
        int hashKey = hashFunction(w);
        HashNode<T,string>* checkMe = table[hashKey];
        while (checkMe != nullptr)
        {
            if(checkMe->key == w)
                return checkMe->values;

            checkMe = checkMe->next;
        }//end while
    }//end getValuesForKey

    T& get(WordObject w)
    {
        //make sure in lowercase
        int hashKey = hashFunction(w);
        HashNode<T,string>* checkMe = table[hashKey];
        while (checkMe != nullptr)
        {
            if(checkMe->key == w)
                return checkMe->key;

            checkMe = checkMe->next;
        }//end while
    }//end get

    bool contains(WordObject w)
    {
        //make sure in lowercase
        int hashKey = hashFunction(w);
        HashNode<T,string>* checkMe = table[hashKey];
        while (checkMe != nullptr)
        {
            if (checkMe->key == w)
                return true;

            checkMe = checkMe->next;
        }//end while
        return false;
    }//end contains

    void insert(WordObject w)
    {
        insert(w,w.getIDs().back());
    }//end insert

    void insert(T& setKey, string& setValue)
    {
        int hashKey = hashFunction(setKey);
//    cout << hashKey << ": " << setKey << ", " << setValue << endl;
        HashNode<T,string>* checkMe = table[hashKey];
        HashNode<T,string>* prev = nullptr;
        //iterate thru table until find setKey
        while (checkMe != nullptr && checkMe->key != setKey)
        {
            prev = checkMe;
            checkMe = checkMe->next;
        }//end while
        //if reach end of table and don't find setKey
        if (checkMe == nullptr)
        {
            //create new node
            checkMe = new HashNode<T,string>(setKey, setValue);
            //if first element in table
            if (prev == nullptr)
                table[hashKey] = checkMe;
            else
                prev->next = checkMe;
        }//end if
            //if find setKey
        else
            {
            //add value to list of values for key
            if (checkMe->key == setKey)
                checkMe->values.push_back(setValue);
            else
                {
                if (checkMe->next == nullptr)
                    checkMe->next = new HashNode<T,string>(setKey, setValue);
                else {
                    while (checkMe->next != nullptr) {
                        checkMe = checkMe->next;
                        if (checkMe->key == setKey) {
                            checkMe->values.push_back(setValue);
                            break;
                        }//end if
                        if (checkMe->next == nullptr) {
                            checkMe->next = new HashNode<T, string>(setKey, setValue);
                            break;
                        }//end if
                    }//end while
                }//end else
            }//end else
        }//end else
    }//end insert

    void insert(T& setKey, vector<string>& setVector)
    {
        int hashKey = hashFunction(setKey);
        HashNode<T,string>* checkMe = table[hashKey];
        HashNode<T,string>* prev = nullptr;
        //iterate thru table until find setKey
        while (checkMe != nullptr && checkMe->key != setKey)
        {
            prev = checkMe;
            checkMe = checkMe->next;
        }//end while
        //if reach end of table and don't find setKey
        if (checkMe == nullptr)
        {
            //create new node
            checkMe = new HashNode<T,string>(setKey, setVector);
            //if first element in table
            if (prev == nullptr)
                table[hashKey] = checkMe;
            else
                prev->next = checkMe;
        }//end if
            //if find setKey
        else
            {
            //add value to list of values for key
            if (checkMe->key == setKey)
                checkMe->values = setVector;
            else
                {
                if (checkMe->next == nullptr)
                    checkMe->next = new HashNode<T,string>(setKey, setVector);
                else
                    {
                    while (checkMe->next != nullptr)
                    {
                        checkMe = checkMe->next;
                        if (checkMe->key == setKey)
                        {
                            checkMe->values = setVector;
                            break;
                        }//end if
                        if (checkMe->next == nullptr)
                        {
                            checkMe->next = new HashNode<T,string>(setKey, setVector);
                            break;
                        }//end if
                    }//end while
                }//end else
            }//end else
        }//end else
    }//end insert

    void removeKey(T& removeKey)
    {
        int hashKey = hashFunction(removeKey);
        HashNode<T,string>* checkMe = table[hashKey];
        HashNode<T,string>* prev = nullptr;
        //iterate thru table until find setKey
        while (checkMe != nullptr && checkMe->key != removeKey)
        {
            prev = checkMe;
            checkMe = checkMe->next;
        }//end while
        //if reach end of table and don't find removeKey
        if (checkMe == nullptr)
            return;
        else
            {
            //if removing first element of table
            if (prev == nullptr)
                table[hashKey] = checkMe->next;
            else
                prev->next = checkMe->next;

            delete checkMe;
        }//end else
    }//end remove key

    void clear()
    {
        if(table != nullptr)
        {
            //iterate thru table, delete elements
            for (int i = 0; i < capacity; i++)
            {
                if (table[i] != nullptr)
                {
                    if (table[i]->next == nullptr)
                        delete table[i];
                    else
                        {
                        HashNode<T,string>* temp = table[i];
                        HashNode<T,string>* prev = table[i];
                        while (temp->next != nullptr)
                        {
                            temp = temp->next;
                            delete prev;
                            prev = temp;
                        }//end while
                        delete temp;
                    }//end else
                    table[i] = nullptr;
                }//end if
            }//end for
        }//end if
    }//end clear

    void saveTable(ofstream& outputFile)
    {
        //Format:
        //word
        //id
        //NEW_ELEMENT
        //word
        //id
        for (int i = 0; i < capacity; i++) {
            HashNode<T,string>* temp = table[i];
            while (temp != nullptr) {
                outputFile << temp->key << "\n";
                int tempSize = temp->values.size();
                for (int j = 0; j < tempSize; j++) {
                    outputFile << temp->values[j] << "\n";
                }
                temp = temp->next;
                outputFile << "NEW_ELEMENT\n";
            }
        }
    }

    vector<string>& operator[](T& index)
    {
        int hashKey = hashFunction(index);
        if (table[hashKey] != nullptr)
        {
            if (table[hashKey]->key == index)
                return table[hashKey]->values;
            else {
                HashNode<T,string>* temp = table[hashKey];
                while (temp->next != nullptr)
                {
                    if (temp->key == index)
                        return temp->values;
                    temp = temp->next;
                }//end while
                //if matches no specific keys just return first value in list
                return table[hashKey]->values;
            }//end else
        }//end if
    }//end operator[]

private:
//hashfuntion to deal w string keys
    int hashFunction(WordObject& keyword)
    {
        int sum = 0;
        int length = keyword.getWord().length();
        for (int i = 0; i < length; i++)
            sum += int(keyword.getWord()[i]);

        if (sum > capacity)
            sum %= capacity;

        return sum;
    }//end hashfunction

    int hashFunction(int& keyNum)
    {
        return keyNum % capacity;
    }//end hashfunction


    HashNode<T,string>** table;
    int capacity;
    int size;
};//end hashtable class

#endif // HASHTABLE_H
