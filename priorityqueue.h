// priorityqueue.h
//
// Priority queue program to efficiently store, delete, track, and compare items in a queue based on their priority using a binary search tree. Program uses a struct as each element in the queue to keep track of information and accesses it via pointers to create an efficient way of spending memory
// Created maintaining an efficient time algorithym to insert, search, and find at O(logN) time.
//
// Course: CS 251, Fall 2022, Wed 10am lab
// System: macOs using Microsoft Visual Studios
// Author: Ali Abuzir
//

#pragma once

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

template<typename T>

// class priority queue which contains public and private functions and variables to add patients to a queue based on priority
class priorityqueue {

private:
    struct NODE {
        int priority;  // used to build BST
        T value;  // stored data for the p-queue
        bool dup;  // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;  // links to linked list of NODES with duplicate priorities
        NODE* left;  // links to left child
        NODE* right;  // links to right child
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of elements in the pqueue
    NODE* curr;  // pointer to next item in pqueue (see begin and next)


    // helper function used to clear all nodes in a linked list
    void clearLinkedList(NODE* &curr) {
        
        NODE* linkIteration = curr->link; // iterates and 
        while (linkIteration != nullptr) {
            NODE* holdNode = linkIteration->link;
            delete linkIteration; // frees node in linked list
            (this->size)--; // decrements size due to losing a node
            linkIteration = holdNode; // goes to next link after deleting current link
        }
    }


    // recursively goes through our BST using post order traversal to delete nodes from leaf up
    void clearRecursive(NODE* &curr) {
        
        if (curr == nullptr) {
            return;
        }
        else {
            clearRecursive(curr->left);
            clearRecursive(curr->right);
            if (curr->link != nullptr) {
                clearLinkedList(curr); // if there is a linked list attached at a node we free all of those nodes first
            }
            delete curr; // free current node
            (this->size)--; // decrement size due to losing a node
        }
    }


    // copies BST tree contents from other priority queue object using its own heap memory using pre order traversal
    void copyTree(NODE* otherCurr, NODE* &thisCurr) {
        
        if (otherCurr == nullptr) { // if other tree is nullptr
            thisCurr = nullptr; // thisCurr gets nullptr too
            return;
        }
        else {
            if (this->root == thisCurr) { // if node is first going in tree, we assign root
                this->root = new NODE;
                thisCurr = this->root;
            }
            else { // if node is not root
                thisCurr = new NODE;
            }
            
            // copies over contents from other tree
            thisCurr->priority = otherCurr->priority;
            thisCurr->value = otherCurr->value;
            thisCurr->dup = otherCurr->dup;
            thisCurr->left = nullptr;
            thisCurr->right = nullptr;
            thisCurr->parent = nullptr;
            thisCurr->link = nullptr;
            (this->size)++; // increments size

            if (thisCurr->dup == 1) { // if we reach a node in the other object that has a linked list
                NODE* linkedListCurrIter = thisCurr; // for iteration in this object
                NODE* linkedListOtherIter = otherCurr->link; // for iteration in other object
                
                while (linkedListOtherIter != nullptr) { // while other list iteration is not null, we allocate space in this object and copy contents from other object
                    NODE* tempNode = new NODE; // uses a temp node and assigns all contents then assigns it to this objects tree
                    tempNode->priority = linkedListOtherIter->priority;
                    tempNode->value = linkedListOtherIter->value;
                    tempNode->dup = linkedListOtherIter->dup;
                    tempNode->right = nullptr;
                    tempNode->left = nullptr;
                    tempNode->parent = nullptr;
                    tempNode->link = nullptr;
                    (this->size)++; // increments size

                    linkedListCurrIter->link = tempNode;

                    linkedListCurrIter = linkedListCurrIter->link;
                    linkedListOtherIter = linkedListOtherIter->link;
                }
            }
            copyTree(otherCurr->left, thisCurr->left);
            copyTree(otherCurr->right, thisCurr->right);
        }
     }


