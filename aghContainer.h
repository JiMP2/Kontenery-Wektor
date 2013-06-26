/**
* \file aghContainer.h
* \author Wojciech Kryscinski
* \date 22.05.2013
* \brief Definition of base class template aghContainer.
*/
 
#ifndef __aghContainer__aghContainer__
#define __aghContainer__aghContainer__
 
#include <iostream>
using namespace std;
 
template <class T>
class aghContainer {
 
public:
     //\brief Class constructor
    aghContainer();
 
     //\brief Class destructor. Virtual method.
    virtual ~aghContainer();
 
     //\brief Method appends new element to end of container.
     //\_element - Element value.
    void append(T const& _element);
 
     //\brief Method appends new element to end of container. Virtual method.
     //\_element - Element value.
     //\return true if operation successful.
    virtual bool insert(int _position, T const& _element) = 0;
 
     //\brief Method replaces element at given position with given value.
     //\_element - new value.
     //\_position - Index of element.
     //\return true if operation successful.
    bool replace(int _position, T const& _element);
 
     //\brief Method returns element from given position. Virtual method.
     //\_position - Index of element.
     //\return value of element at given position.
    virtual T& at(int _position) const = 0;
 
     //\brief Method returns size of container. Virtual method.
     //\return size of container.
    virtual int size(void) const = 0;
 
     //\brief Method removes element at given position. Virual method.
     //\return true if operation successful.
    virtual bool remove(int _position) = 0;
 
     //\brief Method removes all elements of container.
    void clear(void);
 
     //\brief Method checks if container is empty.
    //\return true if container empty.
    bool isEmpty(void);
 
     //\brief Method finds index of element of given value.
     //\_value element value
     //\_from search start point
     //\return index of element
    int indexOf(T const& _value, int _from = 0) const;
 
     //\brief Method checks if container has element of given value.
     //\_element - Element value.
     //\_value element value
     //\_from search start point
     //\return true if value found in container.
    bool contains(T const& _value, int _from = 0) const;
 
     //\brief Overload of operator==.
     //\_right Operand of overloaded operator.
    bool operator==(aghContainer<T> const& _right);
 
     //\brief Overload of operator!=.
     //\_right Operand of overloaded operator.
    bool operator!=(aghContainer<T> const& _right);
 
     //\brief Overload of operator=[].
     //\n Operand of overloaded operator.
    T& operator[](int n) const;
 
     //\brief Overload of operator=.
     //\_right Operand of overloaded operator.
    aghContainer<T>& operator=(aghContainer<T> const& _right);
 
     //\brief Overload of operator+=.
     //\_right Operand of overloaded operator.
    aghContainer<T>& operator+=(aghContainer<T> const& _right);
 
     //\brief Overload of operator+=.
     //\_element Operand of overloaded operator.
    aghContainer<T>& operator+=(T const& _element);
 
     //\brief Overload of operator<<.
     //\_element Operand of overloaded operator.
    aghContainer<T>& operator<<(T const& _element);
 
     //\brief Overload of operator<<.
     //\_right Operand of overloaded operator.
    aghContainer<T>& operator<<(aghContainer<T> const& _right);
 
     //\brief Overload of operator<<.
     //\_output Operand of oveloaded operator.
     //\_right Operand of overloaded operator.
    friend ostream& operator<<(ostream& _output, aghContainer<T> const& _right)
    {
        for (int i = 0; i < _right.size(); i++)
        {
            _output << _right[i] << "\t";
        }
        return _output;
    }
};      
    template <typename T>
    aghContainer<T>::aghContainer()
    {
    }
 
    template <typename T>
    aghContainer<T>::~aghContainer()
    {
    }
    template <class T>
    void aghContainer<T>::append(T const& _element)
    {
        insert(size(), _element);
    }
 
    template <typename T>
    bool aghContainer<T>::replace(int _position, T const& _element)
    {
        if(remove(_position))
        {
               if(insert(_position, _element))
               {
                    return true;
               }
        }
        return false;
    }
 
    template <typename T>
    void aghContainer<T>::clear(void)
    {
        while (size())
        {
            remove(0);
        }
    }
 
    template <typename T>
    bool aghContainer<T>::isEmpty(void)
    {
        if (size())
            return false;
        else
            return true;
    }
 
    template <typename T>
    int aghContainer<T>::indexOf(T const& _value, int _from) const
    {
          for(int i = _from; i<size(); i++)
          {
               if(this->at(i) == _value){
                    return i;
               }
          }
          return -1;
    }
 
    template <typename T>         
    bool aghContainer<T>::contains(T const& _value, int _from) const
    {
          if(indexOf(_value, _from) == -1){
               return false;
          }
          return true;
    }         
 
    template <typename T>
    bool aghContainer<T>::operator==(aghContainer<T> const& _right)
    {
          if(this->size() != _right.size())
          {
               return false;
          }
          else
          {
               for(int i=0;i<size();i++)
               {
                    if(this->at(i) != _right.at(i))
                        return false;
               }
          }
          return true;
    }
 
    template <typename T>
    bool aghContainer<T>::operator!=(aghContainer<T> const& _right)
    {
        return !operator==(_right);
    }
 
    template <typename T>
    aghContainer<T>& aghContainer<T>::operator=(aghContainer<T> const& right)
    {
        if(this != &right){
             this->clear();
 
             for(int i = 0; i < right.size(); i++)
             {
                 this->append(right[i]);
             }
        }              
        return *this;
    }
 
    template <typename T>
    T& aghContainer<T>::operator[](int n) const
    {
        return at(n);
    }
 
    template <typename T>
    aghContainer<T>& aghContainer<T>::operator+=(aghContainer<T> const& _right)
    {
        for (int i = 0; i < _right.size(); i++)
        {
            this->append(_right.at(i));
        }
        return *this;
    }
 
    template <typename T>
    aghContainer<T>& aghContainer<T>::operator+=(T const& _element)
    {
        append(_element);
        return *this;
    }
 
    template <typename T>
    aghContainer<T>& aghContainer<T>::operator<<(T const& _element)
    {
       return (*this += _element);
    }
 
    template <typename T>
    aghContainer<T>& aghContainer<T>::operator<<(aghContainer<T> const& _right)
    {
        return (*this += _right);
    }
 
#endif /* defined(__aghContainer__aghContainer__) */
