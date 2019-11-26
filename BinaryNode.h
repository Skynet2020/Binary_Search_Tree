/*
 * Разобратсья с вопросом, что делать с item при пустой инициализации объекта
 * (дефолтным конструктором).
 */

/* 
 * File:   BinaryNode.h
 * Author: Arman B.
 * Created on November 20, 2019, 7:06 AM
 */

#ifndef BINARYNODE_H
#define BINARYNODE_H

#include <memory>
using namespace std;


template <class AnyType>
class BinaryNode
{
protected:
    AnyType item;
    shared_ptr<BinaryNode<AnyType>> left; //uses shared_ptr
    shared_ptr<BinaryNode<AnyType>> right; //uses shared_ptr
public:
    BinaryNode();
    BinaryNode(const AnyType& anItem);
    BinaryNode(const AnyType& anItem,
            shared_ptr<BinaryNode<AnyType>> left,
            shared_ptr<BinaryNode<AnyType>>  right);
    
    void setItem(const AnyType& anItem);
    AnyType getItem() const;
    bool isLeaf() const;
    
    shared_ptr<BinaryNode<AnyType>> getLeft() const; //uses shared_ptr, auto can be used instead
    shared_ptr<BinaryNode<AnyType>> getRight() const; //uses shared_ptr, auto can be used instead
    
    void setLeft(shared_ptr<BinaryNode<AnyType>> newLeft);
    void setRight(shared_ptr<BinaryNode<AnyType>> newRight);
            
};
#include "BinaryNode.cpp"
#endif /* BINARYNODE_H */



