//
//  Menu.h
//  Project
//
//  Created by Andrej Hurynovič on 17.12.20.
//

#ifndef Menu_h
#define Menu_h

#include "Doctor.h"
#include "BinaryTree.h"
#include "Undo.h"

class Menu {
    
    BinaryTree<Bachelor, int> bachelors;
    BinaryTree<Master, int> masters;
    BinaryTree<Doctor, int> doctors;
    
    stack<Undo<Bachelor>> bachelorsUndoStack;
    stack<Undo<Master>> mastersUndoStack;
    stack<Undo<Doctor>> doctorsUndoStack;

    
    int chooseStudentType();
    
    bool noStudents();
    template <typename studentType>
    bool noStudentsIn(BinaryTree<studentType, int>&);
    
    bool checkPrivateID(string privateID, bool printMessage = true);
    
    
    template <typename studentType>
    BinaryTree<studentType, int>sortBinaryTree(BinaryTree<studentType, int>);
    
    
    template <typename studentType>
    studentType createStudent();
    
    template <typename studentType>
    void editStudent(BinaryTree<studentType, int>&);
    template <typename studentType>
    bool editStudentByID(BinaryTree<studentType, int>&, string);
    
    template <typename studentType>
    void removeStudent(BinaryTree<studentType, int>&);
    template <typename studentType>
    bool removeStudentByID(BinaryTree<studentType, int>&, string);
   
    template <typename studentType>
    void printStudent(BinaryTree<studentType, int>);
    
    template <typename studentType>
    void searchStudent(BinaryTree<studentType, int>&);
    
    
    template <typename studentType>
    void undoStudent(stack<Undo<studentType>> &stack, BinaryTree<studentType, int>& tree);
    template <typename studentType>
    void addUndo(stack<Undo<studentType>>&, Undo<studentType>);
    
    template <typename studentType>
    void writeStudent(File&, BinaryTree<studentType, int>&);
    void readStudents();
    template <typename studentType>
    void readStudent(File&, BinaryTree<studentType, int>&);
    
public:
    Menu(){
        readStudents();
    }
    
    void call();
    
    void enter();
    void edit();
    void remove();
    void print();
    void search();
    void undo();
    void settings();
    void write();
    
    ~Menu(){
        bachelors.clear();
        masters.clear();
        doctors.clear();
    }
};




template <typename studentType>
bool Menu::noStudentsIn(BinaryTree<studentType, int> &tree){
    return tree.empty();
}



