//
//  main.cpp
//  Iterator Test
//
//  Created by Andrej Hurynovič on 7.01.21.
//

#include <iostream>
#include "BinaryTree.h"

int main(int argc, const char * argv[]) {
    
    
    int array[1000];
    
    for(int i = 0; i < 1000; i++){
        bool error = false;
        do{
            error = false;
            int temp = rand() % 1000;
            for(int j = 0; j < i; j++){
                if(array[j] == temp){
                    error = true;
                }
            }
            array[i] = temp;
        }while(error);
        
    }
    
    for(int i = 0; i < 1000; i++){
        bool error = false;
        do{
            error = false;
            int temp = rand() % 1000;
            for(int j = 0; j < i; j++){
                if(array[j] == temp){
                    error = true;
                }
            }
            array[i] = temp;
        }while(error);
        
    }
    
    BinaryTree<int, int> tree(new Node<int, int>(array[0], array[0]));
    
    for(int i = 1; i < 1000; i++){
        tree.add(new Node<int, int>(array[i], array[i]));
    }
    
    for(int i = 0; i < 1000; i++){
        bool error = false;
        do{
            error = false;
            int temp = rand() % 1000;
            for(int j = 0; j < i; j++){
                if(array[j] == temp){
                    error = true;
                }
            }
            array[i] = temp;
        }while(error);
    }
    
    for(int i = 0; i < 1000; i++){
  
        tree.print();
        
        tree.remove(array[i]);
        
        std::cout << std::endl << std::endl;
        
        if(tree.checkKey(array[i])){
            
        }
    }


    
    return 0;
}
