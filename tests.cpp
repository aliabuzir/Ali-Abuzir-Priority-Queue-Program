// tests.cpp
//
// Using google tests, a thorough dive into testing priorityqueue.h is performed here by measuring all potential cases along with edge cases for each public member function of priorityqueue.h
//
// Course: CS 251, Fall 2022, Wed 10am lab
// System: macOs using Microsoft Visual Studios
// Author: Ali Abuzir
// 

#include <gtest/gtest.h>
#include "priorityqueue.h"
#include <vector>


// tests priorityqueue object constructor and whether or not they assign proper default values for size and root with various data types for the priorityqueue object
TEST(priorityqueue, constructor) {
    priorityqueue<string> constructorCheck;
    EXPECT_EQ(constructorCheck.getRoot(), nullptr);
    EXPECT_EQ(constructorCheck.Size(), 0);

    priorityqueue<int> constructorCheck2;
    EXPECT_EQ(constructorCheck.getRoot(), nullptr);
    EXPECT_EQ(constructorCheck2.Size(), 0);

    priorityqueue<bool> constructorCheck3;
    EXPECT_EQ(constructorCheck.getRoot(), nullptr);
    EXPECT_EQ(constructorCheck3.Size(), 0);

    priorityqueue<double> constructorCheck4;
    EXPECT_EQ(constructorCheck.getRoot(), nullptr);
    EXPECT_EQ(constructorCheck4.Size(), 0);

    priorityqueue<char> constructorCheck5;
    EXPECT_EQ(constructorCheck.getRoot(), nullptr);
    EXPECT_EQ(constructorCheck5.Size(), 0);
}


// tests the overloaded operator= function with various data types for the priorityqueue objects and testing whether or not every aspect of one object gets properly copied over
TEST(priorityqueue, operatorequals) {
    priorityqueue<int> operatorEquals1;
    priorityqueue<int> operatorEquals2;
    operatorEquals1.enqueue(6, 1);
    operatorEquals1.enqueue(3, 1);
    operatorEquals1.enqueue(6, 1);
    operatorEquals1.enqueue(1, 2);
    operatorEquals1.enqueue(-1, 2);
    operatorEquals1.enqueue(90, 3);
    operatorEquals1.enqueue(0, 3);
    operatorEquals1.enqueue(43, 4);
    operatorEquals1.enqueue(15, 5);
    operatorEquals1.enqueue(0, 6);
    operatorEquals1.enqueue(6, 7);
    operatorEquals1.enqueue(6, 7);
    operatorEquals1.enqueue(6, 7);
    operatorEquals2 = operatorEquals1;
    EXPECT_EQ(operatorEquals2 == operatorEquals1, true);
    EXPECT_EQ(operatorEquals2.Size() == operatorEquals1.Size(), true);
    
    operatorEquals1.dequeue();
    EXPECT_EQ(operatorEquals2 == operatorEquals1, false);
    EXPECT_EQ(operatorEquals2.Size() == operatorEquals1.Size(), false);
    operatorEquals2.dequeue();
    EXPECT_EQ(operatorEquals2 == operatorEquals1, true);
    EXPECT_EQ(operatorEquals2.Size() == operatorEquals1.Size(), true);

    operatorEquals1 = operatorEquals2;
    EXPECT_EQ(operatorEquals2 == operatorEquals1, true);
    EXPECT_EQ(operatorEquals2.Size() == operatorEquals1.Size(), true);

    priorityqueue<int> operatorEquals3;
    priorityqueue<int> operatorEquals4;

    operatorEquals3 = operatorEquals4;
    EXPECT_EQ(operatorEquals3 == operatorEquals4, true);
    EXPECT_EQ(operatorEquals3.Size() == operatorEquals4.Size(), true);

    priorityqueue<bool> operatorEquals5;
    priorityqueue<bool> operatorEquals6;
    operatorEquals5.enqueue(1, 1);
    operatorEquals5 = operatorEquals6;
    EXPECT_EQ(operatorEquals5 == operatorEquals6, true);
    operatorEquals5 = operatorEquals6;
    EXPECT_EQ(operatorEquals5 == operatorEquals6, true);

    priorityqueue<double> operatorEquals7;
    priorityqueue<double> operatorEquals8;
    operatorEquals7.enqueue(12.3, 1);
    operatorEquals8.enqueue(12.3, 4);
    operatorEquals7 = operatorEquals8;
    EXPECT_EQ(operatorEquals7 == operatorEquals8, true);
    operatorEquals7 = operatorEquals8;
    EXPECT_EQ(operatorEquals7 == operatorEquals8, true);

    priorityqueue<string> operatorEquals9;
    priorityqueue<string> operatorEquals10;
    operatorEquals9.enqueue("dan", 1);
    operatorEquals10.enqueue("rodger", 4);
    operatorEquals10.enqueue("irene", 4);
    operatorEquals9 = operatorEquals10;
    EXPECT_EQ(operatorEquals9 == operatorEquals10, true);
    operatorEquals9 = operatorEquals10;
    EXPECT_EQ(operatorEquals9 == operatorEquals10, true);


    priorityqueue<char> operatorEquals11;
    priorityqueue<char> operatorEquals12;
    operatorEquals11.enqueue('d', 1);
    operatorEquals12.enqueue('r', 4);
    operatorEquals11.enqueue('r', 4);
    operatorEquals12 = operatorEquals11;
    EXPECT_EQ(operatorEquals11 == operatorEquals12, true);
    operatorEquals11 = operatorEquals12;
    EXPECT_EQ(operatorEquals11 == operatorEquals12, true);

}


