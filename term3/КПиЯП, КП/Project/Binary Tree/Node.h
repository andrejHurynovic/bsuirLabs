//
//  Node.h
//  BinaryTreeIterator Test
//
//  Created by Andrej Hurynovič on 7.01.21.
//

#ifndef Node_h
#define Node_h

template <typename DataType, typename KeyDataType>
class Node {
public:
    DataType data;
    KeyDataType key;
    
    Node* left;
    Node* right;
    Node* parent;
    
public:
    Node(DataType data, KeyDataType key){
        this->data = data;
        this->key = key;
        
        this->left = NULL;
        this->right = NULL;
        this->parent = NULL;
    }

    void add(Node*);
    
    Node* find(int);
    Node* getNext(KeyDataType);
    
    void deleteKey(Node** root, KeyDataType);
    Node* supportDeleteFunction(Node*);
    
    void deleteAll();
    
    DataType& getData();
    KeyDataType getKey();
    void setData(DataType);
    void setKey(KeyDataType);
    
};



template <typename DataType, typename KeyDataType>
void Node<DataType, KeyDataType>::add(Node* node){
    if(node->key < this->key){
        if(this->left){
            this->left->add(node);
        }else{
            node->parent = this;
            this->left = node;
        }
    }
    
    if(node->key > this->key){
        if(this->right){
            this->right->add(node);
        }else{
            node->parent = this;
            this->right = node;
        }
    }
}



template <typename DataType, typename KeyDataType>
Node<DataType, KeyDataType>* Node<DataType, KeyDataType>::find(int key){
    if(this->key == key){
        return this;
    }
    
    if(key < this->key){
        if(left){
            return left->find(key);
        }
    }
    
    if(key > this->key){
        if(right){
            return right->find(key);
        }
    }
    
    return NULL;
}

template <typename DataType, typename KeyDataType>
Node<DataType, KeyDataType>* Node<DataType, KeyDataType>::getNext(KeyDataType key){
    
    if(!parent && !right && !left){
        return NULL;
    }
    
    if(left && right){
        if(left->key > key){
            return left->getNext(key);
        }else{
            if(this->key <= key){
                if(right->key > key){
                    return right->getNext(key);
                }
            }
        }
    }
    
    if(left && left->key > key){
        return left->getNext(key);
    }
    
    if(right){
        if(this->key > key){
            return this;
        }
        
        if(right->key > key){
            return right->getNext(key);
        }else{
            if(parent){
                return parent->getNext(key);
            }else{
                return NULL;
            }
        }
    }
    
    
    if(this->key > key){
        return this;
    }
    
    if(parent){
        Node* temp = parent->getNext(key);
        if(temp && temp->getKey() > key){
            return temp;
        }else{
            return NULL;
        }
        
    }
    return NULL;
}



template <typename DataType, typename KeyDataType>
void Node<DataType, KeyDataType>::deleteKey(Node** root, KeyDataType key){
    
    if(*root){
        if((*root)->key == key){
        
            if(key == 0){
                
            }
            
            if(!((*root)->parent) && !((*root)->left) && !((*root)->right)){
                delete (*root);
                (*root) = NULL;
                return;
            }
            
            if(!(*root)->left && !(*root)->right){
                
                if((*root)->parent->left == (*root)){
                    (*root)->parent->left = NULL;
                    delete (*root);
                    return;
                }
                
                if((*root)->parent->right == (*root)){
                    (*root)->parent->right = NULL;
                    delete (*root);
                    return;
                }
                
            }
            
            if(!(*root)->left && (*root)->right){
                Node* tempNode = (*root)->right;
                (*root)->right->parent = (*root)->parent;
                delete (*root);
                (*root) = tempNode;
                return;
            }
            
            if((*root)->left && !(*root)->right){
                (*root)->left->parent = (*root)->parent;
                Node* tempNode = (*root)->left;
                delete (*root);
                (*root) = tempNode;
                return;
            }
            
            if((*root)->left && (*root)->right){
                Node* tempNode = supportDeleteFunction((*root)->right);
                Node* temp = tempNode->parent;
                if(!temp){
                    temp = *root;
                }
                
                if(!tempNode->left && !tempNode->right){
                    if(temp->left && temp->left == tempNode){
                        if(temp->left->key == tempNode->key){
                            temp->left = NULL;
                        }
                    }
                    if(temp->right && temp->right == tempNode){
                        if(temp->right->key == tempNode->key){
                            temp->right = NULL;
                        }
                    }
                    
                    if((*root)->left && (*root)->left != tempNode){
                        tempNode->left = (*root)->left;
                        (*root)->left->parent = tempNode;
                    }
                    
                    
                    if((*root)->right && (*root)->right != tempNode){
                        tempNode->right = (*root)->right;
                        (*root)->right->parent = tempNode;
                    }
                    
                    
                    tempNode->parent = (*root)->parent;
                    delete (*root);
                    (*root) = tempNode;
                }
                
                if(!tempNode->left && tempNode->right){
                    if(temp->left){
                        if(temp->left->key == tempNode->key){
                            tempNode->right->parent = temp;
                            temp->left = tempNode->right;
                        }
                    }
                    if(temp->right){
                        if(temp->right->key == tempNode->key){
                            tempNode->right->parent = temp;
                            temp->right = tempNode->right;
                        }
                    }
                    
                    if((*root)->left != tempNode){
                        tempNode->left = (*root)->left;
                        (*root)->left->parent = tempNode;
                    }
                    
                    
                    if((*root)->right != tempNode){
                        tempNode->right = (*root)->right;
                        (*root)->right->parent = tempNode;
                    }
                    
                    tempNode->parent = (*root)->parent;
                    delete (*root);
                    (*root) = tempNode;
                }
                
            }
        }else{
            if(key < (*root)->key){
                deleteKey(&(*root)->left, key);
            }else{
                deleteKey(&(*root)->right, key);
            }
        }
    }
}



template <typename DataType, typename KeyDataType>
Node<DataType, KeyDataType>* Node<DataType, KeyDataType>::supportDeleteFunction(Node* root){
    if((!root->left && root->right) || (!root->left && !root->right)){
        return root;
    }
    
    if(root->left){
        return supportDeleteFunction(root->left);
    }
    
    return NULL;

}



template <typename DataType, typename KeyDataType>
void Node<DataType, KeyDataType>::deleteAll(){
    if(left){
        left->deleteAll();
        left = NULL;
    }
    if(right){
        right->deleteAll();
        right = NULL;
    }
    delete this;
}



template <typename DataType, typename KeyDataType>
DataType& Node<DataType, KeyDataType>::getData(){
    return data;
}

template <typename DataType, typename KeyDataType>
KeyDataType Node<DataType, KeyDataType>::getKey(){
    return key;
}

template <typename DataType, typename KeyDataType>
void Node<DataType, KeyDataType>::setData(DataType data){
    this->data = data;
}

template <typename DataType, typename KeyDataType>
void Node<DataType, KeyDataType>::setKey(KeyDataType key){
    this->key = key;
}


#endif /* Node_h */