    // assigns the parent after copying the tree over from a different tree object using pre order traversal
    void assignParent(NODE* &curr) {
        
        if (curr == nullptr) {
            return;
        }
        else {
            if (curr->left != nullptr) {
                curr->left->parent = curr;
            }
            if (curr->right != nullptr) {
                curr->right->parent = curr;
            }
            if (curr == this->root) {
                curr->parent = nullptr;
            }
            assignParent(curr->left);
            assignParent(curr->right);
        }
    }


    // compares two tree objects to check if they are equal using recurrsion
    bool compareTree(NODE* otherCurr, NODE* thisCurr) const {

        if (otherCurr == nullptr && thisCurr == nullptr) {
            return true;
        }
        else if (otherCurr == nullptr) {
            return false;
        }
        else if (thisCurr == nullptr) {
            return false;
        }
        else {
            // keeps recurssing and comparing nodes and if they are always the same we return true else we return false
            if (compareTree(otherCurr->left, thisCurr->left) && otherCurr->priority == thisCurr->priority && otherCurr->value == thisCurr->value && otherCurr->dup == thisCurr->dup && compareTreeLinks(otherCurr, thisCurr) && compareTree(otherCurr->right, thisCurr->right)) {
                return true;
            }
            else {
                return false;
            }
        }
    }


    // called in compareTree
    // checks if the both trees have the same links if they have any. If not, checks if their links are both nullptr
    bool compareTreeLinks(NODE* otherCurr, NODE* thisCurr) const {
        
        if (otherCurr->link == nullptr && thisCurr->link == nullptr) {
            return true;
        }
        else if (otherCurr->link == nullptr) {
            return false;
        }
        else if (thisCurr->link == nullptr) {
            return false;
        }
        else { // else meaning there is a linked list and they both have one
            NODE* otherCurrIterate = otherCurr; // iterates through other tree
            NODE* thisCurrIterate = thisCurr; // iterates through this tree

            // 
            while (otherCurrIterate != nullptr && thisCurrIterate != nullptr) { // iterates until end of tree
                // if contents of both trees are not the same
                if (otherCurrIterate->priority != thisCurrIterate->priority || otherCurrIterate->value != thisCurrIterate->value) {
                    return false;
                }
                thisCurrIterate = thisCurrIterate->link;
                otherCurrIterate = otherCurrIterate->link;
                if (otherCurrIterate == nullptr && thisCurrIterate != nullptr) { // if other tree reaches end of list before this tree
                    return false;
                }
                if (otherCurrIterate != nullptr && thisCurrIterate == nullptr) { // if this tree reaches end of list before the other tree
                    return false;
                }
            }
            return true; // everything checks out at this point
        }
    }


    // deletes the lowest priority node in the tree after a call to dequeue();
    void deleteNode(NODE* &curr) {
        
        if (curr == nullptr) {
            return;
        }
        else {
            // if node has a linked list, we treat that node as the head and we assign the next node in the tree the same parent as the head node and point its left and right nodes to heads right and left nodes
            // we reassign the parents right and left pointers to point to node rather than head node
            // we assign the head's children's parent nodes to point to node
            // we then delete curr
            if (curr->dup == true) { 
                curr->link->left = curr->left;
                curr->link->right = curr->right;
                curr->link->parent = curr->parent;
                if (curr->parent != nullptr) {
                    if (curr->parent->right == curr) {
                        curr->parent->right = curr->link;
                    }
                    else {
                        curr->parent->left = curr->link;
                    }
                }
                if (curr->link->right != nullptr) {
                    curr->link->right->parent = curr->link;
                }
                if (curr->link->left != nullptr) {
                    curr->link->left->parent = curr->link;
                }
                if (root == curr) { // if head node was root, we reassign root to node
                    root = curr->link;
                }
            }

            // if above conditions don't match, if node we are deleting is the root, then we assign the root to point to the right since that is where the rest of the nodes are and so we don't lose our track of our tree
            else if (curr == this->root) {
                this->root = curr->right;
            }

            // if above conditions don't match, if the node's right child is not null, we assign the parent's child node (either left or right depending on where the curr node is on the parents end) to the right child of curr
            // we then assign the curr right childs parent nodes to then point to curr
            else if (curr->right != nullptr) {
                if (curr->parent != nullptr) {
                    if (curr->parent->left == curr) {
                        curr->parent->left = curr->right;
                    }
                    else {
                        curr->parent->right = curr->right;
                    }
                }
                curr->right->parent = curr->parent;
            }

            // if all above conditions are false, we point curr's parents pointer to curr to nullptr since we are going to delete curr and no reassignments are needed
            else {
                if (curr->parent->right == curr) {
                    curr->parent->right = nullptr;
                }
                else {
                    curr->parent->left = nullptr;
                }
            }

            // checks if curr is last node, if so assigns root to nullptr
            if (curr->left == nullptr && curr->right == nullptr && curr->parent == nullptr && curr->dup == false) {
                this->root = nullptr;
            }

            delete curr; // frees curr
            curr = nullptr; // assigns curr to nullptr since there are no more nodes
            (this->size)--; // decrements size due to losing a node
        }
    }

    
    // lowestNode finds the lowest node in the list at any given time even after deletion ieration to as left of the tree as possible
    void lowestNode(NODE* &iteration) {
        
        if (iteration == nullptr) { // 
            return;
        }
        else {
            this->curr = iteration;
            lowestNode(iteration->left);
        }
    }


