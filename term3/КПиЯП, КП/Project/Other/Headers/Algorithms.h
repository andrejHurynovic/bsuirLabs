//
//  Algorithms.h
//  Project
//
//  Created by Andrej Hurynovič on 10.01.21.
//

#ifndef Algorithms_h
#define Algorithms_h

#include "Bachelor.h"
#include "ExceptionFile.h"
#include "Undo.h"


class Algorithms {
public:
    static void writeBachelorToFile(Bachelor&, File&);
    
    static fstream openFile(enum FileType, bool);
    
    static float calclulateBachelorScholarship(Bachelor&, float);
    
    template <typename studentType>
    static void executeUndo(Undo<studentType>&,  BinaryTree<studentType, int>&);
    
    
};

template <typename studentType>
void Algorithms::executeUndo(Undo<studentType>& undo,  BinaryTree<studentType, int>& tree){

    switch (undo.getType) {
        case add:
            tree.remove(undo.getPrivateID);
            break;
        case edit:
            tree.remove(undo.getPrivateID);
            tree.add(*undo.getStudent, stoi(undo.student->getPrivateID()));
            break;
        case UndoType::remove:
            tree.add(*undo.getStudent, stoi(undo.student->getPrivateID()));
            break;
    }
}

#endif /* Algorithms_h */