template <typename studentType>
BinaryTree<studentType, int> Menu::sortBinaryTree(BinaryTree<studentType, int> tree){
    
    
    vector<string> usedIDs;
    BinaryTree<studentType, int> sortedTree;
        
    cout <<  endl <<
    "Choose sort way: " << endl <<
    "0. Private ID." << endl <<
    "1. Group." << endl <<
    "2. Scholarship." << endl;

    switch (ExceptionEnter::NumberData<int>(sortMenu)) {
        case 0:
            sortedTree = tree;
            break;
        case 1:{
            auto iterator = tree.begin();
            int a = 0;
            int b = 0;
            int c;
            int minimalGroup;
            int previousGroup = 1000000;
            
            do{
                minimalGroup = 999999;
                iterator = tree.begin();
                do{
                    c = 0;
                    if((&iterator)->getKey() && stoi((&iterator)->getData().getGroup()) < minimalGroup && stoi((&iterator)->getData().getGroup()) != previousGroup){
                        for(int g = 0; g < usedIDs.size(); g++){
                            if((&iterator)->getData().getPrivateID() == usedIDs[g]){
                                c = 1;
                            }
                        }
                        if(!c){
                            a = 0;
                            minimalGroup = stoi((&iterator)->getData().getGroup());
                        }
                    }
                    iterator++;
                }while(iterator != NULL);
                
                if(a == -1){
                    break;
                }
                
                a = 0;
                iterator = tree.begin();
                do{
                    if(stoi((&iterator)->getData().getGroup()) == minimalGroup){
                        usedIDs.push_back((&iterator)->getData().getPrivateID());
                        sortedTree.add((&iterator)->getData(), b);
                        b++;
                    }
                    iterator++;
                }while(iterator != NULL);
                
                a = -1;
                previousGroup = minimalGroup;
            }while(true);
            break;
        }
        case 2:{
            auto iterator = tree.begin();
            int a = 0;
            int b = 0;
            int c;
            int minimalScholarship;
            int previousScholarship = 1000000;
            
            do{
                minimalScholarship = 999999;
                iterator = tree.begin();
                do{
                    c = 0;
                    if((&iterator)->getKey() && (&iterator)->getData().getScholarship() < minimalScholarship && (&iterator)->getData().getScholarship() != previousScholarship){
                        for(int g = 0; g < usedIDs.size(); g++){
                            if((&iterator)->getData().getPrivateID() == usedIDs[g]){
                                c = 1;
                            }
                        }
                        if(!c){
                            a = 0;
                            minimalScholarship = (&iterator)->getData().getScholarship();
                        }
                    }
                    iterator++;
                }while(iterator != NULL);
                
                if(a == -1){
                    break;
                }
                
                a = 0;
                iterator = tree.begin();
                do{
                    if((&iterator)->getData().getScholarship() == minimalScholarship){
                        usedIDs.push_back((&iterator)->getData().getPrivateID());
                        sortedTree.add((&iterator)->getData(), b);
                        b++;
                    }
                    iterator++;
                }while(iterator != NULL);
                
                a = -1;
                previousScholarship = minimalScholarship;
            }while(true);
            break;
        }
    }
    
    return sortedTree;
    
}



template <typename studentType>
studentType Menu::createStudent(){
    studentType student;
    
    string privateID;
    cout << "Enter private ID ("<< Settings::getLength(DataType::privateID) << " digits): ";
    do{
        privateID = ExceptionEnter::stringData(DataType::privateID);
    }while(checkPrivateID(privateID));
    student.setPrivateID(privateID);
    
    cin >> student;
    student.calculateScholarship();
    return student;
}



template <typename studentType>
void Menu::editStudent(BinaryTree<studentType, int> &tree){
    if(noStudentsIn(tree)){
        cout << "No students of this type." << endl;
        return;
    }
    printStudent(tree);
    
    do{
        cout << "Enter student ID: ";
    }while(!editStudentByID(tree, ExceptionEnter::stringData(privateID)));
}

template <typename studentType>
bool Menu::editStudentByID(BinaryTree<studentType, int> &tree, string ID){
    
    Node<studentType, int>* node = tree.findNodeKey(stoi(ID));
    
    if(!node){
        return false;
    }
    
    studentType *student = new studentType(node->getData());
    
    Doctor* tempStudent = static_cast<Doctor*>(student);

    
    if(typeid(studentType) == typeid(Bachelor)){
        addUndo(bachelorsUndoStack, Undo<Bachelor>(UndoType::edit, dynamic_cast<Bachelor*>(tempStudent), stoi(student->getPrivateID())));
    }
    if(typeid(studentType) == typeid(Master)){
        addUndo(mastersUndoStack, Undo<Master>(UndoType::edit, dynamic_cast<Master*>(tempStudent), stoi(student->getPrivateID())));
    }
    if(typeid(studentType) == typeid(Doctor)){
        addUndo(doctorsUndoStack, Undo<Doctor>(UndoType::edit, tempStudent, stoi(student->getPrivateID())));
    }
    
    node->getData().editMenu(true);
    node->getData().calculateScholarship();
    
    if(node->getData().getPrivateID() != ID){
        if(checkPrivateID(node->getData().getPrivateID())){
            node->getData().setPrivateID(ID);
            cout << "This private ID is already exist, returned to the original value." << endl;
        }else{
            tree.add(node->getData(), stoi(node->getData().getPrivateID()));
            tree.remove(stoi(ID));
            
            if(typeid(studentType) == typeid(Bachelor)){
                bachelorsUndoStack.top().setPrivateID(stoi(node->getData().getPrivateID()));
            }
            if(typeid(studentType) == typeid(Master)){
                mastersUndoStack.top().setPrivateID(stoi(node->getData().getPrivateID()));
            }
            if(typeid(studentType) == typeid(Doctor)){
                doctorsUndoStack.top().setPrivateID(stoi(node->getData().getPrivateID()));
            }
        }
    }
    return true;
}



