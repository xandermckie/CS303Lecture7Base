// CS303Lecture7Base.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "LinkedList.h"

using namespace myList;

int main() {
    LinkedList<int> myStack;

    LinkedList<int> s;
    int n1, n2, n3;
    s.pushFront(17);
    s.pushFront(143);
    s.pushFront(42);
    n1 = s.front();
    s.popFront();
    n2 = s.front();
    s.pushFront(n2);
    n3 = s.front();
    s.popFront();
    n1 = s.front();

    std::cout << n1 << " " << n2 << " " << n3 << "\n";

    try {
        myStack.pushFront(1);
        myStack.pushFront(2);
        myStack.pushFront(3);
        myStack.pushFront(4);
        myStack.pushFront(5);

        while (!myStack.empty()) {
            std::cout << myStack.front() << " ";
            myStack.popFront();
        }
        std::cout << std::endl;
    }
    catch (std::runtime_error& err) {
        std::cout << err.what() << std::endl;
    }

    //Task 1:  Work with 1-2 other people to complete these items:
    //palindrome();
    //decToBinary();

    //Task 2:  Work in the same group & complete one of these items:
    //UndoRedoActions();
    //PostfixEvaluator();
    //InToPostfix();
}
