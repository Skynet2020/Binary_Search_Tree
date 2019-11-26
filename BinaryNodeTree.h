#ifndef BINARYNODETREE_H
#define BINARYNODETREE_H

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "PrecondViolatedExcep.h"
#include "NotFoundException.h"
#include <memory>
using namespace std;



template <class AnyType>
class BinaryNodeTree : public BinaryTreeInterface<AnyType>
{
	typedef BinaryNode<AnyType> BinNode;
	typedef BinaryNodeTree<AnyType> BNT;
	typedef shared_ptr<BinaryNode<AnyType>> NodePtr;
	typedef shared_ptr<BinaryNodeTree<AnyType>> BNTPtr;

protected:
	shared_ptr<BinaryNode<AnyType>> root;

	// Recursive traversal helper methods:
	void preorder(void visit(AnyType&), NodePtr aNode) const;
	void inorder(void visit(AnyType&), NodePtr aNode) const;
	void postorder(void visit(AnyType&), NodePtr aNode) const;

	int getHeightHelper(NodePtr subTree) const;
	int getNumberOfNodesHelper(NodePtr subTree) const;

	// Recursiveley deletes all nodes from the tree:   
	NodePtr balancedAdd(NodePtr subTree, NodePtr newNode);
	virtual NodePtr removeValue(NodePtr subTree, const AnyType target, bool& success);
	NodePtr moveValuesUpTree(NodePtr subTree);
	NodePtr findNode(NodePtr tree, const AnyType& target, bool& success) const;
	NodePtr copyTree(const NodePtr tree) const;

public:
	//------------------------------------------------------
	//          Constructor and Destructor Section.
	//------------------------------------------------------
	BinaryNodeTree();
	BinaryNodeTree(const AnyType& rootItem);
	BinaryNodeTree(const AnyType& rootItem, const BNTPtr leftTree, const BNTPtr rightTree);
	BinaryNodeTree(const BNT& tree);
	virtual ~BinaryNodeTree();

	//------------------------------------------------------
	//          Public BinaryTreeInterface Methods.
	//------------------------------------------------------
	virtual AnyType getEntry(const AnyType& anEntry) const;
	AnyType getRootData() const;

	bool isEmpty() const;
	virtual bool add(const AnyType& newData);
	virtual bool remove(const AnyType& data);
	virtual bool contains(const AnyType& anEntry) const;

	int getHeight() const;
	int getNumberOfNodes() const;

	void clear();
	virtual void setRootData(const AnyType& newData);

	//------------------------------------------------------
	//              Public Traversals Section.
	//------------------------------------------------------
	void preorderTraverse(void visit(AnyType&)) const;
	void inorderTraverse(void visit(AnyType&)) const;
	void postorderTraverse(void visit(AnyType&)) const;

	//------------------------------------------------------
	//              Overloaded Operator Section.
	//------------------------------------------------------
	BinaryNodeTree<AnyType>& operator=(const BinaryNodeTree& rightHandside);
};
#include "BinaryNodeTree.cpp"
#endif /* BINARYNODETREE_H */