// tests the enqueue and dequeue functions with various data types for the priorityqueue objects checking if nodes are assigned and allocated properly and deallocated properly and returning correct values
TEST(priorityqueue, enqueueAndDequeue) {
    priorityqueue<int> enqueueCheck;
    enqueueCheck.enqueue(6, 1);
    enqueueCheck.enqueue(3, 1);
    enqueueCheck.enqueue(6, 1);
    enqueueCheck.enqueue(1, 2);
    enqueueCheck.enqueue(-1, 2);
    enqueueCheck.enqueue(90, 3);
    enqueueCheck.enqueue(0, 3);
    enqueueCheck.enqueue(43, 4);
    enqueueCheck.enqueue(15, 5);
    enqueueCheck.enqueue(0, 6);
    enqueueCheck.enqueue(6, 7);
    enqueueCheck.enqueue(6, 7);
    enqueueCheck.enqueue(6, 7);
    EXPECT_EQ(enqueueCheck.Size(), 13);

    vector<int> valueInt {6, 3, 6, 1, -1, 90, 0, 43, 15, 0, 6, 6, 6};
    for (size_t i = 0; i < valueInt.size(); ++i) {
        EXPECT_EQ(enqueueCheck.dequeue() == valueInt.at(i), true);
    }

    priorityqueue<string> dequeueCheck;

    dequeueCheck.enqueue("alpha", 1);
    dequeueCheck.enqueue("alpha2", 1);
    dequeueCheck.enqueue("alpha3", 1);
    dequeueCheck.enqueue("alpha4", 2);
    dequeueCheck.enqueue("alpha5", 2);
    dequeueCheck.enqueue("alpha6", 3);
    dequeueCheck.enqueue("dan", 3);
    dequeueCheck.enqueue("alpha7", 4);
    dequeueCheck.enqueue("lewis", 5);
    dequeueCheck.enqueue("alpha8", 6);
    dequeueCheck.enqueue("danny", 7);
    dequeueCheck.enqueue("Muhammad", 7);
    dequeueCheck.enqueue("Danny", 7);
    EXPECT_EQ(dequeueCheck.Size() == 13, true);
    
    vector<string> valueString = {"alpha", "alpha2", "alpha3", "alpha4", "alpha5", "alpha6", "dan", "alpha7", "lewis", "alpha8", "danny", "Muhammad", "Danny"};
    for (int i = 0; i < valueString.size(); ++i) {
        EXPECT_EQ(dequeueCheck.dequeue() == valueString.at(i), true);
    }

    EXPECT_EQ(dequeueCheck.dequeue() == "", true); // checks if begin() returns null and therefore does not assign valueOut a value and keeps it at an empty string implying there is no node to delete

    dequeueCheck.enqueue("lewis", 5);
    dequeueCheck.enqueue("alpha8", 6);
    dequeueCheck.enqueue("danny", 7);
    dequeueCheck.enqueue("Muhammad", 7);
    dequeueCheck.enqueue("Danny", 7);
    dequeueCheck.enqueue("alpha", 1);
    dequeueCheck.enqueue("alpha2", 1);
    dequeueCheck.enqueue("alpha3", 1);
    dequeueCheck.enqueue("alpha4", 2);
    dequeueCheck.enqueue("alpha5", 2);
    dequeueCheck.enqueue("alpha7", 4);
    dequeueCheck.enqueue("alpha6", 3);
    dequeueCheck.enqueue("dan", 3);

    for (int i = 0; i < valueString.size(); ++i) {
        EXPECT_EQ(dequeueCheck.dequeue() == valueString.at(i), true);
    }

    EXPECT_EQ(dequeueCheck.dequeue() == "", true); // checks if begin() returns null and therefore does not assign valueOut a value and keeps it at an empty string implying there is no node to delete

    priorityqueue<string> emptyQueue;

    EXPECT_EQ(emptyQueue.dequeue() == "", true);

    priorityqueue<int> intTree;
    intTree.enqueue(1, 100);
    intTree.enqueue(2, 85);
    intTree.enqueue(3, 2);
    intTree.enqueue(4, 0);
    intTree.enqueue(4, 2);
    intTree.enqueue(10, 100);
    intTree.enqueue(5, 0);

    vector<int> intTreeValues = {4, 5, 3, 4, 2, 1, 10};
    for (int i = 0; i < intTreeValues.size(); ++i) {
        EXPECT_EQ(intTree.dequeue() == intTreeValues.at(i), true);
    }

}


