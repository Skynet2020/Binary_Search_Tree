/*******************************************************************************
 * File:   sortedtree.cpp
 * Author: Arman B.
 * Created on November 20, 2019, 7:02 AM
 * Programming Fundamentals III: Data Structure
 *
 * This program is an implementation of Lab-6: Binary Search Tree.
 *
*******************************************************************************/

#include <iostream>
#include <memory>
#include <random>
#include <chrono>
#include <thread>

#include "BinaryNodeTree.h"
#include "BinarySearchTree.h"
#include "BinaryTreeInterface.h"
#include "PrecondViolatedExcep.h"
using namespace std;

//------------------------------------------------------
//                      Prototypes:
//------------------------------------------------------
int generateARandomNumber();
void displayHeader();
void testRunner(int size);
template <class AnyType>
void display(AnyType& anItem);


/*******************************************************************************
*                                   MAIN									   *
*******************************************************************************/
int main(int argc, char** argv) {
    
    int size = 21; // Sets the size of the Binary Tree.    
    testRunner(size);
    
    return 0;
}
/******************************************************************************/


//------------------------------------------------------
//      TESTING THE BINARY SEARCH TREE CLASS:
//------------------------------------------------------
void testRunner(int size) {    
    
    shared_ptr<BinaryNodeTree<int>> binSearchTree = make_shared<BinarySearchTree<int>>();
    int firstEntry;
    
    displayHeader();
    cout << endl;   
    
    cout << "Tree isEmpty()?: " << binSearchTree->isEmpty()\
            << " (should be 1)" << endl << endl;
    
    cout << "Populating the tree with random numbers:";    
    for (int i=1; i<=size; i++)
    {
        int randomNumber = generateARandomNumber();
        cout << ' ' << randomNumber;
        if (binSearchTree->contains(randomNumber))
            --i;
        binSearchTree->add(randomNumber);        
        
        if (i==1)
            firstEntry = randomNumber;        
    } cout << endl << endl;
    
    cout << "List isEmpty()?: " << binSearchTree->isEmpty()\
            << " (should be 0)" << endl << endl;
    
    cout << "Number of nodes: " << binSearchTree->getNumberOfNodes() << endl;
    cout << "Content of the tree:";
    binSearchTree->inorderTraverse(display);
    cout << endl << endl;
    
    cout << "First entry was: " << firstEntry << endl;
    if (binSearchTree->remove(firstEntry))
        cout << "First entry was removed from the tree." << endl;
    else
        cout << "Failure removing first entry" << endl;
    
    cout << "\nNumber of nodes: " << binSearchTree->getNumberOfNodes() << endl;
    cout << "Updated content of the tree:";
    binSearchTree->inorderTraverse(display);
    cout << endl << endl;
    
    cout << "Attempt to remove an unexsisting value (200): ";
    binSearchTree->remove(200);
    
    cout << "\nAttempt to set root data: ";
    try {
        binSearchTree->setRootData(66);
    }
    catch (PrecondViolatedExcep err) {
        cout << err.what() << endl;
    }    
}

void displayHeader()
{
    cout << "\t************************************************"\
       << "\n\t*           LAB-6: BINARY SEARCH TREE          *"\
       << "\n\t************************************************"\
       << endl;
}

template <class AnyType>
void display(AnyType& anItem)
{
    cout << ' ' << anItem;
}


//------------------------------------------------------
//		GENERATE A RANDOM NUMBER:
//------------------------------------------------------
int generateARandomNumber()
{
    ///***** Chrono library: *****///
    typedef chrono::high_resolution_clock myclock;
    myclock::time_point beginning = myclock::now();

    // Creates an interval between two now() to get a higher seed:
    std::this_thread::sleep_for(chrono::milliseconds(3));

    // Duration calculates the time span between two now() measurements:
    myclock::duration d = myclock::now() - beginning;

    unsigned seed = d.count();
    default_random_engine generator(seed);

    uniform_int_distribution<int> distribution(1, 100);
    return distribution(generator);
}
