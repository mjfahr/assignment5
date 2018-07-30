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

<<<<<<< HEAD
  h1.Insert(4);
  h1.Insert(10);
  h1.Insert(5);
  h1.Insert(7);

  //h1.print();
  //cout << "h1: Smallest: " << h1.peekMin() << endl;

  h2.Insert(3);
  h2.Insert(6);
  h2.Insert(1);
  h2.Insert(25);

  //h2.print();
  //cout << "h2: Smallest: " << h2.peekMin() << endl;
=======
  int choice = 0;
  int insertion;
  string fileName;
  ifstream din;

  while(choice != 5)
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
          break;

        default:
          cout << "Invalid choice.\n";
          break;
    }
  }
>>>>>>> 3dad7b53506faf4d06f36a3b44102b163b262f33

  FibonacciHeap<int> h3 = FibonacciHeap<int>::Merge(h1, h2);
  cout << "h3: " << endl;
  h3.print();


  // FibonacciHeap<int> h4 = h1;
  // cout << "h4: " << endl;
  // h4.print();
  // cout << endl;
  //
  // FibonacciNode<int>* n1 = h1.getNode(5);
  // h1.decreaseKey(n1, 2);
  // cout << h1.peekMin() << endl;

  return 0;
}