// tests the Size() function for priorityqueue objects of different data types after doing operations such as operator=, enqueue, dequeue, empty to see if we get a proper size return
TEST(priorityqueue, sizeFunction) {
    priorityqueue<string> sizeString;
    sizeString.enqueue("dan", 2);
    sizeString.enqueue("pete", 3);
    sizeString.enqueue("peter", 2);
    EXPECT_EQ(sizeString.Size(), 3);

    priorityqueue<bool> sizeBool;
    EXPECT_EQ(sizeBool.Size(), 0);

    sizeBool.enqueue(true, 3);
    EXPECT_EQ(sizeBool.Size(), 1);

    EXPECT_EQ(sizeBool.dequeue() == true, true);
    EXPECT_EQ(sizeBool.Size(), 0);

    priorityqueue<string> emptyTree;
    EXPECT_EQ(emptyTree.dequeue() == "", true);
    EXPECT_EQ(emptyTree.Size(), 0);

    priorityqueue<int> intTree;
    intTree.enqueue(1, 100);
    intTree.enqueue(2, 85);
    intTree.enqueue(3, 2);
    intTree.enqueue(4, 0);
    intTree.enqueue(3, 2);
    intTree.enqueue(1, 100);
    intTree.enqueue(4, 0);

    EXPECT_EQ(intTree.Size(), 7);
    intTree.dequeue();
    EXPECT_EQ(intTree.Size(), 6);
    intTree.dequeue();
    EXPECT_EQ(intTree.Size(), 5);
    intTree.dequeue();
    EXPECT_EQ(intTree.Size(), 4);
    intTree.dequeue();
    EXPECT_EQ(intTree.Size(), 3);
    intTree.dequeue();
    EXPECT_EQ(intTree.Size(), 2);
    intTree.dequeue();
    EXPECT_EQ(intTree.Size(), 1);
    intTree.dequeue();
    EXPECT_EQ(intTree.Size(), 0);
    intTree.dequeue();
    EXPECT_EQ(intTree.Size(), 0);
    intTree.enqueue(1, 100);
    EXPECT_EQ(intTree.Size(), 1);
    intTree.dequeue();
    EXPECT_EQ(intTree.Size(), 0);

    priorityqueue<int> intTreeCopy;

    intTreeCopy = intTree;

    EXPECT_EQ(intTreeCopy.Size() == intTree.Size(), true);

    intTreeCopy.enqueue(1, 100);

    EXPECT_EQ(intTreeCopy.Size() == intTree.Size(), false);
    EXPECT_EQ(intTreeCopy == intTree, false);

    intTreeCopy = intTree;

    EXPECT_EQ(intTreeCopy.Size() == intTree.Size(), true);
    EXPECT_EQ(intTreeCopy == intTree, true);

    intTree = intTreeCopy;

    EXPECT_EQ(intTreeCopy.Size() == intTree.Size(), true);
    EXPECT_EQ(intTreeCopy == intTree, true);

    priorityqueue<char> charSize;

    charSize.enqueue('a', 1);
    charSize.enqueue('a', 1);
    charSize.enqueue('a', 1);
    charSize.enqueue('a', 1);
    charSize.enqueue('a', 1);

    EXPECT_EQ(charSize.Size(), 5);

    charSize.dequeue();
    EXPECT_EQ(charSize.Size(), 4);

    charSize.dequeue();
    EXPECT_EQ(charSize.Size(), 3);

    charSize.dequeue();
    EXPECT_EQ(charSize.Size(), 2);

    charSize.dequeue();
    EXPECT_EQ(charSize.Size(), 1);

    charSize.dequeue();
    EXPECT_EQ(charSize.Size(), 0);

    charSize.dequeue();
    EXPECT_EQ(charSize.Size(), 0);
}


