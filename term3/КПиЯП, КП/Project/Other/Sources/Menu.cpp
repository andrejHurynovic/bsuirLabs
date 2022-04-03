//
//  Menu.cpp
//  Project
//
//  Created by Andrej Hurynovič on 17.12.20.
//

#include "Menu.h"

int Menu::chooseStudentType(){
    cout << "1. Bachelor." << endl << "2. Master." << endl << "3. Doctor." << endl << "0. Exit." << endl;
    return ExceptionEnter::NumberData<int>(studnetTypes);
}



bool Menu::noStudents(){
    if(noStudentsIn(bachelors) && noStudentsIn(masters) && noStudentsIn(doctors)){
        cout << "No students." << endl;
        return true;
    }
    return false;
}



bool Menu::checkPrivateID(string privateID, bool printMessage){
    if(ExceptionEnter::checkThisID(privateID, bachelors) || ExceptionEnter::checkThisID(privateID, masters) || ExceptionEnter::checkThisID(privateID, doctors)){
        if(printMessage){
            cout << "This private ID is already exist." << endl;
        }
        return true;
    }
    return false;
}



void Menu::call(){
    
    do{
        cout <<  endl <<
        "1. Add studnet." << endl <<
        "2. Edit studnet." << endl <<
        "3. Remove students." << endl <<
        "4. Print students." << endl <<
        "5. Search students." << endl <<
        "6. Undo." << endl <<
        "7. Settings." << endl <<
        "8. Save students." << endl <<
        "0. Exit." << endl;
        
        switch (ExceptionEnter::NumberData<int>(menuNumber)) {
            case 0:
                return;
            case 1:
                enter();
                break;
            case 2:
                edit();
                break;
            case 3:
                remove();
                break;
            case 4:
                print();
                break;
            case 5:
                search();
                break;
            case 6:
                undo();
                break;
            case 7:
                settings();
                break;
            case 8:
                write();
                break;
        }
    }while(true);
}

void Menu::enter(){
    
    switch (chooseStudentType()) {
        case 0:{
            return;
        }
        case 1:{
            Bachelor bachelor = createStudent<Bachelor>();
            addUndo(bachelorsUndoStack, Undo<Bachelor>(add, NULL, stoi(bachelor.getPrivateID())));
            bachelors.add(bachelor, stoi(bachelor.getPrivateID()));
            break;
        }
        case 2:{
            Master master(createStudent<Master>());
            addUndo(mastersUndoStack, Undo<Master>(add, NULL, stoi(master.getPrivateID())));
            masters.add(master, stoi(master.getPrivateID()));
            break;
        }
        case 3:{
            Doctor doctor = createStudent<Doctor>();
            addUndo(doctorsUndoStack, Undo<Doctor>(add, NULL, stoi(doctor.getPrivateID())));
            doctors.add(doctor, stoi(doctor.getPrivateID()));
            break;
        }
    }
}

void Menu::edit(){
    if(noStudents()){
        return;
    }
    
    switch (chooseStudentType()) {
        case 0:
            return;
        case 1:
            editStudent(bachelors);
            break;
        case 2:
            editStudent(masters);
            break;
        case 3:
            editStudent(doctors);
            break;
    }
}

void Menu::remove(){
    if(noStudents()){
        return;
    }
    
    switch (chooseStudentType()){
        case 0:
            return;
        case 1:
            removeStudent(bachelors);
            break;
        case 2:
            removeStudent(masters);
            break;
        case 3:
            removeStudent(doctors);
            break;
    }
}


void Menu::print(){
    if(noStudents()){
        return;
    }
    
    switch (chooseStudentType()) {
        case 0:
            return;
        case 1:
            printStudent(bachelors);
            break;
        case 2:
            printStudent(masters);
            break;
        case 3:
            printStudent(doctors);
            break;
    }
}

void Menu::search(){
    if(noStudents()){
        return;
    }
    
    switch (chooseStudentType()) {
        case 0:
            return;
        case 1:
            searchStudent(bachelors);
            break;
        case 2:
            searchStudent(masters);
            break;
        case 3:
            searchStudent(doctors);
            break;
    }
}

void Menu::undo(){
    if(bachelorsUndoStack.empty() && mastersUndoStack.empty() && doctorsUndoStack.empty()){
        cout << "No undo." << endl;
        return;
    }
    
    switch (chooseStudentType()){
        case 0:
            return;
        case 1:
            undoStudent(bachelorsUndoStack, bachelors);
            break;
        case 2:
            undoStudent(mastersUndoStack, masters);
            break;
        case 3:
            undoStudent(doctorsUndoStack, doctors);
            break;
    }
}


void Menu::settings(){
    Settings::menu();
    auto iterator = bachelors.begin();

    while(iterator != NULL){
        (&iterator)->getData().calculateScholarship();
        iterator++;
    };
    
    auto iterator2 = masters.begin();

    while(iterator2 != NULL){
        
        (&iterator2)->getData().calculateScholarship();
        iterator2++;
    };
    
    auto iterator3 = doctors.begin();

    while(iterator3 != NULL){
        (&iterator3)->getData().calculateScholarship();
        iterator3++;
    };
}


void Menu::readStudents(){
    File file(FileType::bachelors, false);
    readStudent(file, bachelors);
    
    File file2(FileType::masters, false);
    readStudent(file2, masters);
    
    File file3(FileType::doctors, false);
    readStudent(file3, doctors);
}

void Menu::write(){
    File file(FileType::bachelors, true);
    writeStudent(file, bachelors);

    File file2(FileType::masters, true);
    writeStudent(file2, masters);

    File file3(FileType::doctors, true);
    writeStudent(file3, doctors);
    
    cout << "Students was saved successfully." << endl;
}
