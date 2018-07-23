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
  bool isEmpty();

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
