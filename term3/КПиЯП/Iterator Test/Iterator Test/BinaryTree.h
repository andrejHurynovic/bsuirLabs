//
//  BinaryTree.h
//  Iterator Test
//
//  Created by Andrej Hurynovič on 7.01.21.
//

#ifndef BinaryTree_h
#define BinaryTree_h

#include "Node.h"


template <typename DataType, typename KeyDataType>
class BinaryTree {
protected:
    Node<DataType, KeyDataType>* root;
public:
    
    class Iterator;

    BinaryTree(Node<DataType, KeyDataType>* root = NULL){
        this->root = root;
        
        this->beginConst = root;
        this->endConst = NULL;
    }
    
    bool empty(){
        if(!root){
            return true;
        }else{
            return false;
        }
    }
    
    bool checkKey(KeyDataType key){
        Iterator iterator = begin();
        while(iterator != end()){
            if((*iterator)->getKey() == key){
                return true;
            }
            iterator++;
        }
        return false;
    }
    
    Node<DataType, KeyDataType>* findKey(int key){
        return root->find(key);
    }
    
    void print(){
        Iterator iterator = begin();
        while(iterator != end()){
            std::cout << (*iterator)->getData() << std::endl;
            iterator++;
        }
    }
    

    
    
    void add(Node<DataType, KeyDataType> *node){
        if(empty()){
            root = node;
            
            beginConst = root;
            endConst = NULL;
        }else{
            root->add(node);
            
            if(beginConst > node->getKey()){
                beginConst = node;
            }
        }
    }
    
    void remove(KeyDataType key){
        
    
        if(key == (*beginConst)->getKey()){
            if((*beginConst)->getNext((*beginConst)->getKey()) == NULL){
                
            }else{
                beginConst = (*beginConst)->getNext((*beginConst)->getKey());
            }
        }

        root->deleteKey(&root, key);
    }
    
    
    
    //Iterators
    
    Iterator beginConst;
    Iterator endConst;
    
    Iterator begin(){
        return beginConst;
    }
    Iterator end(){
        return endConst;
    }
    

    
    
    
    
    class Iterator{
    private:
        Node<DataType, KeyDataType>* current;
    public:
        Iterator(Node<DataType, KeyDataType>* current = NULL){
            this->current = current;
        }
        
        void operator = (Node<DataType, KeyDataType>* current) {
            this->current = current;
        }
        
        Node<DataType, KeyDataType>* operator * () {
            return current;
        }
        
        
        
        void operator ++ (int){
            this->current = current->getNext(current->getKey());
        }
        

        
        bool operator > (KeyDataType key){
            if(current->getKey() > key){
                return true;
            }else{
                return false;
            }
        }
        
        bool operator < (KeyDataType key){
            if(current->getKey() < key){
                return true;
            }else{
                return false;
            }
        }
        
        bool operator == (const Iterator& iterator) {
            if(this->current == iterator.current){
                return true;
            }else{
                return false;
            }
        }
        
        bool operator != (const Iterator& iterator) {
            if(!(*this == iterator)){
                return true;
            }else{
                return false;
            }
        }
    };
};

#endif /* BinaryTree_h */
