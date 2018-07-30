/*
Copyright (C) 2018  Michael Fahr, Adam Goertz, Alec Ray

This program is free software: you may redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but without any guarantee of its fitness for any particular purpose. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>

*/

#ifndef FIBONACCIHEAP_H
#define FIBONACCIHEAP_H

#include <limits>
#include <iostream>
#include "FibonacciNode.h"

using namespace std;

template <class T>
class FibonacciHeap
{
public:
  FibonacciHeap();
  FibonacciHeap(FibonacciNode<T>* node);
  FibonacciHeap(const FibonacciHeap<T>& other);
  ~FibonacciHeap();

  void Insert(const T _value);

  T peekMin() { return smallest->value; }
  void extractMin();
  FibonacciNode<T>* getNode(const T _value);

  bool decreaseKey(FibonacciNode<T>* node, T newKey);
  void Delete(FibonacciNode<T>* node);
  void addChild(FibonacciNode<T>* _parent, FibonacciNode<T>* _child);

  static FibonacciHeap<T> Merge(const FibonacciHeap<T>& one, const FibonacciHeap<T>& other);
  FibonacciHeap<T> operator+(FibonacciHeap<T>& other) { return Merge(*this, other); }
  FibonacciHeap<T> operator=(const FibonacciHeap<T>& other) { return new FibonacciHeap<T>(other); }

  bool isEmpty() { return smallest == nullptr; }
  void print();

private:
  void copyHelper(FibonacciNode<T>* node);
  void destructHelper(FibonacciNode<T>* node);
  void printHelper(FibonacciNode<T>* root) const;
  FibonacciNode<T>* getNodeHelper(const T _value, FibonacciNode<T>* node);

  int getRank(FibonacciNode<T>* node);
  void setSmallest();
  void addNode(FibonacciNode<T>* newNode);

  void cut(FibonacciNode<T>* ndoe);
  void cascadingCut(FibonacciNode<T>* node);

  FibonacciNode<T>* smallest;
  int numNodes;
  T MIN; // Smallest possible value for a node in the heap, generally defined for numeric types only.

};

template <class T>
FibonacciHeap<T>::FibonacciHeap()
{
  smallest = nullptr;
  numNodes = 0;
  //Set the minimum possible value for any node (used to simplify code for deleting a node) NOTE: only works for numeric types
  if (numeric_limits<T>::is_specialized)
     MIN = numeric_limits<T>::lowest();
}

template <class T>
FibonacciHeap<T>::FibonacciHeap(FibonacciNode<T>* node)
{
  smallest = node;
  smallest->right = node;
  smallest->left = node;
  numNodes = 1;
  //Set the minimum possible value for any node (used to simplify code for deleting a node) NOTE: only works for numeric types
  if (numeric_limits<T>::is_specialized)
     MIN = numeric_limits<T>::lowest();
}

//copy constructor: creates a copy by appending all nodes in other heap to root list of new heap. Does not preserve heap topology.
template <class T>
FibonacciHeap<T>::FibonacciHeap(const FibonacciHeap<T>& other)
{
  smallest = nullptr;
  numNodes = 0;
  if (numeric_limits<T>::is_specialized)
     MIN = numeric_limits<T>::lowest();

  copyHelper(other.smallest);
}

template <class T>
void FibonacciHeap<T>::copyHelper(FibonacciNode<T>* node)
{
  if (node != nullptr)
  {
    FibonacciNode<T>* ptr = node;
    const FibonacciNode<T>* init = ptr;

    do
    {
      Insert(ptr->value);

      copyHelper(ptr->child);

      ptr = ptr->right;

    } while(ptr != init);
  }
}

template <class T>
FibonacciHeap<T>::~FibonacciHeap()
{
  destructHelper(smallest);
}

// destructHelper: private: recusive helper function for destructor
template <class T>
void FibonacciHeap<T>::destructHelper(FibonacciNode<T>* node)
{
  FibonacciNode<T>* current = node;
  FibonacciNode<T>* next = node;

  if (current != nullptr)
  {
    do
    {
      current = next;
      destructHelper(current->child);
      next = current->right;
      delete current;

    } while(next != node);
  }
}

//Insert: Public: Allows for the easy ( O(1) ) insertion of a value by adding a new heap to the root list.
template <class T>
void FibonacciHeap<T>::Insert(const T _value)
{
  FibonacciNode<T>* newNode = new FibonacciNode<T>(_value);
  // Insert the new node into the root list of the heap
  addNode(newNode);
}

