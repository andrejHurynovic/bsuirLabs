//
//  Undo.h
//  Project
//
//  Created by Andrej Hurynovič on 8.01.21.
//

#ifndef Undo_h
#define Undo_h

#include "BinaryTree.h"

enum UndoType{
    add,
    edit,
    remove,
};

template <typename studentTypeUndo>
class Undo {
private:
    enum UndoType type;
    studentTypeUndo *student;
    int privateID;
public:
    Undo(enum UndoType type = add, studentTypeUndo *student = NULL, int privateID = 0){
        this->type = type;
        this->student = student;
        this->privateID = privateID;
    }
    
    void execute(BinaryTree<studentTypeUndo, int>&);
    enum UndoType getType();
    studentTypeUndo* getStudent();
    int getPrivateID();
    void setType(enum UndoType);
    void setStudent(studentTypeUndo*);
    void setPrivateID(int);
};



template <typename studentTypeUndo>
void Undo<studentTypeUndo>::execute(BinaryTree<studentTypeUndo, int> &tree){
    switch (type) {
        case add:
            tree.remove(privateID);
            break;
        case edit:
            tree.remove(privateID);
            tree.add(*student, stoi(student->getPrivateID()));
            break;
        case UndoType::remove:
            tree.add(*student, stoi(student->getPrivateID()));
            break;
    }
}

template <typename studentTypeUndo>
enum UndoType Undo<studentTypeUndo>::getType(){
    return type;
}
template <typename studentTypeUndo>
studentTypeUndo* Undo<studentTypeUndo>::getStudent(){
    return student;
}
template <typename studentTypeUndo>
int Undo<studentTypeUndo>::getPrivateID(){
    return privateID;
}


template <typename studentTypeUndo>
void Undo<studentTypeUndo>::setType(enum UndoType type){
    this->type = type;
}
template <typename studentTypeUndo>
void Undo<studentTypeUndo>::setStudent(studentTypeUndo *student){
    this->student = student;
}
template <typename studentTypeUndo>
void Undo<studentTypeUndo>::setPrivateID(int privateID){
    this->privateID = privateID;
}

#endif /* Undo_h */
