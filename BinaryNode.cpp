/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "BinaryNode.h"
#include<memory>
using namespace std;


                        // Default constructor
template <class AnyType>
BinaryNode<AnyType>::BinaryNode()
{
    left = nullptr;
    right = nullptr;
}
                    // Item initializing constructor
template <class AnyType>
BinaryNode<AnyType>::BinaryNode(const AnyType& anItem)
{
    item = anItem;
    left = nullptr;
    right = nullptr;
}
              // Item and pointers initializing constructor
template <class AnyType>
BinaryNode<AnyType>::BinaryNode(const AnyType& anItem,
                                shared_ptr<BinaryNode<AnyType>> aLeft,
                                shared_ptr<BinaryNode<AnyType>> aRight)
{
    item = anItem;
    left = aLeft;
    right = aRight;
}

template <class AnyType>
void BinaryNode<AnyType>::setItem(const AnyType& anItem)
{
    item = anItem;
}

template <class AnyType>
AnyType BinaryNode<AnyType>::getItem() const
{
    return item;
}

template <class AnyType>
bool BinaryNode<AnyType>::isLeaf() const
{
    return (left==nullptr && right==nullptr);
}

template <class AnyType>
shared_ptr<BinaryNode<AnyType>> BinaryNode<AnyType>::getLeft() const
{
    return left;
}

template <class AnyType>
shared_ptr<BinaryNode<AnyType>> BinaryNode<AnyType>::getRight() const
{
    return right;
}

template <class AnyType>
void BinaryNode<AnyType>::setLeft(shared_ptr<BinaryNode<AnyType>> newLeft)
{
    left = newLeft;
}

template <class AnyType>
void BinaryNode<AnyType>::setRight(shared_ptr<BinaryNode<AnyType>> newRight)
{
    right = newRight;
}