// tests the toString() function with various data types for the priorityqueue objects after doing operations such as operator=, enqueue, dequeue, empty to see if we get a proper string return and this also helps us see if our nodes are attached properly in our tree
TEST(priorityqueue, toStringFunction) {
    priorityqueue<string> toStringObject;
    toStringObject.enqueue("ali", 3);
    toStringObject.enqueue("omar", 6);
    toStringObject.enqueue("steve", 2);
    toStringObject.enqueue("aete", 2);
    EXPECT_EQ(toStringObject.toString(), "2 value: steve\n2 value: aete\n3 value: ali\n6 value: omar\n");
    toStringObject.dequeue();
    EXPECT_EQ(toStringObject.toString(), "2 value: aete\n3 value: ali\n6 value: omar\n");
    toStringObject.dequeue();
    EXPECT_EQ(toStringObject.toString(), "3 value: ali\n6 value: omar\n");
    toStringObject.dequeue();
    EXPECT_EQ(toStringObject.toString(), "6 value: omar\n");

    priorityqueue<char> toStringObject2;
    toStringObject2.enqueue('a', 1);
    toStringObject2.enqueue('a', 1);
    toStringObject2.enqueue('a', 1);
    toStringObject2.enqueue('a', 1);
    toStringObject2.enqueue('a', 1);
    EXPECT_EQ(toStringObject2.toString(), "1 value: a\n1 value: a\n1 value: a\n1 value: a\n1 value: a\n");
    toStringObject2.dequeue();
    EXPECT_EQ(toStringObject2.toString(), "1 value: a\n1 value: a\n1 value: a\n1 value: a\n");
    toStringObject2.dequeue();
    EXPECT_EQ(toStringObject2.toString(), "1 value: a\n1 value: a\n1 value: a\n");
    toStringObject2.dequeue();
    EXPECT_EQ(toStringObject2.toString(), "1 value: a\n1 value: a\n");
    toStringObject2.dequeue();
    EXPECT_EQ(toStringObject2.toString(), "1 value: a\n");
    toStringObject2.dequeue();
    EXPECT_EQ(toStringObject2.toString(), "");

    priorityqueue<int> toStringObject3;
    toStringObject3.enqueue(2, 1);
    toStringObject3.enqueue(5, 1);
    toStringObject3.enqueue(0, 1);
    toStringObject3.enqueue(-3, 1);
    toStringObject3.enqueue(7, 1);
    EXPECT_EQ(toStringObject3.toString(), "1 value: 2\n1 value: 5\n1 value: 0\n1 value: -3\n1 value: 7\n");
    toStringObject3.dequeue();
    EXPECT_EQ(toStringObject3.toString(), "1 value: 5\n1 value: 0\n1 value: -3\n1 value: 7\n");
    toStringObject3.dequeue();
    EXPECT_EQ(toStringObject3.toString(), "1 value: 0\n1 value: -3\n1 value: 7\n");
    toStringObject3.dequeue();
    EXPECT_EQ(toStringObject3.toString(), "1 value: -3\n1 value: 7\n");
    toStringObject3.dequeue();
    EXPECT_EQ(toStringObject3.toString(), "1 value: 7\n");
    toStringObject3.dequeue();
    EXPECT_EQ(toStringObject3.toString(), "");

    priorityqueue<bool> toStringObject4;
    toStringObject4.enqueue(1, 1);
    toStringObject4.enqueue(1, 1);
    toStringObject4.enqueue(0, 1);
    toStringObject4.enqueue(0, 1);
    toStringObject4.enqueue(0, 1);
    EXPECT_EQ(toStringObject4.toString(), "1 value: 1\n1 value: 1\n1 value: 0\n1 value: 0\n1 value: 0\n");
    toStringObject4.dequeue();
    EXPECT_EQ(toStringObject4.toString(), "1 value: 1\n1 value: 0\n1 value: 0\n1 value: 0\n");
    toStringObject4.dequeue();
    EXPECT_EQ(toStringObject4.toString(), "1 value: 0\n1 value: 0\n1 value: 0\n");
    toStringObject4.dequeue();
    EXPECT_EQ(toStringObject4.toString(), "1 value: 0\n1 value: 0\n");
    toStringObject4.dequeue();
    EXPECT_EQ(toStringObject4.toString(), "1 value: 0\n");
    toStringObject4.dequeue();
    EXPECT_EQ(toStringObject4.toString(), "");
}


