/**
* \file aghVector.h
* \author Filip Pasternak
* \date 22.05.2013
* \brief Definition of class template aghVector which extends aghContainer class template.
*/
// -------------------------------------------------------------------------
#ifndef AGHVECTOR_H
#define AGHVECTOR_H
 
#include <iostream>
#include "aghContainer.h"
#include "aghException.h"
 
using namespace std;
 
/**
* \class template aghVector
* \author Filip Pasternak
* \date 22.05.2013
* \brief Definition of class template aghVector which extends aghContainer class template.
*/
template <class T>
class aghVector : public aghContainer<T>{
     private:
          T* values; ///< Pointer to stored elements
          int elementsCount;  ///< Number of elements
     public:
 
     //\brief The class constructor
     //
     //\param _size - number of elements to store
     aghVector(int _size = 0);
 
     //\brief The copying contructor.
     //
     //\param _source - source object
     aghVector(const aghContainer<T>& _source);
 
     //\brief The class destructor
     ~aghVector();
 
     //\brief Function to return value of given element.
     //
     //\param id - id of element
     //\return value of element on id position
     T& at(int _id) const;
 
     //\brief Function to check ammount of elements
     //
     //\return ammount of elements in vector
     int size(void) const;
 
     //\brief Function to insert element
     //
     //\param id - id of place for element
     //\param element - value to set
     //\return TRUE if the place is correct
     bool insert(int _id, T const& _element);
 
     //\brief Function to delete element
     //
     //\param id - id of element
     //\return TRUE if removed successfully
     bool remove(int _id);
 
     //\brief Function to move elements from one table to another (temp)
     //
     //\param _size - size of source table
     //\param _elements - source table
     //\param _id - place where we want to add new / from where we want to remove element
     //\param _erease - function mode (making space for new element / removing element)
     //\return new table of elements
     T* move(T* _elements, int _id, bool _erease = false);
 
     //\brief Overload of operator=
     //
     //\param - source aghVector<T> object
     //\return reference to 'this' object
     aghVector<T>& operator=(aghVector<T> const& _right);
};
 
template <typename T>
aghVector<T>::aghVector(int _size){
    if(_size > 0){
        values = new T[_size];
        elementsCount = _size;
    }else{
        values = NULL;
        elementsCount = 0;
    }
}
 
template <typename T>
aghVector<T>::aghVector(const aghContainer<T>& _source){
     values = new T[_source.size()];
     elementsCount = _source.size();
     for(int i=0; i<elementsCount; i++){
          *(values+i) = _source[i];
     }
}
 
template <typename T>
aghVector<T>::~aghVector(){
    delete [] values;
}
 
template <typename T>
T& aghVector<T>::at(int _id) const{
     if(_id < 0 || _id >= elementsCount){
          throw aghException(0, "Index out of range", __FILE__, __LINE__);
     }else{
          return *(values+_id);
     }    
}
 
template <typename T>
int aghVector<T>::size(void) const{
    return elementsCount;
}
 
template <typename T>
bool aghVector<T>::insert(int _id, T const& _element){
    if(_id < 0 || _id > elementsCount){
        return false;
    }else{
        T* temp = move(values, _id);
        *(temp+_id) = _element;
        values = temp;
        elementsCount++;
        return true;
    }
}
 
template <typename T>
bool aghVector<T>::remove(int _id){
     if(_id < 0 || _id >= elementsCount){
          return false;
     }else{
          T* temp = move(values, _id, true);
          values = temp;
          elementsCount--;
          return true;
     }
}
 
template <typename T>
aghVector<T>& aghVector<T>::operator=(aghVector<T> const& _right){
     if(this != &_right){
          this->clear();
          for(int i = 0; i < _right.size(); i++){
               this->append(_right[i]);
          }
     }
     return *this;
}
 
template <typename T>
T* aghVector<T>::move(T* _elements, int _id, bool _erease){
    T* temp;
    int newSize, i=0, j=0;
 
    if(!_erease){
        newSize = elementsCount+1;
    }else{
        newSize = elementsCount-1;
    }
    temp = new T[newSize];
 
    while(i < newSize){        
        if(_erease && j == _id){
             j++;
        }else if(!_erease && i == _id){
             i++;
        }else{
             *(temp+i) = *(_elements+j);
             i++;
             j++;
        }
    }
    delete [] _elements;
    return temp;
}
#endif