template <typename studentType>
void Menu::removeStudent(BinaryTree<studentType, int> &tree){
    if(noStudentsIn(tree)){
        cout << "No students of this type." << endl;
        return;
    }
    printStudent(tree);
    
    cout <<  endl <<
    "1. Choose student to remove." << endl <<
    "2. Remove all students of this type. (This action cannot be undone!)" << endl <<
    "0. Exit." << endl;
    
    switch (ExceptionEnter::NumberData<int>(removeMenu)){
        case 0:
            return;
        case 1:
            do{
                cout << "Enter student ID: ";
            }while(!removeStudentByID(tree, ExceptionEnter::stringData(privateID)));
            
            cout << "This student was removed." << endl;
            break;
        case 2:
            tree.clear();
            cout << "All students of this type was removed." << endl;
        default:
            break;
    }
}

template <typename studentType>
bool Menu::removeStudentByID(BinaryTree<studentType, int> &tree, string ID){
    
    if(!tree.checkKey(stoi(ID))){
        return false;
    }
    
    studentType *student = new studentType(tree.findKey(stoi(ID)));
    
    Doctor* tempStudent = static_cast<Doctor*>(student);

    
    if(typeid(studentType) == typeid(Bachelor)){
        addUndo(bachelorsUndoStack, Undo<Bachelor>(UndoType::remove, dynamic_cast<Bachelor*>(tempStudent)));
    }
    if(typeid(studentType) == typeid(Master)){
        addUndo(mastersUndoStack, Undo<Master>(UndoType::remove, dynamic_cast<Master*>(tempStudent)));
    }
    if(typeid(studentType) == typeid(Doctor)){
        addUndo(doctorsUndoStack, Undo<Doctor>(UndoType::remove, tempStudent));
    }
    
    
    tree.remove(stoi(ID));

    return true;
}