// tests the clear() function for priorityqueue objects of different data types after doing operations such as operator=, enqueue, dequeue, empty to see whether or not we clear our tree of everything and update variables
TEST(priorityqueue, clear) {
    priorityqueue<string> hello4;
    priorityqueue<string> hello5;
    hello4.enqueue("ali", 3);
    hello5.enqueue("ali", 3);
    hello4.enqueue("dan", 2);
    hello5.enqueue("dan", 2);
    hello4.enqueue("smith", 2);
    hello5.enqueue("smith", 2);
    hello4.enqueue("ice", 6);
    hello5.enqueue("ice", 6);
    hello4.enqueue("blue", 1);
    hello5.enqueue("blue", 1);
    EXPECT_EQ(hello4 == hello5, true);
    hello4.clear();
    EXPECT_EQ(hello4.getRoot(), nullptr);
    EXPECT_EQ(hello4.Size(), 0);
    EXPECT_EQ(hello5.Size(), 5);
    EXPECT_EQ(hello5.toString() == "1 value: blue\n2 value: dan\n2 value: smith\n3 value: ali\n6 value: ice\n", true);
    EXPECT_EQ(hello4.toString() == "", true);
    EXPECT_EQ(hello4 == hello5, false);

    priorityqueue<bool> hello;
    priorityqueue<bool> hello1;
    hello.clear();
    EXPECT_EQ(hello == hello1, true);
    hello1.clear();
    EXPECT_EQ(hello == hello1, true);
}


// tests the operator== function for priorityqueue objects of different data types after doing operations such as operator=, enqueue, dequeue, empty to see if we properly check if two objects contain the exact same contents
TEST(priorityqueue, operatorEquality) {
    priorityqueue<string> hello6;
    priorityqueue<string> hello7;
    hello6.enqueue("ali", 3);
    hello6.enqueue("omar", 6);
    hello6.enqueue("steve", 2);
    hello6.enqueue("aete", 2);
    hello7.enqueue("man", 1);
    hello7 = hello6;
    EXPECT_EQ(hello6 == hello7, true);

    priorityqueue<char> hello8;
    priorityqueue<char> hello9;
    hello8.enqueue('a', 1);
    hello8.enqueue('a', 1);
    hello8.enqueue('a', 1);
    hello8.enqueue('a', 1);
    hello8.enqueue('a', 1);
    hello9 = hello8;
    EXPECT_EQ(hello9 == hello8, true);

    priorityqueue<int> hello10;
    priorityqueue<int> hello11;

    hello10 = hello11;
    EXPECT_EQ(hello10 == hello11, true);

    priorityqueue<int> hello12;
    priorityqueue<int> hello13;

    hello12.enqueue(1,2);
    hello13.enqueue(1,2);
    hello12.enqueue(2,3);
    hello13.enqueue(2,3);

    hello12 = hello13;
    EXPECT_EQ(hello12 == hello13, true);
}


