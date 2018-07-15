#include "distributed.h"
#include <tuple>
#include "cilk.h"
#include <vector>

#pragma once
 
typedef uint64_t IndexType;

template <class ScalarType>
class miniVector 
{
 
private:
  IndexType vCapacity; // amount of available space
  IndexType vSize;     // number of elements in the list
  T *vArr;       // the dynamic array

};
 

T & miniVector<T>::operator [ ] (unsigned int i)
{
  assert ((i >= 0) && (index < vSize));
  return vArr[i];
}



template <typename T>
void miniVector<T>::push_back(const T& item)
{
  // if space is full, allocate more capacity
  if (vSize == vCapacity)
    {
      if (vCapacity == 0)
        // if capacity is 0, set capacity to 1.
        // set copy to false because there are
        // no existing elements
         reserve(1,false);
      else
        // double the capacity
        reserve(2 * vCapacity, true);
    }
  
  // add item to the list, update vSize
  vArr[vSize] = item;
  vSize++;
}



template <typename T>
void miniVector<T>::reserve(int n, bool copy)
{

  int i;
  
  // allocate a new dynamic array with n elements
  
  T *newArr = (long *) mw_localmalloc(n*sizeof(long), &B[2]);

  if (newArr == NULL)
    std::cerr <<"memoryAllocationError(miniVector reserve(): memory allocation failure)";
  
  // if copy is true, copy elements from the old list to the new list
  if (copy)
    for(i = 0; i < vSize; i++)
      newArr[i] = vArr[i];
  
  // delete original dynamic array. if vArr is NULL, the vector was
  // originally empty and there is no memory to delete
  if (vArr != NULL)
    delete [] vArr;
  
  // set vArr to the value newArr. update vCapacity
  vArr = newArr;
  vCapacity = n;
}

 