//
//  BinaryTreeIterator.h
//  LabWork 8. BinaryTreeIterators
//
//  Created by Andrej Hurynovič on 14.12.20.
//

#include "Node.h"

#ifndef BinaryTreeIterator_h
#define BinaryTreeIterator_h

template <typename DataType, typename KeyDataType>
class BinaryTreeIterator{
private:
    Node<DataType, KeyDataType>* current;
public:
    BinaryTreeIterator(Node<DataType, KeyDataType>* current = NULL){
        this->current = current;
    }
    
    DataType& operator * ();
    Node<DataType, KeyDataType>* operator & ();

    void operator = (Node<DataType, KeyDataType>* current);
    
    void operator ++ (int);
    BinaryTreeIterator& operator + (int temp);
    
    void operator -- (int);
    BinaryTreeIterator& operator - (int temp);
    
    
    bool operator > (KeyDataType key);
    bool operator >= (KeyDataType key);
    bool operator < (KeyDataType key);
    bool operator <= (KeyDataType key);
    
    bool operator == (const BinaryTreeIterator& iterator);
    bool operator != (const BinaryTreeIterator& iterator);
};



template <typename DataType, typename KeyDataType>
void BinaryTreeIterator<DataType, KeyDataType>::operator = (Node<DataType, KeyDataType>* current) {
    this->current = current;
}

template <typename DataType, typename KeyDataType>
DataType& BinaryTreeIterator<DataType, KeyDataType>::operator * () {
    return (current->getData());
}

template <typename DataType, typename KeyDataType>
Node<DataType, KeyDataType>* BinaryTreeIterator<DataType, KeyDataType>::operator & (){
    return current;
}




template <typename DataType, typename KeyDataType>
void BinaryTreeIterator<DataType, KeyDataType>::operator ++ (int){
    this->current = current->getNext(current->getKey());
}

template <typename DataType, typename KeyDataType>
BinaryTreeIterator<DataType, KeyDataType>& BinaryTreeIterator<DataType, KeyDataType>::operator + (int temp){
    do{
        (*this)++;
        temp--;
    }while(temp && *this != NULL);
    return *this;
}



template <typename DataType, typename KeyDataType>
bool BinaryTreeIterator<DataType, KeyDataType>::operator > (KeyDataType key){
    if(current->getKey() > key){
        return true;
    }else{
        return false;
    }
}

template <typename DataType, typename KeyDataType>
bool BinaryTreeIterator<DataType, KeyDataType>::operator >= (KeyDataType key){
    if(current->getKey() >= key){
        return true;
    }else{
        return false;
    }
}

template <typename DataType, typename KeyDataType>
bool BinaryTreeIterator<DataType, KeyDataType>::operator < (KeyDataType key){
    if(current->getKey() < key){
        return true;
    }else{
        return false;
    }
}

template <typename DataType, typename KeyDataType>
bool BinaryTreeIterator<DataType, KeyDataType>::operator <= (KeyDataType key){
    if(current->getKey() <= key){
        return true;
    }else{
        return false;
    }
}



template <typename DataType, typename KeyDataType>
bool BinaryTreeIterator<DataType, KeyDataType>::operator == (const BinaryTreeIterator& iterator) {
    if(this->current == iterator.current){
        return true;
    }else{
        return false;
    }
}

template <typename DataType, typename KeyDataType>
bool BinaryTreeIterator<DataType, KeyDataType>::operator != (const BinaryTreeIterator& iterator) {
    if(this->current != iterator.current){
        return true;
    }else{
        return false;
    }
}



#endif /* BinaryTreeIterator_h */
