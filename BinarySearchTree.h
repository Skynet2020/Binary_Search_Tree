/*
	1. setRootData() - Needs implementation. Do we need this function? Why not to use the parent class's?
	2. How to organize constructors? Is it possible to use the super class's constructors w/out redefining them
		in the sub-class?
	3. getEntry() - What's its purpose? We provide the value as a parameter, and the function returns exactly
		the same value. So what's the purpose?
    4. How to disable th setRootData()?
*/
 
#ifndef BINARY_SEARCH_TREE_
#define BINARY_SEARCH_TREE_

#include <memory>
#include <vector>
#include <iostream>
#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcep.h"
using namespace std;

template<class AnyType>
class BinarySearchTree : public BinaryNodeTree<AnyType>
{
// use this->rootPtr to access the BinaryNodeTree rootPtr

    typedef shared_ptr<BinaryNode<AnyType>> NodePtr;

    
   
protected:
   //------------------------------------------------------------
   // Protected Utility Methods Section:
   // Recursive helper methods for the public methods.
   //------------------------------------------------------------
   // Recursively finds where the given node should be placed and
   // inserts it in a leaf at that point.
   NodePtr placeNode(NodePtr subTreePtr, NodePtr newNode);
   
   // Removes the given target value from the tree while maintaining a
   // binary search tree.
   NodePtr removeValue(NodePtr subTreePtr, const AnyType target, bool& success) override;
   
   // Removes a given node from a tree while maintaining a
   // binary search tree.
   NodePtr removeNode(NodePtr nodePtr);
   
   // Removes the leftmost node in the left subtree of the node
   // pointed to by nodePtr.
   // Sets inorderSuccessor to the value in this node.
   // Returns a pointer to the revised subtree.
   NodePtr removeLeftmostNode(NodePtr subTreePtr, AnyType& inorderSuccessor);
   
   // Returns a pointer to the node containing the given value,
   // or nullptr if not found.
   NodePtr findNode(NodePtr treePtr, const AnyType& target) const;
   
public:
    void setRootData(const AnyType& newData) override;
    bool add(const AnyType& newEntry) override;
    bool remove(const AnyType& anEntry) override;
    AnyType getEntry(const AnyType& anEntry) const override;
    bool contains(const AnyType& anEntry) const override;
   
};
#endif


/*******************************************************************************
 * 
 *                          CLASS IMPLEMENTATION. 
 * 
*******************************************************************************/

template <class AnyType>
using NodePtr = shared_ptr<BinaryNode<AnyType>>;


/*******************************************************************************
*                            PROTECTED METHODS SECTION:									   *
*******************************************************************************/

//------------------------------------------------------
//                      Place Node():
//------------------------------------------------------
template <class AnyType>
NodePtr<AnyType> BinarySearchTree<AnyType>::
placeNode(NodePtr subTreePtr, NodePtr newNode)
{
    if (subTreePtr == nullptr)
        return newNode;

    else if(subTreePtr->getItem() == newNode->getItem())
    {
        return subTreePtr;
    }

    else
    {
        if(subTreePtr->getItem() > newNode->getItem())
        {
            NodePtr tempPtr = placeNode(subTreePtr->getLeft(), newNode);
            subTreePtr->setLeft(tempPtr);
        }
        else
        {
            NodePtr tempPtr = placeNode(subTreePtr->getRight(), newNode);
            subTreePtr->setRight(tempPtr);
        }
    }    
    return subTreePtr;
}

//------------------------------------------------------
//                    Remove Value():
//------------------------------------------------------
template <class AnyType>
NodePtr<AnyType> BinarySearchTree<AnyType>::
removeValue(NodePtr subTreePtr, const AnyType target, bool& success)
{
    if (subTreePtr == nullptr)
    {
        success = false;
        return subTreePtr;
    }

    else if (!contains(target))
    {
        cout << "The value is not in the tree" << endl;
        return subTreePtr;
    }

    else if (subTreePtr->getItem() == target)
    {
        subTreePtr = removeNode(subTreePtr);
        success = true;
        return subTreePtr;
    }

    else if (subTreePtr->getItem() > target) // Search the left subtree
    {
        NodePtr tempPtr = removeValue(subTreePtr->getLeft(), target, success);
        subTreePtr->setLeft(tempPtr);
        return subTreePtr;
    }

    else // Search the right subtree
    {
        NodePtr tempPtr = removeValue(subTreePtr->getRight(), target, success);
        subTreePtr->setRight(tempPtr);
        return subTreePtr;
    }
}

