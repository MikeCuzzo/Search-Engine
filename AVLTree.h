#ifndef AVLTREE_H
#define AVLTREE_H

#include "DataStructures.h"
#include <stdexcept>
#include <fstream>
#include "HashTable.h"
#include "wordobject.h"

using namespace std;

template <class T>
class AVLTree : public DataStructures<T>
{
private:
    //private class for the nodes of the AVLTree
    template<class U>
    class AVLNode
    {
        friend class AVLTree<U>;
        U data;
        AVLNode* left;
        AVLNode* right;
        int height;

        AVLNode(U& element, AVLNode* L, AVLNode* R, int h = 0)
        {
            data = element;
            left = L;
            right = R;
            height = h;
        }///end construcor
    };///end AVLNode class

    AVLNode<T>* root;
    int size;

    //returns the height of a node, returns 0 for any leaf
    int getHeight(AVLNode<T>* node)
    {
        if(node == nullptr){
            return -1;
        } else {
            return node->height;
        }///end else
    }///end getHeight

    // returns the larger of the two numbers
    int max(int lhs,int rhs)
    {
        if(lhs<rhs){
            return rhs;
        } else {
            return lhs;
        }///end else
    }///end max

    //private recursive insert
    void insert(T& toAdd, AVLNode<T>*& node)
    {
        if(node == nullptr)
            node = new AVLNode<T>(toAdd, nullptr, nullptr);

        else if(node->data > toAdd)
        {
            insert(toAdd, node->left);
            if(getHeight(node->left)-getHeight(node->right) == 2)
            {
                if(node->left->data > toAdd){
                    //case 1 rotation
                    rotateWithLeftChild(node);
                } else {
                    //case 2 rotation
                    doubleWithLeftChild(node);
                }///end else
            }///end if
            node->height = max(getHeight(node->left), getHeight(node->right))+1;
        } else if(node->data < toAdd) {
            insert(toAdd, node->right);
            if(getHeight(node->right)-getHeight(node->left)==2)
            {
                if(node->right->data < toAdd){
                    //case 4 rotation
                    rotateWithRightChild(node);
                } else {
                    //case 3 rotation
                    doubleWithRightChild(node);
                }///end else
            }///end if
            node->height = max(getHeight(node->left), getHeight(node->right))+1;
        }///end else if
    }///end insert

    //case 1 rotations at node k2
    void rotateWithLeftChild(AVLNode<T>*& k2)
    {
        AVLNode<T>* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(getHeight(k2->left), getHeight(k2->right))+1;
        k1->height = max(getHeight(k1->left), k2->height)+1;
        k2 = k1;
    }///end rotateWithLeftChild

    //case 4 rotations at node k2
    void rotateWithRightChild(AVLNode<T>*& k2)
    {
        AVLNode<T>* k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2->height = max(getHeight(k2->left), getHeight(k2->right))+1;
        k1->height = max(getHeight(k1->right), k2->height)+1;
        k2 = k1;
    }///end rotateWithRightChild

    //case 2 rotations at node k3
    void doubleWithLeftChild(AVLNode<T>*& k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }///end doubleWithLeftChild

    //case 3 rotations at node k3
    void doubleWithRightChild(AVLNode<T>*& k3)
    {
        rotateWithLeftChild(k3->right);
        rotateWithRightChild(k3);
    }///end doubleWithRightChild

    //searches for the max value recursively
    AVLNode<T>* findMax(AVLNode<T>*& node)
    {
        if(node->right == nullptr)
            return node;
        else
            return findMax(node->right);
    }///end findMax

    //searches for the minimum value recursively
    AVLNode<T>* findMin(AVLNode<T>*& node)
    {
        if(node->left == nullptr)
            return node;
        else
            return findMin(node->left);
    }///end findMin

    //searches to see if a value is stored recursively
    bool contains(T toFind, AVLNode<T>*& node)
    {
        if(node==nullptr)
            return false;

        if(node->data == toFind)
            return true;
        else if(toFind < node->data)
            return contains(toFind, node->left);
        else
            return contains(toFind, node->right);
    }///end contains

    //recursively empties the tree
    void makeEmpty(AVLNode<T>*& node)
    {
        if(node == nullptr)
            return;

        makeEmpty(node->left);
        makeEmpty(node->right);
        delete node;
    }///end makeEmpty

    T& get(T toGet, AVLNode<T>*& node)
    {
        if(node == nullptr)
            throw underflow_error("doesnt exist");

        if(node->data == toGet)
            return node->data;
        else if(node->data >toGet)
            return get(toGet,node->left);
        else
            return get(toGet, node->right);
    }///end get

    void writeOut(ofstream& out, AVLNode<T>*& node)
    {
        if(node == nullptr)
            return;

        writeOut(out,node->left);
        out << node->data << endl;
        writeOut(out, node->right);
    }///end writeOut
public:
    //empty constructor that will set the root to nullptr
    AVLTree()
    {
        root = nullptr;
        size = 0;
    }///end constructor

    //copy constructor
    AVLTree(const AVLTree<T>& rhs)
    {
        if(this!= &rhs)
            *this = rhs;

        size = rhs.size;
    }///end copy constructor

    ~AVLTree()
    {
        writeOut();
        makeEmpty();
    }///end destructor

    // finds the minimum element in the tree
    const T& findMin()
    {
        if(isEmpty())
            throw underflow_error("empty tree");

        return findMin(root)->data;
    }///end findMin

    // finds the maximum element in the tree
    const T& findMax()
    {
        if(isEmpty())
            throw underflow_error("empty tree");

        return findMax(root)->data;
    }///endfindMax

    // returns whether or not the tree contains a value
    bool contains(WordObject toFind)
    {
        return contains(toFind, root);
    }///end contains

    //returns whether or not the tree is empty
    bool isEmpty()
    {
        return root == nullptr;
    }///end isEmpty

    // clears all values from the tree
    void makeEmpty()
    {
        makeEmpty(root);
    }///end makeEmpty

    //inserts the given value to the tree
    void insert(WordObject toAdd)
    {
        insert(toAdd, root);
        size++;
    }///end insert

    AVLNode<T>& getRoot()
    {
        return root;
    }///end getRoot

    int getSize()
    {
        return size;
    }///end getSize

    T& get(WordObject toGet)
    {
        return get(toGet, root);
    }///end get

    void writeOut()
    {
        ofstream out("AVLTree.txt");
        writeOut(out,root);
        out.close();
    }///end writeOut
};///end AVLTree

#endif // AVLTREE_H