// tests the begin() and next() function for priorityqueue objects of different data types after doing operations such as operator=, enqueue, dequeue, empty to see if we get the proper lowest priority in our tree as well as every node after that in all cases
TEST(priorityqueue, beginAndNext) {
    priorityqueue<string> hello9;
    string value = "";
    int priority = 0;

    hello9.enqueue("alpha", 1);
    hello9.enqueue("alpha2", 1);
    hello9.enqueue("alpha3", 1);
    hello9.enqueue("alpha4", 2);
    hello9.enqueue("alpha5", 2);
    hello9.enqueue("alpha6", 3);
    hello9.enqueue("dan", 3);
    hello9.enqueue("alpha7", 4);
    hello9.enqueue("lewis", 5);
    hello9.enqueue("alpha8", 6);
    hello9.enqueue("danny", 7);
    hello9.begin();

    EXPECT_EQ(hello9.next(value, priority), true); 
    EXPECT_EQ(hello9.next(value, priority), true);
    EXPECT_EQ(hello9.next(value, priority), true);
    EXPECT_EQ(hello9.next(value, priority), true);
    EXPECT_EQ(hello9.next(value, priority), true);
    EXPECT_EQ(hello9.next(value, priority), true);
    EXPECT_EQ(hello9.next(value, priority), true);
    EXPECT_EQ(hello9.next(value, priority), true);
    EXPECT_EQ(hello9.next(value, priority), true);
    EXPECT_EQ(hello9.next(value, priority), true);
    EXPECT_EQ(hello9.next(value, priority), false);
    EXPECT_EQ(hello9.next(value, priority), false);

    priorityqueue<int> hello10;
    int valueInt = 0;
    hello10.enqueue(1, 100);
    hello10.enqueue(2, 85);
    hello10.enqueue(3, 2);
    hello10.enqueue(4, 0);
    hello10.enqueue(3, 2);
    hello10.enqueue(1, 100);
    hello10.enqueue(4, 0);

    hello10.begin();

    EXPECT_EQ(hello10.next(valueInt, priority), true); 
    EXPECT_EQ(hello10.next(valueInt, priority), true);
    EXPECT_EQ(hello10.next(valueInt, priority), true);
    EXPECT_EQ(hello10.next(valueInt, priority), true);
    EXPECT_EQ(hello10.next(valueInt, priority), true);
    EXPECT_EQ(hello10.next(valueInt, priority), true);
    EXPECT_EQ(hello10.next(valueInt, priority), false);
    EXPECT_EQ(hello10.next(valueInt, priority), false);
    EXPECT_EQ(hello10.next(valueInt, priority), false);
    EXPECT_EQ(hello10.next(valueInt, priority), false);
    EXPECT_EQ(hello10.next(valueInt, priority), false);
    EXPECT_EQ(hello10.next(valueInt, priority), false);

    priorityqueue<char> hello11;
    char valueChar = 'b';
    hello11.enqueue('a', 1);
    hello11.enqueue('a', 1);
    hello11.enqueue('a', 1);
    hello11.enqueue('a', 1);
    hello11.enqueue('a', 1);

    hello11.begin();

    EXPECT_EQ(hello11.next(valueChar, priority), true);
    EXPECT_EQ(hello11.next(valueChar, priority), true);
    EXPECT_EQ(hello11.next(valueChar, priority), true);
    EXPECT_EQ(hello11.next(valueChar, priority), true);
    EXPECT_EQ(hello11.next(valueChar, priority), false);
    EXPECT_EQ(hello11.next(valueChar, priority), false);
    EXPECT_EQ(hello11.next(valueChar, priority), false);
    EXPECT_EQ(hello11.next(valueChar, priority), false);

    priorityqueue<bool> hello12;
    bool valueBool = false;

    hello12.begin();

    EXPECT_EQ(hello12.next(valueBool, priority), false);
    EXPECT_EQ(hello12.next(valueBool, priority), false);
    EXPECT_EQ(hello12.next(valueBool, priority), false);
    EXPECT_EQ(hello12.next(valueBool, priority), false);
    EXPECT_EQ(hello12.next(valueBool, priority), false);
    EXPECT_EQ(hello12.next(valueBool, priority), false);
    EXPECT_EQ(hello12.next(valueBool, priority), false);
}


