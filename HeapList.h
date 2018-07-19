template <class T>
class HLNode
{
  Heap<T>* heap;
  Heap<T>* left;
  Heap<T>* right;
}

class HeapList
{
public:
  HLNode<T>* smallest;
  void print() const;

private:
  void addHeap(Heap<T>* newHeap);
  void printHelper(HeapNode<T>* current) const;

}

//addHeap: Private: Adds a new heap to the circular, doubly-linked list of heaps.
template <class T>
void HeapList<T>::addHeap(Heap<T>* newHeap)
{
  if (!isEmpty())
  {
    // Insert new heap into list, to the right of smallest (arbitrary choice)
    newHeap->right = smallest->right;
    newHeap->left = smallest;

    newHeap->right->left = newHeap;
    smallest->right = newHeap;

    // Move smallest pointer if necessary
    if (smallest->root->value > newHeap->root->value)
      smallest = newHeap;
  }
  else // Fibonacci heap is empty, first value is the smallest.
  {
    smallest = newHeap;
    // Create circular linking
    smallest->right = smallest;
    smallest->left = smallest;
  }
}

//print: public: prints all the values of the fibonacci heap, one sub-heap at a time -- starting with smallest.
template <class T>
void HeapList<T>::print() const
{
  Heap<T>* ptr = smallest;

  do
  {
    printHelper(ptr->root);
    cout << endl;
    ptr = ptr->right;
  } while (ptr != smallest);
}

template <class T>
void HeapList<T>::printHelper(HeapNode<T>* current) const
{
  cout << current->value << " ";
  for (HeapNode<T>* node : current->children)
    printHelper(node);
}