template <typename studentType>
void Menu::
searchStudent(BinaryTree<studentType, int> &students){
    
    if(students.empty()){
        cout << "No students of this type." << endl;
    }
    
    BinaryTree<studentType, int> tree;
    
    do{
        cout <<  endl <<
        "1. Private ID." << endl <<
        "2. Group." << endl <<
        "3. Name." << endl <<
        "4. Scholarship size." << endl <<
        "5. Benifits." << endl <<
        "0. Exit." << endl;
        
        tree.clear();
        
        switch (ExceptionEnter::NumberData<int>(searchMenu)){
            case 0:
                return;
            case 1:{
                cout << "Enter private ID ("<< Settings::getLength(DataType::privateID) << " digits): ";
                string ID = ExceptionEnter::stringData(privateID);
                Node<studentType, int> *node = students.findNodeKey(stoi(ID));
                
                if(node){
                    tree.add(node->getData(), stoi(node->getData().getPrivateID()));
                }
            }
                break;
            case 2:{
                cout << endl << "Enter group (" << Settings::getLength(DataType::group) << " digits): " << endl;
                string group = ExceptionEnter::stringData(DataType::group);
                
                auto iterator = students.begin();
                
                do{
                    if((&iterator)->getData().getGroup() == group){
                        tree.add((&iterator)->getData(), stoi((&iterator)->getData().getPrivateID()));
                    }
                    iterator++;
                }while(iterator != NULL);
            }
                break;
            case 3:{
                cout << endl << "Enter name (" << Settings::getLength(DataType::name) << " digits): " << endl;
                string name = ExceptionEnter::stringData(DataType::name);
                
                auto iterator = students.begin();
                
                do{
                    if((&iterator)->getData().getName() == name){
                        tree.add((&iterator)->getData(), stoi((&iterator)->getData().getPrivateID()));
                    }
                    iterator++;
                }while(iterator != NULL);
            }
                break;
            case 4:
                cout <<  endl <<
                "1. Integer value." << endl <<
                "2. Range." << endl <<
                "0. Exit." << endl;
                switch (ExceptionEnter::NumberData<int>(scholarshipMenu)) {
                    case 0:
                        return;
                        break;
                    case 1:{
                        cout << endl << "Enter value: " << endl;
                        int value = ExceptionEnter::NumberData<int>(scholarshipValue);
                        
                        auto iterator = students.begin();
                        
                        do{
                            if(int((&iterator)->getData().getScholarship()) == value){
                                tree.add((&iterator)->getData(), stoi((&iterator)->getData().getPrivateID()));
                            }
                            iterator++;
                        }while(iterator != NULL);
                        break;
                    }
                    case 2:
                        cout << endl << "Enter first value: " << endl;
                        int firstValue = ExceptionEnter::NumberData<int>(scholarshipValue);
                        cout << endl << "Enter second value: " << endl;
                        int secondValue = ExceptionEnter::NumberData<int>(scholarshipValue);
                        
                        if(firstValue > secondValue){
                            int tempValue = secondValue;
                            secondValue = firstValue;
                            firstValue = tempValue;
                        }
                        
                        auto iterator = students.begin();

                        do{
                            if(firstValue <= int((&iterator)->getData().getScholarship()) && secondValue >= int((&iterator)->getData().getScholarship())){
                                tree.add((&iterator)->getData(), stoi((&iterator)->getData().getPrivateID()));
                            }
                            iterator++;
                        }while(iterator != NULL);
                }
                break;
            case 5:
                Benefit benefit;
                cin >> benefit;
                
                auto iterator = students.begin();

                do{
                    int i = 0;
                    while((&iterator)->getData().getBenefitForID(i) != NULL){
                        if(*(&iterator)->getData().getBenefitForID(i) == benefit){
                            tree.add((&iterator)->getData(), stoi((&iterator)->getData().getPrivateID()));
                        }
                        i++;
                    }

                    iterator++;
                }while(iterator != NULL);
                
                break;
                
        }
        
        if(!tree.empty()){
            this->printStudent(tree);
        }else{
            cout << endl << "Can't find students by this parameters." << endl;
        }
    }while(true);
}


template <typename studentType>
void Menu::undoStudent(stack<Undo<studentType>> &stack, BinaryTree<studentType, int>& tree){
    if(stack.empty()){
        cout << "No undo actions." << endl;
    }else{
        stack.top().execute(tree);
        stack.pop();
        cout << "Action complited." << endl;
    }
}


template <typename studentType>
void Menu::addUndo(stack<Undo<studentType>> &stack, Undo<studentType> undo){
    stack.push(undo);
}


template <typename studentType>
void Menu::printStudent(BinaryTree<studentType, int> tree){
    if(tree.empty()){
        cout << "No students of this type." << endl;
        return;
    }
    
    tree = sortBinaryTree(tree);
    
    studentType::printSpreadsheet(true);
    cout << endl;
    
    auto iterator = tree.begin();

    do{
        cout << (&iterator)->getData() << endl;
        (&iterator)->getData().printMarksAndBenefits();
        iterator++;
    }while(iterator != NULL);
    cout << endl;
}



template <typename studentType>
void Menu::readStudent(File &file, BinaryTree<studentType, int> &students){
    while(!file.endOfFile()){
        studentType student;
        student.readFromFile(file);
        students.add(student, stoi(student.getPrivateID()));
    }
}

template <typename studentType>
void Menu::writeStudent(File &file, BinaryTree<studentType, int> &tree){
    auto iterator = tree.begin();

    while(iterator != NULL){
        (&iterator)->getData().writeToFile(file);
        iterator++;
    }
}

#endif /* Menu_h */