// tests the peek() function for priorityqueue objects of different data types after doing operations such as operator=, enqueue, dequeue, empty to see if we get the correct object at the lowest priority in the tree and get it returned with the correct value
TEST(priorityqueue, peek) {
    priorityqueue<string> hello9;

    hello9.enqueue("alpha", 1);
    hello9.enqueue("alpha2", 1);
    hello9.enqueue("alpha3", 1);
    hello9.enqueue("alpha4", 2);
    hello9.enqueue("alpha5", 2);
    hello9.enqueue("alpha6", 3);
    hello9.enqueue("dan", 3);
    hello9.enqueue("alpha7", 4);
    hello9.enqueue("lewis", 5);
    hello9.enqueue("alpha8", 6);
    hello9.enqueue("danny", 7);
    hello9.enqueue("Muhammad", 7);

    EXPECT_EQ(hello9.peek(), "alpha");
    hello9.dequeue();
    EXPECT_EQ(hello9.peek(), "alpha2");
    hello9.dequeue();
    EXPECT_EQ(hello9.peek(), "alpha3");
    hello9.dequeue();
    EXPECT_EQ(hello9.peek(), "alpha4");
    hello9.dequeue();
    EXPECT_EQ(hello9.peek(), "alpha5");
    hello9.dequeue();
    EXPECT_EQ(hello9.peek(), "alpha6");
    hello9.dequeue();
    EXPECT_EQ(hello9.peek(), "dan");
    hello9.dequeue();
    EXPECT_EQ(hello9.peek(), "alpha7");
    hello9.dequeue();
    EXPECT_EQ(hello9.peek(), "lewis");
    hello9.dequeue();
    EXPECT_EQ(hello9.peek(), "alpha8");
    hello9.dequeue();
    EXPECT_EQ(hello9.peek(), "danny");
    hello9.dequeue();
    EXPECT_EQ(hello9.peek(), "Muhammad");
    hello9.dequeue();
    EXPECT_EQ(hello9.peek(), "");
    hello9.dequeue();
    EXPECT_EQ(hello9.peek(), "");

    priorityqueue<string> hello111;
    EXPECT_EQ(hello111.peek(), "");

    priorityqueue<char> hello11;
    hello11.enqueue('a', 1);
    hello11.enqueue('a', 1);
    hello11.enqueue('a', 1);
    hello11.enqueue('a', 1);
    hello11.enqueue('a', 1);

    EXPECT_EQ(hello11.peek(), 'a');
    hello11.dequeue();
    EXPECT_EQ(hello11.peek(), 'a');
    hello11.dequeue();
    EXPECT_EQ(hello11.peek(), 'a');
    hello11.dequeue();
    EXPECT_EQ(hello11.peek(), 'a');
    hello11.dequeue();
    EXPECT_EQ(hello11.peek(), 'a');
    hello11.dequeue();

    priorityqueue<int> hello10;
    hello10.enqueue(1, 100);
    hello10.enqueue(2, 85);
    hello10.enqueue(3, 2);
    hello10.enqueue(4, 0);
    hello10.enqueue(3, 2);
    hello10.enqueue(1, 100);
    hello10.enqueue(4, 0);

    EXPECT_EQ(hello10.peek(), 4);
    hello10.dequeue();
    EXPECT_EQ(hello10.peek(), 4);
    hello10.dequeue();
    EXPECT_EQ(hello10.peek(), 3);
    hello10.dequeue();
    EXPECT_EQ(hello10.peek(), 3);
    hello10.dequeue();
    EXPECT_EQ(hello10.peek(), 2);
    hello10.dequeue();
    EXPECT_EQ(hello10.peek(), 1);
    hello10.dequeue();
    EXPECT_EQ(hello10.peek(), 1);
    hello10.dequeue();
}
