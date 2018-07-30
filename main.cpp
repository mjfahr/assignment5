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
  "5) Print the Fibonacci Heap\n" <<
  "6) Quit\n";
}


int main()
{
  FibonacciHeap<int> h1;
  FibonacciHeap<int> h2;

  int choice = 0;
  int insertion;
  string fileName;
  ifstream din;

  while(choice != 6)
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
          din.open(fileName);
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
          cout << "Printing Fibonacci Heap:\n";
          h1.print();
          break;

        case 6:
          cout << "\nExiting.\n";
          break;

        default:
          cout << "Invalid choice.\n";
          break;
    }
  }

  FibonacciHeap<int> h3 = h1 + h2;
  cout << "h3: " << endl;
  h3.print();


  FibonacciHeap<int> h4 = h1;
  cout << "h4: " << endl;
  h4.print();
  cout << endl;

  FibonacciNode<int>* n1 = h1.getNode(5);
  h1.decreaseKey(n1, 2);
  cout << h1.peekMin() << endl;

  return 0;
}