//------------------------------------------------------
//                    Remove Node():
//------------------------------------------------------
template <class AnyType>
NodePtr<AnyType> BinarySearchTree<AnyType>::
removeNode(NodePtr nodePtr)
{	
    bool isLeaf = ((nodePtr->getLeft() == nullptr) && (nodePtr->getRight() == nullptr));
    bool leftIsNotEmpty = (nodePtr->getLeft() != nullptr);
    bool rightIsNotEmpty = (nodePtr->getRight() != nullptr);
    bool hasOneChild = (leftIsNotEmpty==false || rightIsNotEmpty==false);
    bool hasBothChildren = (leftIsNotEmpty && rightIsNotEmpty);

    NodePtr nodeToConnect;


    if (isLeaf)
    {
        nodePtr.reset();
        return nodePtr;
    }
    else if (hasOneChild)
    {
        if (leftIsNotEmpty)
    {
        nodeToConnect = nodePtr->getLeft();
    }

        else // if rightIsNotEmpty
        {
                nodeToConnect = nodePtr->getRight();			
        }
        nodePtr.reset();
        return nodeToConnect;
    }
    else if (hasBothChildren) // subTree has two children
    {
        AnyType newNodeValue;
        NodePtr tempPtr = removeLeftmostNode(nodePtr->getRight(), newNodeValue);
        nodePtr->setRight(tempPtr);
        nodePtr->setItem(newNodeValue);
        return nodePtr;
    }
}

//------------------------------------------------------
//               Remove Leftmost Node():
//------------------------------------------------------
template <class AnyType>
NodePtr<AnyType> BinarySearchTree<AnyType>::
removeLeftmostNode(NodePtr subTreePtr, AnyType& inorderSuccessor)
{
    if (subTreePtr->getLeft() == nullptr) // Current node is the leftmost node.
    {
        inorderSuccessor = subTreePtr->getItem();
        return removeNode(subTreePtr);
    }
    else // Current node is not the leftmost => apply this function to its left node (branch).
    {
        NodePtr tempPtr = removeLeftmostNode(subTreePtr->getLeft(), inorderSuccessor);
        subTreePtr->setLeft(tempPtr);
        return subTreePtr;
    }
}

//------------------------------------------------------
//                  Find Node():               
//------------------------------------------------------
template <class AnyType>
NodePtr<AnyType> BinarySearchTree<AnyType>::
findNode(NodePtr treePtr, const AnyType& target) const
{    
    if (treePtr == nullptr) // not found here
        return treePtr;
    
    if (treePtr->getItem() == target) // found it
    {
        return treePtr;
    }
    else
    {
        NodePtr targetNodePtr;
        
        if (target < treePtr->getItem())
            targetNodePtr = findNode(treePtr->getLeft(), target);
        else
            targetNodePtr = findNode(treePtr->getRight(), target);
             
        return targetNodePtr;
    }
}


/*******************************************************************************
*                             PUBLIC METHODS SECTION:									   *
*******************************************************************************/

//------------------------------------------------------
//                   Set Root Data():
//------------------------------------------------------
template <class AnyType>
void BinarySearchTree<AnyType>::setRootData(const AnyType& newData)
{
	throw PrecondViolatedExcep("setRootData() is not allowed in BinarySearchTree");
}


//------------------------------------------------------
//                         Add():
//------------------------------------------------------
template <class AnyType>
bool BinarySearchTree<AnyType>::add(const AnyType& newEntry)
{
    if (this->root == nullptr)
    {
        this->root = make_shared<BinaryNode<AnyType>>(newEntry);
    }

    else
    {
        NodePtr newNode = make_shared<BinaryNode<AnyType>>(newEntry);
        auto result = placeNode(this->root, newNode);
        return true;
    }
}

//------------------------------------------------------
//                      Remove():
//------------------------------------------------------
template <class AnyType>
bool BinarySearchTree<AnyType>::remove(const AnyType& target)
{
	bool success = false;
	NodePtr rootPtr = removeValue(this->root, target, success);
	
	return success;
}

//------------------------------------------------------
//                      Get Entry():
//------------------------------------------------------
template <class AnyType>
AnyType BinarySearchTree<AnyType>::getEntry(const AnyType& anEntry) const
{
    // STUB        
}

//------------------------------------------------------
//                      Contains():
//------------------------------------------------------
template <class AnyType>
bool BinarySearchTree<AnyType>::contains(const AnyType& anEntry) const
{
    if (BinaryNodeTree<AnyType>::isEmpty())   
        return false;
    else
    {
        NodePtr tempPtr = findNode(this->root, anEntry);
        if (tempPtr != nullptr)
                return true;
        else
                return false;
    }    
}











