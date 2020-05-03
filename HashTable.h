#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "AVLTree.h"
#include "DataStructures.h"
#include <functional>
#include <vector>

using namespace std;

template<class T>
class HashTable : public DataStructures<T>
{
    //HASHNODE CLASS
    template <typename K, typename V>
    class HashNode
            {
    public:
        HashNode() {}///end constructor

        HashNode(const K &key, const V &value)
        {
            keys.push_back(key);
            keys.push_back(value);
        }//end copy constructor

        ~HashNode() {}///end destructor

        V& getValue(K key)
        {
            for(int i=0;i<keys.size();i++)
            {
                if(keys[i] == key)
                    return values[i];
            }//end for
            throw underflow_error("not in here");
        }//end getValue

        vector<V>& getValues()
        {
            return values;
        }//end getValues

        vector<K>& getKeys()
        {
            return keys;
        }//end getKeys

        K& getKey(K key)
        {
            for(int i=0;i<keys.size();i++)
            {
                if(keys[i] == key)
                    return keys[i];
            }//end for
            throw underflow_error("not in here");
        }//end getValue

        int getSize()
        {
            return keys.size();
        }//end getSize

        bool addValue(K key, V value)
        {
            if(keys.size()>=4)
                return false;

            keys.push_back(key);
            values.push_back(value);
            return true;
        }//end addValue

        bool room()
        {
            return keys.size()<4;
        }//end room

        bool contains(K key)
        {
            for(int i=0;i<keys.size();i++)
            {
                if(keys[i] == key)
                    return true;
            }//end for
            return false;
        }//end contains

    private:
        // key-value pair
        vector<K> keys;
        vector<V> values;
    };//end HashNode class

private:
    HashNode<T,string>* data;
    int currSize;
    int capacity;
public:
    HashTable()
    {
        data = new HashNode<T,string>[10000];
        capacity = 10000;
        currSize = 0;
        for(int i = 0; i<capacity; i++)
            data[i] = HashNode<T,string>();
    }//end constructor

    HashTable(const HashTable<T>& rhs);

    HashTable(int numElements)
    {
        data = new HashNode<T,string>[numElements];
        capacity = numElements;
        currSize = 0;
        for(int i = 0; i<capacity; i++)
            data[i] = HashNode<T,string>();
    }//end copy constructor

    ~HashTable()
    {
        delete[] data;
    }//end destructor

    void insert(WordObject w)
    {
        add(w,w.getIDs().back());
    }//end insert

    void add(WordObject key, string id)
    {
        int hash = std::hash<string>().operator()(key.getWord());
        int spot = hash%capacity;
        if(!data[spot].room())
            resize();
        data[spot].addValue(key,id);
        currSize++;
    }//end add

    T& get(WordObject key)
    {
        int hash = std::hash<string>().operator()(key.getWord());
        int spot = hash%capacity;
        if(data[spot].contains(key))
            return data[spot].getKey(key);

        throw std::underflow_error("not in table");
    }//end get

    T& operator[](WordObject key)
    {
        return get(key);
    }//end operator[]

    bool contains(WordObject key)
    {
        int hash = std::hash<string>().operator()(key.getWord());
        int spot = hash%capacity;
        return(data[spot].contains(key));
    }//end contains

    void resize()
    {
        int newCap = capacity*4;
        HashNode<T,string>* newDat = new HashNode<T,string>[newCap];
        for(int i=0;i<newCap;i++)
            newDat[i] = HashNode<T,string>();

        for(int i = 0; i < capacity; i++)
        {
            vector<string> vals = data[i].getValues();
            vector<T> keys = data[i].getKeys();
            for(int j=0;j<data[i].getSize();j++)
            {
                int hash = std::hash<string>().operator()(keys[j].getWord());
                int spot = hash%newCap;
                if(!newDat[spot].room())
                    resize();
                data[spot].addValue(keys[i],vals[i]);
            }//end for
        }//end for

        delete[] data;
        data = newDat;
        capacity = newCap;
    }//end resize
};//end class

#endif // HASHTABLE_H
