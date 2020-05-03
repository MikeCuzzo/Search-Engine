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
       HashNode(K& k, string& v)
       {
            key = k;
            values.push_back(v);
            next = nullptr;
       }//end constructor

        HashNode(K& k, vector<string>& v)
        {
            key = k;
            values = v;
            next = nullptr;
        }//end constructor

    private:
        K key;
        vector<string> values;
        HashNode* next;
    };//end hashnode class

public:
    template <class U, class Y> friend class HashNode;
    HashTable()
    {
        capacity = 5000; //choose default table size
        size = 0;
        table = new HashNode<T,string>*[capacity];
        //iterate thru table, set each row to nullptr
        for(int i=0;i<capacity;i++)
            table[i] = nullptr;
    }//end constructor

    ~HashTable()
    {
        clear();
    }//end destructor

    vector<string>& getValuesForKey(T& w)
    {
        int hashKey = hashFunction(w);
        HashNode<T,string>* toCheck = table[hashKey];
        while (toCheck != nullptr)
        {
            if(toCheck->key == w)
                return toCheck->values;

            toCheck = toCheck->next;
        }//end while
    }//end getValuesForKey

    T& get(WordObject w)
    {
        int hashKey = hashFunction(w);
        HashNode<T,string>* toCheck = table[hashKey];
        while (toCheck != nullptr)
        {
            if(toCheck->key == w)
                return toCheck->key;

            toCheck = toCheck->next;
        }//end while
    }//end get

    bool contains(WordObject w)
    {
        int hashKey = hashFunction(w);
        HashNode<T,string>* toCheck = table[hashKey];
        while (toCheck != nullptr)
        {
            if (toCheck->key == w)
                return true;

            toCheck = toCheck->next;
        }//end while
        return false;
    }//end contains

    int getSize()
    {
        return size;
    }//end getSize

    void insert(WordObject w)
    {
        insert(w,w.getIDs().back());
        size++;
    }//end insert

    void insert(T& k, string& setValue)
    {
        int hashKey = hashFunction(k);
        HashNode<T,string>* toCheck = table[hashKey];
        HashNode<T,string>* prev = nullptr;
        //iterate thru table until find k
        while (toCheck != nullptr && toCheck->key != k)
        {
            prev = toCheck;
            toCheck = toCheck->next;
        }//end while

        //if reach end of table and don't find k
        if (toCheck == nullptr)
        {
            //create new node
            toCheck = new HashNode<T,string>(k, setValue);
            //if first element in table
            if (prev == nullptr)
                table[hashKey] = toCheck;
            else
                prev->next = toCheck;
        }//end if
            //if find k
        else
            {
            //add value to list of values for key
            if (toCheck->key == k)
                toCheck->values.push_back(setValue);
            else
                {
                if (toCheck->next == nullptr)
                    toCheck->next = new HashNode<T,string>(k, setValue);
                else {
                    while(toCheck->next != nullptr)
                    {
                        toCheck = toCheck->next;
                        if (toCheck->key == k)
                        {
                            toCheck->values.push_back(setValue);
                            break;
                        }//end if
                        if (toCheck->next == nullptr)
                        {
                            toCheck->next = new HashNode<T, string>(k, setValue);
                            break;
                        }//end if
                    }//end while
                }//end else
            }//end else
        }//end else
    }//end insert

    void insert(T& k, vector<string>& v)
    {
        int hashKey = hashFunction(k);
        HashNode<T,string>* toCheck = table[hashKey];
        HashNode<T,string>* prev = nullptr;
        //iterate thru table until find k
        while (toCheck != nullptr && toCheck->key != k)
        {
            prev = toCheck;
            toCheck = toCheck->next;
        }//end while
        //if reach end of table and don't find k
        if (toCheck == nullptr)
        {
            //create new node
            toCheck = new HashNode<T,string>(k, v);
            //if first element in table
            if (prev == nullptr)
                table[hashKey] = toCheck;
            else
                prev->next = toCheck;
        }//end if
            //if find k
        else
            {
            //add value to list of values for key
            if (toCheck->key == k)
                toCheck->values = v;
            else
                {
                if (toCheck->next == nullptr)
                    toCheck->next = new HashNode<T,string>(k, v);
                else
                    {
                    while (toCheck->next != nullptr)
                    {
                        toCheck = toCheck->next;
                        if (toCheck->key == k)
                        {
                            toCheck->values = v;
                            break;
                        }//end if
                        if (toCheck->next == nullptr)
                        {
                            toCheck->next = new HashNode<T,string>(k, v);
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
        HashNode<T,string>* toCheck = table[hashKey];
        HashNode<T,string>* prev = nullptr;
        //iterate thru table until find k
        while (toCheck != nullptr && toCheck->key != removeKey)
        {
            prev = toCheck;
            toCheck = toCheck->next;
        }//end while
        //if reach end of table and don't find removeKey
        if (toCheck == nullptr)
            return;
        else
            {
            //if removing first element of table
            if (prev == nullptr)
                table[hashKey] = toCheck->next;
            else
                prev->next = toCheck->next;

            delete toCheck;
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