//addHeap: Private: Adds a new heap to the root list.
template <class T>
void FibonacciHeap<T>::addNode(FibonacciNode<T>* newNode)
{
  if (!isEmpty())
  {
    // Insert new heap into list, to the right of smallest (arbitrary choice)
    newNode->right = smallest->right;
    newNode->left = smallest;

    newNode->right->left = newNode;
    smallest->right = newNode;

    // Move smallest pointer if necessary
    if (smallest->value > newNode->value)
      smallest = newNode;
  }
  else // Fibonacci heap is empty, first value is the smallest.
  {
    smallest = newNode;
    // Create circular linking
    smallest->right = smallest;
    smallest->left = smallest;
  }
  numNodes++;
}

template <class T>
void FibonacciHeap<T>::addChild(FibonacciNode<T>* _parent, FibonacciNode<T>* _child)
{
    if(_parent->child == nullptr)
    {
        _parent->child = _child;
        _child->right = _child;
        _child->left = _child;
    }
    else
    {
        _child->right = _parent->child->right;
        _child->left = _parent->child;
        _parent->child->right->left = _child;
        _parent->child->right = _child;
    }
}

//deleteMin: Public: Removes the minimum value of the heap, a.k.a the root of 'smallest'. This removes ONLY the root, not the entire heap.
template <class T>
void FibonacciHeap<T>::extractMin()
{
  if (!isEmpty())
  {
    // Add smallest's children to the top level of the heap
    if (smallest->child != nullptr)
    {
      FibonacciNode<T>* ptr = smallest->child;
      FibonacciNode<T>* next = smallest->child;
      do
      {
        next = ptr->right; // store the next child to be processed, as ptr->right will change in addNode(ptr).
        addNode(ptr);
        ptr = next;
      } while(ptr != smallest->child);
    }

    // Remove smallest from the heap and reconnect doubly linked list
    if (smallest != smallest->right) // smallest is not the only node
    {
      smallest->left->right = smallest->right;
      smallest->right->left = smallest->left;

      // delete smallest
      FibonacciNode<T>* toDel = smallest;
      smallest = smallest->right; // set new smallest to be the right sibling of the current smallest (arbitrary choice), will be changed later.
      delete toDel;



      // TODO: Consolidate nodes on the top level so that no two nodes have the same rank (# of children)
      FibonacciNode<T>* move;
      FibonacciNode<T>** ranks = new FibonacciNode<T>*[numNodes];
      for(int i = 0; i <= 5; i++)
          ranks[i] = NULL;

      ranks[smallest->rank] = smallest;
      bool flag = false;


      move = smallest->right;
      do
      {

          //If move doesn't match ranks with anything, add it to the array at its
          //correct rank position
          if(ranks[move->rank] == NULL)
          {
              ranks[move->rank] = move;
              move = move->right;
          }

              //If it does match
          else
          {
              //Find the greater value
              if(move->value > ranks[move->rank]->value)
              {
                  //Removes node with same rank from Heap
                  ranks[move->rank]->left->right = ranks[move->rank]->right;
                  ranks[move->rank]->right->left = ranks[move->rank]->left;

                  //Moves node with same rank to position of move and updates
                  //pointers around it
                  ranks[move->rank]->left = move->left;
                  ranks[move->rank]->right = move->right;
                  ranks[move->rank]->left->right = ranks[move->rank];
                  ranks[move->rank]->right->left = ranks[move->rank];

                  //Clears left and right since no pointers are beside it
                  move->left = nullptr;
                  move->right = nullptr;

                  //Adds smaller valued node as parent
                  move->parent = ranks[move->rank];

                  //Adds child to smaller node
                  addChild(ranks[move->rank], move);


                  //Return back to the top level
                  ranks[move->rank]->rank++;
                  ranks[move->rank] = NULL;
                  move = move->parent;
              }
              else
              {
                  //Removes node with same rank from Heap
                  ranks[move->rank]->left->right = ranks[move->rank]->right;
                  ranks[move->rank]->right->left = ranks[move->rank]->left;

                  ranks[move->rank]->left = nullptr;
                  ranks[move->rank]->right = nullptr;

                  ranks[move->rank]->parent = move;
                  addChild(move, ranks[move->rank]);

                  move->rank++;
                  ranks[move->rank] = NULL;

              }
          }


          if(move == smallest->left)
              flag = true;



      } while(move != smallest->right || flag == false || ranks[smallest->rank] != smallest);
      //delete []ranks;

      // find the new smallest node
      setSmallest();



    }
    else
    {
      delete smallest;
      smallest = nullptr;
    }
    numNodes--;
  }
}

//getNode: public: returns a pointer to a node in the heap, for use in the decreaseKey and delete functions.
template <class T>
FibonacciNode<T>* FibonacciHeap<T>::getNode(const T _value)
{
  return getNodeHelper(_value, smallest);
}

