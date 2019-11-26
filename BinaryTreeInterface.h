/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinaryTreeInterface.h
 * Author: Arman B.
 *
 * Created on November 20, 2019, 7:41 AM
 */

#ifndef BINARYTREEINTERFACE_H
#define BINARYTREEINTERFACE_H
#include "NotFoundException.h"

template <class AnyType>
class BinaryTreeInterface
{
public:    
    virtual AnyType getRootData() const = 0;
    virtual AnyType getEntry(const AnyType& anEntry) const = 0;
    
    virtual bool isEmpty() const = 0;
    virtual bool add(const AnyType& newData) = 0;
    virtual bool remove(const AnyType& target) = 0;
    virtual bool contains(const AnyType& anEntry) const= 0;
    
    virtual int getHeight() const = 0;
    virtual int getNumberOfNodes() const = 0;    
    
    virtual void clear() = 0;
    virtual void setRootData(const AnyType& newData) = 0;
    
    virtual void preorderTraverse(void visit(AnyType&)) const = 0;
    virtual void inorderTraverse(void visit(AnyType&)) const = 0;
    virtual void postorderTraverse(void visit(AnyType&)) const = 0;
    
    virtual ~BinaryTreeInterface() {  }
};
#endif /* BINARYTREEINTERFACE_H */

















