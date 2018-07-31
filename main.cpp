#include "FibonacciHeap.h"
#include <iostream>
#include <fstream>

using namespace std;

void printMenu()
{
  cout << "What simple operation would you like to perform?\n" <<
  "1) Insert a number\n" <<
  "2) Insert multiple numbers by file\n" <<
  "3) Peek the minimum\n" <<
  "4) Delete the minimum\n" <<
  "5) Delete a node\n" <<
  "6) Print the Fibonacci Heap\n" <<
  "7) Quit\n";
}


int main()
{
  cout << "Welcome to the test program for the Fibonacci Heap. This code is written for testing using integers, but the heap should support all pre-defined c++ data types.\n";
  FibonacciHeap<int> h1;
  int choice = 0;
  int insertion;
  string fileName;
  ifstream din;
  int nodeVal;
  bool quit = false;

  while(!quit)
  {
    printMenu();
    cin >> choice;

    switch(choice)
    {
        case 1:
          cout << "Enter a number to insert: ";
          cin >> insertion;
          h1.Insert(insertion);
          break;

        case 2:
          cout << "Enter the name of the file to read from (int only): ";
          cin >> fileName;
          din.open(fileName.c_str());
          while(din >> insertion)
            h1.Insert(insertion);
          din.close();
          break;

        case 3:
          cout << "The minimum is:\n";
          cout << h1.peekMin() << endl;
          break;

        case 4:
          cout << "Deleting the minimum value.\n";
          h1.extractMin();
          break;

        case 5:
          cout << "Which node would you like to delete?\n";
          cin >> nodeVal;
          h1.Delete(nodeVal);
          break;

        case 6:
          cout << "Printing Fibonacci Heap:\n";
          h1.print();
          break;

        case 7:
          quit = true;
          cout << "\nExiting.\n";
          break;

        default:
          cout << "Invalid choice.\n";
          break;
    }
  }
  return 0;
}