    // when trying to find next node and right is not null, we find the leftmost node from curr's right node including curr's right node itself
    void afterRight(NODE* &iteration) {
        
        while (iteration->left != nullptr) {
            iteration = iteration->left;
        }
    }


    // uses an inorder traversal to get each node's value and priority in the tree in order by priority
    // copies all values into a stringstream
    void stringNodes(NODE* &curr, ostream &treeStream) {
        
        if (curr == nullptr) {
            return;
        }
        else {
            stringNodes(curr->left, treeStream);
            treeStream << curr->priority << " " << curr->value << " ";
            if (curr->dup == true) {
                NODE* temp = curr;
                while (temp->dup == true) { // if there is a linked list, it gets their values and maintains order when getting values and priorities
                    temp = temp->link;
                    treeStream << temp->priority << " " << temp->value << " ";
                }
            }
            stringNodes(curr->right, treeStream);
        }
    }

    
    // used when finding next node to see if we are at the end of a linked list, if we are then we assign a pointer to point to the head of the linked list
    void checkLinkExistence(NODE* curr, NODE* &findHead, int priority) {
        
        // finds node priority spot on tree by comparing priorities and going to left or right child depending on if desired priority is greater or less than current priority on tree
        while (curr != nullptr) { 
            if (curr->priority > priority) {
                curr = curr->left;
            }
            else if (curr->priority < priority) {
                curr = curr->right;
            }
            else { // if we found the node with the same priority we are looking for
                if (curr->dup == true) { // if this is true, then we can confirm we are at the end of a linked list since our curr before had a dup of false. Of all nodes in a linked list, the last one has dup as false since its link is nullptr
                    findHead = curr;
                }
                break; // no need to keep looping, we now break to be more efficient
            }
        }
    }


public:
    
    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //
    priorityqueue() {
        
        this->root = nullptr;
        this->size = 0;
        this->curr = nullptr;
        
        
    }
    
    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //
    priorityqueue& operator=(const priorityqueue& other) {
        
        if (*this == other) { // if other tree and current tree are already equal, then we don't bother clearing and copying and just return this object as it is to be more efficient
            return *this;
        }

        this->clear(); // we first clear this object and assign default values

        this->curr = this->root; // assign curr to root to be used to copy tree from root

        copyTree(other.root, this->curr); // calls copyTree to copy over tree from other tree

        this->curr = this->root; // assigns curr to parent to assign parents to nodes starting from root

        assignParent(this->curr); // assigns parents

        return *this; // returns this object after copying nodes from other tree and assigning parents
    
    }
    
    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    void clear() {
        
        this->curr = this->root; // assigns curr to root to clear all nodes

        if (curr == nullptr) { // if null, nothing to clear
            return;
        }
        else {
            clearRecursive(curr); // recursively clears nodes in the tree using post order taversal
        }

        // assigns root and curr to nullptr and size to 0 since nothing is left in tree
        this->root = nullptr;
        this->curr = nullptr;
        this->size = 0;
    }
    
    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue() {
        
        
        if (root != nullptr) { // if root is not nullptr, we clear all of our nodes with the destructor
            this->clear();
        }
        
        
    }
    
    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    void enqueue(T value, int priority) {
        
        this->curr = this->root; // assigns curr to root to go through our tree to right spot to insert node without reassigning root and losing our tree in memory

        NODE* prev = nullptr; // previous pointer to see what node's child we are inserting at

        while (curr != nullptr) { // finds spot of insertion for curr and prev spot to which node's child we are inserting our new node
            if (curr->priority < priority) {
                prev = curr;
                curr = curr->right;
            }
            else if (curr->priority > priority) {
                prev = curr;
                curr = curr->left;
            }
            else {
                break;
            }
        }
            
        if (this->root == nullptr) { // if we are inserting our first node, we assign root
            this->root = new NODE;
            this->root->value = value;
            this->root->priority = priority;
            this->root->dup = false;
            this->root->parent = nullptr;
            this->root->left = nullptr;
            this->root->right = nullptr;
            this->root->link = nullptr;
            (this->size)++;
        }

        else if (this->curr == nullptr) { // else we assign curr for all other nodes
            this->curr = new NODE;
            this->curr->value = value;
            this->curr->priority = priority;
            this->curr->dup = false;
            this->curr->parent = nullptr;
            this->curr->left = nullptr;
            this->curr->right = nullptr;
            this->curr->link = nullptr;

            // we use prev to connect curr to tree
            if (prev->priority < priority) { // priority is greater than prev priority, we assign to right child
                prev->right = this->curr;
                this->curr->parent = prev;
            }
            else { // priority is less than prev priority, we assign to right child
                prev->left = this->curr;
                this->curr->parent = prev;
            }
            (this->size)++; // increment size
        }

        else { // meaning we reached a node with the same priority as the new desired node
            while (this->curr->link != nullptr) { // finds end of linked list
                this->curr = this->curr->link;
            }
                
            // allocates and links new desired node to end of linked list
            // assigns components
            this->curr->dup = true;
            this->curr->link = new NODE;
            this->curr->link->value = value;
            this->curr->link->priority = priority;
            this->curr->link->right = nullptr;
            this->curr->link->left = nullptr;
            this->curr->link->link = nullptr;
            this->curr->link->dup = false;
            this->curr->link->parent = nullptr;
            (this->size)++; // increments size
        }
    }

    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    T dequeue() {
        
        T valueOut; // declares a T variable

        begin(); // calls begin to set curr to lowest priority node in tree

        if (this->curr != nullptr) { // sets valueOut curr's value if its not nullptr
            valueOut = this->curr->value;
        }

        deleteNode(this->curr); // deleted curr and makes any necessary adjustments
        
        return valueOut; // returns the value of the node we deleted. (If dequeue is called after there are no nodes left, valueOut will always be the last deleted nodes value, unless changed elsewhere) 
    }
    
    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int Size() {
        
        return this->size;
    }
    
    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    void begin() {

        lowestNode(this->root); // calls lowestNode to get lowest priority node in tree

        return;
    }
    
    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
    // O(logn), where n is the number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (pq.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //
    bool next(T& value, int &priority) {

        if (this->curr != nullptr) { // assigns value and priority of curr before finding next to help us satisfy conditions of finding next if curr is not null
            value = this->curr->value;
            priority = this->curr->priority;
        }

        if (this->curr == nullptr) { // if null, then we return false and leave meaning there isn't a node left in tree
            return false;
        }

        // meaning that either we only have one node and there is no next or that we are at the end of a linked list
        else if (this->curr->right == nullptr && this->curr->left == nullptr && this->curr->parent == nullptr && this->curr->dup == false) {
            NODE* findHead = nullptr; // declare a pointer that if updated, then we are at the end of a linked list and findHead points to head of linked list. If not updated, then we are not at the end of a linked list, so our case would be we only have one node in tree

            checkLinkExistence(this->root, findHead, this->curr->priority); // finds node with priority in tree, if it is the same node based on dup, then we don't update findHead and return false meaning our case was that we just had one node in our tree

            if (findHead != nullptr) { // if we were at the end of a linked list
                this->curr = findHead; // sets curr to findHead

                // checks next conditions again other than condition with single node or end of link list
                if (this->curr->right == nullptr && this->curr->left == nullptr && this->curr->parent == nullptr) {
                    this->curr = nullptr;
                    return false;
                }
                else if (this->curr->right != nullptr) { // finds from curr right's child, the next lowest node
                    this->curr = this->curr->right;
                    afterRight(this->curr);
                }
                else if (this->curr->right == nullptr && this->curr->parent != nullptr) { // finds the parent with a higher priority if there is one
                    NODE* parentTracker = this->curr; // tracks all parents

                    if (parentTracker->parent->priority > priority) { // if curr's parent has a higher priority
                        this->curr = parentTracker->parent;
                    }
                    else { // if curr's ancestors has a higher proirity but not parent
                        while (parentTracker->parent->priority < priority) {
                            parentTracker = parentTracker->parent;
                            if (parentTracker->parent == nullptr) { // meaning all parents don't have a higher priority, implying we have reached the end of the tree and there is no next node
                                this->curr = nullptr;
                                return false;
                    
                            }
                        }
                        this->curr = parentTracker->parent; // assigns curr to parent that has higher priority
                    }
                }
                else { // else if the last node in the linked list is the last node
                    this->curr = nullptr;
                    return false;
                }
            }
            else { // if findHead didn't change, then we only had one node which means we only had a single node and we weren't at the end of a linked list and there is no next node
                this->curr = nullptr;
                return false;
            }

        }

        else if (this->curr->dup == true) { // if we are at a linked list and there is another node next to curr node, we just update curr to the next node
            this->curr = this->curr->link;
        }

        else if (this->curr->right != nullptr) { // if other conditions aren't true, and curr right child is not null. we find the leftest node from the right child's node including the child's node
            this->curr = this->curr->right;
            afterRight(this->curr);
        }

        else if (this->curr->right == nullptr && this->curr->parent != nullptr) { // if curr rights child is null and the parent isn't, we are going to find the parent with a higher priority if there is one
            NODE* parentTracker = this->curr; // tracks all parents
    
            if (parentTracker->parent->priority > priority) { // if curr's parent has a higher priority
                this->curr = parentTracker->parent;
            }
            else { // if curr's ancestors has a higher proirity but not parent
                if (parentTracker->parent != nullptr) {
                    while (parentTracker->parent->priority < priority) {
                        parentTracker = parentTracker->parent;
                        if (parentTracker->parent == nullptr) { // meaning all parents don't have a higher priority, implying we have reached the end of the tree and there is no next node
                            this->curr = nullptr;
                            return false;
                        }
                    }
                }
                this->curr = parentTracker->parent; // assigns curr to parent with higher priority
            }
        }

        // we assign value and priority with the next node's value and priority
        value = this->curr->value;
        priority = this->curr->priority;

        return true; // if we get here, that means we have a next node because if we didn't, one condition above would have caught it and already returned false
    }
    
    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //
    string toString() {
    
        stringstream bsTree; // declares a stringstream to store all values and priorites in order in our tree

        stringNodes(this->root, bsTree); // calls stringNodes to add values and priorities in order

        string wholeTree; // going to store all bsTree contents in here
        string eachPriority; // gets each priority from stringstream
        string eachValue; // gets each value from stringstream

        while (bsTree >> eachPriority >> eachValue) { // goes until the end of bsTree and concateonates each priority and value
            wholeTree += eachPriority + " value: " + eachValue + '\n';

        }

        return wholeTree; // returns the string of all priorities and values
    }
    
    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    T peek() {
    
        T valueOut; // declares a variable of type T for what value we get when we peek

        begin(); // we call begin to get curr to equal the lowest priority and we return its value for peek
        
        if (this->curr != nullptr) { // if curr is not nullptr, we set valueOut to be its value
            valueOut = this->curr->value;
        }

        return valueOut; // returns either an empty string or curr's value depending on if curr is nullptr(meaning there is no nodes in tree) or not.
    }
    
    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
    bool operator==(const priorityqueue& other) const {
        if (compareTree(other.root, this->root) && this->size == other.size) { // compares the contents of everything in the tree to the other tree including the size
            return true; // if they all match, we return true
        }
        else {
            return false; // if they don't all match, we return false
        }
    }
    
    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};