template <class T>
FibonacciNode<T>* FibonacciHeap<T>::getNodeHelper(const T _value, FibonacciNode<T>* node)
{
  if (node != nullptr)
  {
    FibonacciNode<T>* ptr = node;
    const FibonacciNode<T>* init = ptr;

    do
    {
      if (ptr->value == _value)
        return ptr;

      else
      {
        FibonacciNode<T>* res = getNodeHelper(_value, ptr->child);

        if (res != nullptr)
          return res;

        ptr = ptr->right;
      }

    } while(ptr != init);
  }
  return nullptr;
}


//setSmallest: private: used to find the new min after a deleteMin call
template <class T>
void FibonacciHeap<T>::setSmallest()
{

  if (!isEmpty())
  {
    FibonacciNode<T>* ptr = smallest->right;
    FibonacciNode<T>* init = smallest; // Used to keep track of where we started, since smallest will change.

    while (ptr != init)
    {
      if (ptr->value < smallest->value)
        smallest = ptr;

      ptr = ptr->right;
    }
  }
}

template <class T>
void FibonacciHeap<T>::cut(FibonacciNode<T>* node)
{
  // If the child has siblings
  if (node->right != node)
  {
    //reconnect the circular list of siblings
    node->left->right = node->right;
    node->right->left = node->left;


    // if the parent of node points to node as a child, change the child pointer
    if (node->parent->child == node)
      node->parent->child = node->right;
  }

  // decrease the degree/rank of the parent, since we removed a child
  node->parent->rank--;
  node->marked = false;

  addNode(node);

}

template <class T>
void FibonacciHeap<T>::cascadingCut(FibonacciNode<T>* node)
{
  if (node->parent != nullptr)
  {
    if (node->parent->marked == false)
      node->parent->marked = true;
    else
    {
      cut(node);
      cascadingCut(node->parent);
    }
  }
}

//decreaseKey: public: reduces the value of a node by the specified amount, preserves heap ordering
template <class T>
bool FibonacciHeap<T>::decreaseKey(FibonacciNode<T>* node, T newKey)
{
  // if the new value does not decrease the key of the node
  if (newKey > node->value)
    return false;
  else
  {
    node->value = newKey;

    // if the heap order is violated and the node is not a member of the root list, restore the heap order
    if (node->parent != nullptr && node->parent->value > node->value)
    {
      cut(node);
      cascadingCut(node->parent);
    }

    if (node->value < smallest->value)
      smallest = node;

    return true;
  }
}

template <class T>
void FibonacciHeap<T>::Delete(FibonacciNode<T>* node)
{
  // decrease key of node to MIN
  decreaseKey(node, MIN);
  // deleteMin()
}

//Merge: public: combines two fibonacci heaps into one by splicing together their top-level nodes. the two heaps are not deleted, but should not be used after calling this function.
// NOTE: Alternatively, we could create a copy constructor and create an entirely new heap containing the same node values.
// This would reduce the likelihood of bugs occuring if the original heaps are reused, but it would be slower and less memory-efficient.
template <class T>
FibonacciHeap<T> FibonacciHeap<T>::Merge(const FibonacciHeap<T>& one, const FibonacciHeap<T>& other)
{
  FibonacciHeap<T>* first = new FibonacciHeap<T>(one);
  FibonacciHeap<T>* second = new FibonacciHeap<T>(other);
  // Link the two heaps
  first->smallest->right->left = second->smallest->left;
  second->smallest->left->right = first->smallest->right;

  first->smallest->right = second->smallest;
  second->smallest->left = first->smallest;

  // Set the smallest node
  first->smallest = (first->smallest->value <= second->smallest->value ? first->smallest : second->smallest);

  return *first;
}


//getRank: private: return the number of children of a node.
template <class T>
int FibonacciHeap<T>::getRank(FibonacciNode<T>* node)
{
  int rank = 0;
  FibonacciNode<T>* init = node->child;

  if (init != nullptr)
  {
    FibonacciNode<T>* ptr = init->right;
    rank++;

    while (ptr != init)
    {
      rank++;
      ptr = ptr->right;
    }
  }

  return rank;
}

template <class T>
void FibonacciHeap<T>::print()
{
  FibonacciNode<T>* ptr1 = smallest;
  do
  {
    printHelper(ptr1);
    cout << endl;
    ptr1 = ptr1->right;

  } while(ptr1 != smallest);

}

template <class T>
void FibonacciHeap<T>::printHelper(FibonacciNode<T>* root) const
{
  cout << root->value << " ";

  if (root->child != nullptr)
  {
    FibonacciNode<T>* ptr2 = root->child;

    do
    {
      printHelper(ptr2);
      ptr2 = ptr2->right;
    } while(ptr2 != root->child);
  }
}


#endif
