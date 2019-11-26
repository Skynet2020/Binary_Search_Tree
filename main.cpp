/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Arman B.
 * Created on November 20, 2019, 7:02 AM
 */

#include <iostream>
#include <memory>
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "BinarySearchTree.h"
#include "BinaryTreeInterface.h"
using namespace std;

/*
 * 
 */
template <class AnyType>
void display(AnyType& anItem)
{
   cout << "Displaying item - " << anItem << endl;
}  // end display

int main(int argc, char** argv) {
    
//    unique_ptr<int> myIntPtr = make_unique<int>(5);
    shared_ptr<int> myIntPtr = make_shared<int>(5);
    cout << &myIntPtr << endl;
    shared_ptr<int> sharingPtr = myIntPtr;
    cout << &sharingPtr << endl;
    
    
    
    /// Два следующих выражения равнозначны по свеому результату:
    shared_ptr<BinaryNode<int>> aBinaryNode = make_shared<BinaryNode<int>>(999);
//    auto aBinaryNode = make_shared<BinaryNode<int>>(999);
    
    cout << "Get Item(): " << aBinaryNode->getItem() << endl;
//    cout << aBinaryNode->getLeft() << endl;
//    cout << aBinaryNode->getRight() << endl;
//    cout << "isLeaf?: " << aBinaryNode->isLeaf() << endl;
//       
//    auto binNode2 = make_shared<BinaryNode<int>>(77);
//    auto binNode3 = make_shared<BinaryNode<int>>(55);
//    auto binNode4 = make_shared<BinaryNode<int>>(1000, binNode2, binNode3);
//    cout << "binNode4 isLeaf?: " << binNode4->isLeaf() << endl;
//    
//    cout << "binNode2 item: " << binNode2->getItem() << endl;
//    cout << "binNode3 item: " << binNode3->getItem() << endl;
//    aBinaryNode->setLeft(binNode2);
//    cout << "Get Left(): " << aBinaryNode->getLeft() << endl;
//    aBinaryNode->setRight(binNode3);
//    cout << "Get Right(): " << aBinaryNode->getRight() << endl;
//    
//    auto left = aBinaryNode->getLeft();
//    cout << "Get item of the LEFT: " << left->getItem()<< endl;
    
    
    /***** TESTING THE BINARY NODE TREE CLASS *****/
	cout << "\n/***** TESTING THE BINARY NODE TREE CLASS *****/" << endl;
    auto binTree = make_shared<BinaryNodeTree<int>>();
	cout << "binTree isEmpty(): " << binTree->isEmpty() << endl;
	binTree->add(5);
	binTree->add(6);
	binTree->add(7);
	//binTree->add(8);
	//cout << "root value: " << binTree->getRootData() << endl;
    cout << "binTree->getHeight(): " << binTree->getHeight() << endl;
    
    cout << "Value addition attempt..." << endl;
    cout << "binTree->getHeight(): " << binTree->getHeight() << endl;
    
    
    /// ДЛЯ ЭТОГО БЛОКА НАДО РЕШИТЬ TRY-CATCH !!!
    
    /***** TESTING THE BINARY SEARCH TREE CLASS *****/
    cout << "\n/***** TESTING THE BINARY SEARCH TREE CLASS *****/" << endl;
    
	auto binSearchTree = make_shared<BinarySearchTree<int>>();
    cout << "binSearchTree isEmpty(): " << binSearchTree->isEmpty() << endl;
//	cout << "New root value: " << binSearchTree->getRootData() << endl;
	cout << "Addng values: 5, 7, 9, 4, 6" << endl;
	binSearchTree->add(5);
	binSearchTree->add(7);
	binSearchTree->add(9);
	binSearchTree->add(4);
	binSearchTree->add(6);
//    binSearchTree->add(5);
	binSearchTree->inorderTraverse(display);
	try{
        binSearchTree->setRootData(66);
	}
	catch(PrecondViolatedExcep err)
    {
	    cout << err.what() << endl;
    }


	cout << "Tree height: " << binSearchTree->getHeight() << endl;
	cout << "Contains 5?: " << binSearchTree->contains(5) << endl;
	cout << "Contains 7?: " << binSearchTree->contains(7) << endl;

    binSearchTree->remove(5);
//	if (!binSearchTree->remove(5))
//	{
//		cout << "remove() returned false => wasn't successfull" << endl;
//	}
//	else
//	{
//		cout << "remove() returned true => was successfull" << endl;
//	}
	binSearchTree->inorderTraverse(display);

    //cout << "root value: " << binSearchTree->getRootData() << endl; // CRUSHES ON EMPTY TREE
    /*cout << "Setting a new value for root..." << endl;
    binSearchTree->setRootData(7);
    cout << "New root value: " << binSearchTree->getRootData() << endl;*/


	/*
    cout << "binSearchTree->add(5): " << binSearchTree->add(5) << endl;
    cout << "binSearchTree->add(9): " << binSearchTree->add(9) << endl;
    cout << "binSearchTree->add(4): " << binSearchTree->add(4) << endl;
    cout << "binSearchTree->add(6): " << binSearchTree->add(6) << endl;
	try
	{
		binSearchTree->add(5);
	}
	catch(PrecondViolatedExcep err)
	{
		cout << err.what() << endl;
	}
    binSearchTree->inorderTraverse(display);*/





	/// REMOVE BLOCK TEST:
	/*cout << "binSearchTree->add(5): " << binSearchTree->add(5) << endl;
	binSearchTree->inorderTraverse(display);
	if (!binSearchTree->remove(5))
	{
		cout << "remove(5) returned false" << endl;
	}	
	binSearchTree->inorderTraverse(display);*/
	

    return 0;
}
