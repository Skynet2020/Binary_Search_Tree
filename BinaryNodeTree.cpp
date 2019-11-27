#include "BinaryNodeTree.h"

//using namespace std;


//------------------------------------------------------
//   Typedef for Custom Data Types Used in This Class.
//------------------------------------------------------
template <class AnyType>
using BinNode = BinaryNode<AnyType>;

template <class AnyType>
using NodePtr = shared_ptr<BinaryNode<AnyType>>;

template <class AnyType>
using BNT = BinaryNodeTree<AnyType>;

template <class AnyType>
using BNTPtr = shared_ptr<BinaryNodeTree<AnyType>>;



/*******************************************************************************
                          CLASS IMPLEMENTATION.
*******************************************************************************/
               
                    // Default Constructor:
template <class AnyType>
BinaryNodeTree<AnyType>::BinaryNodeTree()
{
    root = nullptr;
}

//------------------------------------------------------
//              Parametrized Constructor #1:
//------------------------------------------------------
template <class AnyType>
BinaryNodeTree<AnyType>::BinaryNodeTree(const AnyType& rootInitializer)
{
    cout << "#1 Parametrized Super Constructor was called" << endl;
    root = make_shared<BinNode>(rootInitializer, nullptr, nullptr);
    
}

                // Parametrized Constructor #2:
template <class AnyType>
BinaryNodeTree<AnyType>::BinaryNodeTree(const AnyType& rootInitializer, 
        const BNTPtr leftTreePtr, const BNTPtr rightTreePtr)
{
    cout << "#2 Param Super Constructor was called" << endl;
    root = make_shared<BinaryNode<AnyType>>(rootInitializer,
                               copyTree(leftTreePtr->root),
                               copyTree(rightTreePtr->root));
}

                // Copy Constructor:
template <class AnyType>
BinaryNodeTree<AnyType>::BinaryNodeTree(const BNT& treePtr)
{
    cout << "Super Copy Constructor was called" << endl;
    root = copyTree(treePtr.root);
}

template<class AnyType>
BinaryNodeTree<AnyType>::~BinaryNodeTree()
{
    root.reset();
}

                // Copy Tree functiion (used by copy consturctor):
template <class AnyType>
NodePtr<AnyType> BinaryNodeTree<AnyType>::
copyTree(const NodePtr oldTreeRootPtr) const
{
    NodePtr newTreePtr;
    
    // Copy tree nodes during preorder traversal:
    if (oldTreeRootPtr != nullptr)
    {
        newTreePtr = make_shared<NodePtr>(oldTreeRootPtr->getItem(),\
                                          nullptr, nullptr);
        newTreePtr->setLeft(copyTree(oldTreeRootPtr->getLeft()));
        newTreePtr->setRight(copyTree(oldTreeRootPtr->getRight()));
    }
    // Else - tree is empty.
    return newTreePtr;
}

                // Get Height fucntion:
template <class AnyType>
int BinaryNodeTree<AnyType>::getHeight() const
{
    return getHeightHelper(root);
}
                // Get Height Helper function:
template <class AnyType>
int BinaryNodeTree<AnyType>::getHeightHelper(NodePtr subTree) const
{
    if (subTree == nullptr)
        return 0;
    else
        return 1 + max(getHeightHelper(subTree->getLeft()), getHeightHelper(subTree->getRight()));
}
          
//------------------------------------------------------
//                Add and Balanced Add.
//------------------------------------------------------
template <class AnyType>
bool BinaryNodeTree<AnyType>::add(const AnyType& newData)
{
    NodePtr newNode = make_shared<BinaryNode<AnyType>>(newData);
    root = balancedAdd(root, newNode);
    return true;
}

template <class AnyType>
NodePtr<AnyType> BinaryNodeTree<AnyType>::
balancedAdd(NodePtr subTree, NodePtr newNode)
{
    if (subTree == nullptr)
        return newNode;
    else
    {
        NodePtr left = subTree->getLeft();
        NodePtr right = subTree->getRight();
        
        if (getHeightHelper(left) > getHeightHelper(right))
        {
            right = balancedAdd(right, newNode);
            subTree->setRight(right);
        }
        else
        {
            left = balancedAdd(left, newNode);
            subTree->setLeft(left);
        }
    }
    return subTree;
}

//------------------------------------------------------
//   Traversal Methods that call the recursive helpers:
//------------------------------------------------------
template <class AnyType>
void BinaryNodeTree<AnyType>::
preorderTraverse(void visit(AnyType&)) const
{
    postorder(visit, root);
}
template <class AnyType>
void BinaryNodeTree<AnyType>::
postorderTraverse(void visit(AnyType&)) const
{
    preorder(visit, root);
}
template <class AnyType>
void BinaryNodeTree<AnyType>::
inorderTraverse(void visit(AnyType&)) const
{
    inorder(visit, root);
}

//------------------------------------------------------
//           Recursive traversal helpers:
//------------------------------------------------------
template <class AnyType>
void BinaryNodeTree<AnyType>::
preorder(void visit(AnyType&), NodePtr aNode) const
{
    if (aNode != nullptr)
    {
        AnyType theItem = aNode->getItem();
        visit(theItem);
        preorder(visit, aNode->getLeft());
        preorder(visit, aNode->getRight());
    }
}

template <class AnyType>
void BinaryNodeTree<AnyType>::
inorder(void visit(AnyType&), NodePtr aNode) const
{
    if (aNode != nullptr)
    {
        inorder(visit, aNode->getLeft());
        AnyType theItem = aNode->getItem();
        visit(theItem);
        inorder(visit, aNode->getRight());
    }
}

