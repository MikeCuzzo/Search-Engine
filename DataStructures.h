#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include "wordobject.h"

template<class T>
class DataStructures
{
public:
    DataStructures(){}
    DataStructures(const DataStructures<T>& rhs){}
    ~DataStructures(){}
    //    virtual const T& findMin() = 0;
    //    virtual const T& findMax() = 0;
    //    virtual bool isEmpty() = 0;
    //    virtual int getSize() = 0;
    //    virtual void writeOut() = 0;
    virtual bool contains(WordObject) = 0;
    virtual T& get(WordObject) = 0;
    virtual void insert(WordObject) = 0;
};///end class

#endif // DATASTRUCTURE_H