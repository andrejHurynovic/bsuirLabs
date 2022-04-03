//
//  BinaryTree.h
//  BinaryTreeIterator
//
//  Created by Andrej Hurynovič on 7.01.21.
//

#ifndef BinaryTree_h
#define BinaryTree_h

#include "BinaryTreeIterator.h"


template <typename DataType, typename KeyDataType>
class BinaryTree {
private:
    Node<DataType, KeyDataType>* root;
    
    BinaryTreeIterator<DataType, KeyDataType> beginConst;
    BinaryTreeIterator<DataType, KeyDataType> endConst;
    
    
public:
    
    BinaryTree(Node<DataType, KeyDataType>* root = NULL){
        this->root = root;

        this->beginConst = root;
        this->endConst = root;
    }

    BinaryTree(DataType data, KeyDataType key){
        this->root = new Node<DataType, KeyDataType>(data, key);

        this->beginConst = root;
        this->endConst = root;
    }
    
    bool empty();
    bool checkKey(KeyDataType);
    Node<DataType, KeyDataType>* findNodeKey(int);
    DataType& findKey(int);
    int size();
    
    void add(DataType , KeyDataType);
    void remove(KeyDataType);
    void clear();
    
    void print();
    
    DataType& operator [] (int);
    BinaryTreeIterator<DataType, KeyDataType> begin();
    BinaryTreeIterator<DataType, KeyDataType> end();
};







template <typename DataType, typename KeyDataType>
bool BinaryTree<DataType, KeyDataType>::empty(){
    if(!root){
        return true;
    }else{
        return false;
    }
}

template <typename DataType, typename KeyDataType>
bool BinaryTree<DataType, KeyDataType>::checkKey(KeyDataType key){
    BinaryTreeIterator<DataType, KeyDataType> iterator = begin();
    while(iterator != NULL){
        if((&iterator)->getKey() == key){
            return true;
        }
        iterator++;
    }
    return false;
}

template <typename DataType, typename KeyDataType>
Node<DataType, KeyDataType>* BinaryTree<DataType, KeyDataType>::findNodeKey(int key){
    if(empty()){
        return NULL;
    }
    return root->find(key);
}

template <typename DataType, typename KeyDataType>
DataType& BinaryTree<DataType, KeyDataType>::findKey(int key){
    return root->find(key)->getData();
}



template <typename DataType, typename KeyDataType>
int BinaryTree<DataType, KeyDataType>::size(){
    
    int counter = 0;
    
    BinaryTreeIterator<DataType, KeyDataType> iterator = begin();
    while(iterator != NULL){
        iterator++;
        counter++;
    }
    return counter;
}



template <typename DataType, typename KeyDataType>
void BinaryTree<DataType, KeyDataType>::add(DataType data, KeyDataType key){
    
    if(checkKey(key)){
        return;
    }
   
    Node<DataType, KeyDataType> *node;
    node =  new Node<DataType, KeyDataType>(data, key);
    
    if(empty()){
        root = node;
        
        beginConst = root;
        endConst = root;
    }else{
        root->add(node);
        
        if(beginConst > node->getKey()){
            beginConst = node;
        }
        if(endConst < node->getKey()){
            endConst = node;
        }
    }
}

template <typename DataType, typename KeyDataType>
void BinaryTree<DataType, KeyDataType>::remove(KeyDataType key){

    if(key == (&beginConst)->getKey()){
        if((&beginConst)->getNext((&beginConst)->getKey()) == NULL){
            beginConst = NULL;
        }else{
            beginConst = (&beginConst)->getNext((&beginConst)->getKey());
        }
    }

    root->deleteKey(&root, key);
}

template <typename DataType, typename KeyDataType>
void BinaryTree<DataType, KeyDataType>::clear(){
    if(root){
        root->deleteAll();
        root = NULL;
    }
}



template <typename DataType, typename KeyDataType>
void BinaryTree<DataType, KeyDataType>::print(){
    BinaryTreeIterator<DataType, KeyDataType> iterator = begin();
    while(iterator != NULL){
        cout << (&iterator) << endl;
        iterator++;
    }
}



template <typename DataType, typename KeyDataType>
DataType& BinaryTree<DataType, KeyDataType>::operator [] (int temp){
    
    if(temp > size()){
         return *(begin() + (size() - 1));
    }
    
    return *(begin() + temp);
}


template <typename DataType, typename KeyDataType>
BinaryTreeIterator<DataType, KeyDataType> BinaryTree<DataType, KeyDataType>::begin(){
    return beginConst;
}

template <typename DataType, typename KeyDataType>
BinaryTreeIterator<DataType, KeyDataType> BinaryTree<DataType, KeyDataType>::end(){
    return endConst;
}


#endif /* BinaryTree_h */