template <class AnyType>
void BinaryNodeTree<AnyType>::
postorder(void visit(AnyType&), NodePtr aNode) const
{
    if (aNode != nullptr)
    {
        postorder(visit, aNode->getLeft());
        postorder(visit, aNode->getRight());
        AnyType theItem = aNode->getItem();
        visit(theItem);
    }
}

//------------------------------------------------------
//                      Get Entry():
//------------------------------------------------------
template <class AnyType>
AnyType BinaryNodeTree<AnyType>::getEntry(const AnyType& anEntry) const
{
    if (isEmpty())
        throw PrecondViolatedExcep("getRootData() called with empty tree.");
        
    return root->getItem();
}

//------------------------------------------------------
//                      isEmpty():
//------------------------------------------------------
template <class AnyType>
bool BinaryNodeTree<AnyType>::isEmpty() const
{
    return root == nullptr;
}

//------------------------------------------------------
//                      Contains():
//------------------------------------------------------
template <class AnyType>
bool BinaryNodeTree<AnyType>::contains(const AnyType& anEntry) const
{
    bool isSuccessful = false;
    NodePtr result = findNode(root, anEntry, isSuccessful);
    return isSuccessful;
}

//------------------------------------------------------
//             Get Number of Nodes + Helper:
//------------------------------------------------------
template <class AnyType>
int BinaryNodeTree<AnyType>::getNumberOfNodes() const
{
    return getNumberOfNodesHelper(root);
}
template <class AnyType>
int BinaryNodeTree<AnyType>::getNumberOfNodesHelper(NodePtr subTree) const
{
    if (subTree == nullptr)
        return 0;
    else
        return 1 + getNumberOfNodesHelper(subTree->getLeft())
        + getNumberOfNodesHelper(subTree->getRight());
}

//------------------------------------------------------
//             Root Data Setter and Getter:
//------------------------------------------------------
template <class AnyType>
void BinaryNodeTree<AnyType>::setRootData(const AnyType& newItem)
{
	if (isEmpty())
		root = make_shared<BinNode>(newItem);
    else
        root->setItem(newItem);
}

template <class AnyType>
AnyType BinaryNodeTree<AnyType>::getRootData() const
{
    if (isEmpty())
        throw PrecondViolatedExcep("getRootData() called with empty tree.");
        
    return root->getItem();
}
//------------------------------------------------------
//                      Clear():
//------------------------------------------------------
template <class AnyType>
void BinaryNodeTree<AnyType>::clear()
{
    root.reset();
}

//------------------------------------------------------
//                Remove() and Remove Value():
//------------------------------------------------------
template <class AnyType>
bool BinaryNodeTree<AnyType>::remove(const AnyType& target)
{
    bool isSuccessful = false;
    root = removeValue(root, target, isSuccessful);
    return isSuccessful;
}

template <class AnyType>
NodePtr<AnyType> BinaryNodeTree<AnyType>::
removeValue(NodePtr subTree, const AnyType target, bool& success)
{
    if(subTree == nullptr) // not found here
        return subTree;
    
    if (subTree->getItem() == target) // found it
    {
        subTree = moveValuesUpTree(subTree);
        success = true;
        return subTree;
    }
    else
    {
        auto targetNodePtr = removeValue(subTree->getLeft(), target, success);
        subTree->setLeft(targetNodePtr);
        if (!success) // no need to search right subTree
        {
            targetNodePtr = removeValue(subTree->getRight(), target, success);
            subTree->setRight(targetNodePtr);
        }  // end if
        
        return subTree;
    }
}

//------------------------------------------------------
//                  Move Values Up Tree():
//------------------------------------------------------
template <class AnyType>
NodePtr<AnyType> BinaryNodeTree<AnyType>::moveValuesUpTree(NodePtr subTree)
{
    auto  leftPtr = subTree->getLeft();
    auto  rightPtr = subTree->getRight();
    int leftHeight = getHeightHelper(leftPtr);
    int rightHeight = getHeightHelper(rightPtr);
    if (leftHeight > rightHeight)
    {
        subTree->setItem(leftPtr->getItem());
        leftPtr = moveValuesUpTree(leftPtr);
        subTree->setLeft(leftPtr);
        return subTree;
    }
    else
    {
        if (rightPtr != nullptr)
        {
            subTree->setItem(rightPtr->getItem());
            rightPtr = moveValuesUpTree(rightPtr);
            subTree->setRight(rightPtr);
            return subTree;
        }
        else
        {
            //this was a leaf!
            // value not important
            return nullptr;
        }
    }
}

//------------------------------------------------------
//                     Find Node():
//------------------------------------------------------
template <class AnyType>
NodePtr<AnyType> BinaryNodeTree<AnyType>::
findNode(NodePtr tree, const AnyType& target, bool& success) const
{
    if (tree == nullptr) // not found here
        return tree;
    
    if (tree->getItem() == target) // found it
    {
        success = true;
        return tree;
    }
    else
    {
        NodePtr targetNodePtr = findNode(tree->getLeft(), target, success);
        if (!success) // no need to search right subTree
        {
            targetNodePtr = findNode(tree->getRight(), target, success);
        }  // end if
        
        return targetNodePtr;
    } 
}

//------------------------------------------------------
//         Assignment Operator (=)overloading :
//------------------------------------------------------
template <class AnyType>
BinaryNodeTree<AnyType>& BinaryNodeTree<AnyType>::
operator=(const BNT& rightHandSide)
{
    if (!isEmpty())
        clear();
    this = copyTree(&rightHandSide);
    return *this;
}
/*******************************************************************************
                          NEEDS TO BE IMPLEMENTED:
*******************************************************************************/
