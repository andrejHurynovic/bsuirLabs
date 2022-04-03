////
////  fourthB.c
////  labWorks
////
////  Created by Андрэй Гурыновіч on 4/4/20.
////  Copyright © 2020 Андрэй Гурыновіч. All rights reserved.
////
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#define maxinmalStringLenght 256
//
////В бинарном файле записана информация о населении, запись хранит ФИО, идентификационный номер, дату рождения, смещения в файле, по которому лежит информация о родителях. Заранее сформировать и вывести файл с исходными данными. С клавиатуры задать идентификационный номер, число N. Вывести данные о человеке и его предках до N-го уровня дальности (например, для N = 2 вывести информацию о матери, отце, матери и отце матери, матери и отце отца). Реализовать возможность удаления записи.
//
//
//struct Birthday{
//    unsigned int day: 5;
//    unsigned int month: 4;
//    unsigned int year: 16;
//};
//
//void ShowBirthday(struct Birthday *birthday){
//    printf("Birthday: %d.%d.%d\n", birthday->day, birthday->month, birthday->year);
//}
//
//struct Birthday createBurthday(){
//    struct Birthday birthday;
//    
//    int error;
//    unsigned int temp;
//    do{
//        fflush(stdin);
//        printf("Enter day(1...31): ");
//        error = scanf("%d", &temp);
//    }while(!error || temp < 1 || temp > 31);
//    birthday.day = temp;
//    
//    do{
//        fflush(stdin);
//        printf("Enter month (1...12): ");
//        error = scanf("%d", &temp);
//    }while(!error || temp < 1 || temp > 12);
//    birthday.month = temp;
//    
//    do{
//        fflush(stdin);
//        printf("Enter year (0...2046): ");
//        error = scanf("%d", &temp);
//    }while(!error || temp < 0 || temp > 2046);
//    birthday.year = temp;
//    
//    return birthday;
//};
//
//int CompareBirthdays(struct Birthday birthdayA, struct Birthday birthdayB){
//    int temp = birthdayA.year - birthdayB.year;
//    if(temp == 0){
//        temp = birthdayA.month - birthdayB.month;
//        if(temp == 0){
//            temp = birthdayA.day - birthdayB.day;
//            if(temp == 0){
//                return 0;
//            }
//        }
//        if(temp > 0){
//            return 1;
//        } else {
//            return -1;
//        }
//    }
//    if(temp > 0){
//        return 1;                   //-1 A<B
//    }else {                         //0  A==B
//        return -1;                  //1  A>B
//    }
//}
//
//
//
//struct Person{
//    char name[maxinmalStringLenght];
//    char ID[maxinmalStringLenght];
//    struct Birthday birthday;
//    int mother;
//    int father;
//};
//
//void WritePerson(FILE *file, struct Person person,  int point){
//    fseek(file, point * sizeof(struct Person), SEEK_SET);
//    fwrite(&person, sizeof(struct Person), 1, file);
//}
//
//struct Person ReadPerson(FILE *file,  int point){
//    struct Person person;
//    fseek(file, point * sizeof(struct Person), SEEK_SET);
//    fread(&person, sizeof(person), 1, file);
//    return person;
//}
//
//void RemovePerson(FILE *file,  int point,  int numberOfPersons){
//    struct Person person;
//    
//    for(int i = 0; i < numberOfPersons; i++){
//        if(i == point){
//            continue;
//        }
//        
//        person = ReadPerson(file, i);
//        if(person.mother == point){
//            person.mother = -1;
//        }
//        if(person.father == point){
//            person.father = -1;
//        }
//        if(person.mother > point){
//            person.mother--;
//        }
//        if(person.father > point){
//            person.father--;
//        }
//        
//        if(i < point){
//            WritePerson(file, person, i);
//        }else{
//            WritePerson(file, person, i - 1);
//        }
//    }
//}
//
//void ShowPerson(FILE* file, struct Person person, int level){
//    printf("Name: %sID: %s", person.name, person.ID);
//    ShowBirthday(&person.birthday);
//    
//    if(file != NULL && level > 0){
//        if(person.mother > -1){
//            printf("\nMother of %s", person.ID);
//            ShowPerson(file, ReadPerson(file, person.mother), level - 1);
//        }else{
//            printf("\nNo mother for %s", person.ID);
//        }
//        
//        if(person.father > -1){
//            printf("\nFather of %s", person.ID);
//            ShowPerson(file, ReadPerson(file, person.father), level - 1);
//        }else{
//            printf("\nNo father for %s", person.ID);
//        }
//    }
//}
//
//void ShowAllThePersons(FILE* file, int numberOfPersons){
//    for(int i = 0; i < numberOfPersons; i++){
//        printf("\nPerson #%d\n", i);
//        ShowPerson(NULL, ReadPerson(file, i), 0) ;
//    }
//}
//
//int ChoosePerson(FILE* file, int numberOfPersons){
//    int temp;
//    ShowAllThePersons(file, numberOfPersons);
//    int error;
//    do{
//        printf("\nChoose person (0...%d): ", (numberOfPersons - 1));
//        error = scanf("%d", &temp);
//    }while(temp < 0 || temp > (numberOfPersons - 1) || !error);
//    return temp;
//}
//
//struct Person CreatePerson(FILE* file, int numberOfPersons){
//    struct Person person;
//    printf("Enter person name: ");
//    fflush(stdin);
//    fgets(person.name, maxinmalStringLenght, stdin);
//    printf("Enter person ID: ");
//    fflush(stdin);
//    fgets(person.ID, maxinmalStringLenght, stdin);
//    printf("Birthday\n");
//    person.birthday = createBurthday();
//    
//    person.mother = -1;
//    person.father = -1;
//    
//    if(numberOfPersons){
//        
//        char error;
//        int temp;
//        do{
//            printf("Add (change) mother (0), father(1), noone(2): ");
//            do{
//                rewind(stdin);
//            }while(!scanf("%d", &temp) || temp < 0 || temp > 2);
//            
//            if(temp == 2){
//                return person;
//            }
//            
//            for(int i = 0; i < numberOfPersons; i++){
//                struct Person tempPerson = ReadPerson(file, i);
//                if(CompareBirthdays(tempPerson.birthday, person.birthday) != -1){
//                    continue;
//                }
//                if(i == person.father || i == person.mother){
//                    continue;
//                }
//                
//                error = 2;
//                
//                printf("\n\nPerson #%d\n", i);
//                ShowPerson(NULL, tempPerson, 0);
//            }
//            
//            if(error != 2){
//                printf("\nNo suitable persons\n");
//                break;
//            }
//            int personNumber;
//            do{
//                printf("\nEnter person number: ");
//                error = scanf("%d", &personNumber);
//            }while(personNumber < 0 || personNumber > (numberOfPersons - 1) || !error || (CompareBirthdays(ReadPerson(file, personNumber).birthday, person.birthday) != -1));
//            
//            if(temp == 0){
//                person.mother = personNumber;
//            }
//            if(temp == 1){
//                person.father = personNumber;
//            }
//            
//        }while (temp != 2);
//        
//    }
//    return person;
//}
//
//
//
//int main(){
//    int numberOfPersons = 0;
//    
//    FILE* file = fopen("fourthB", "r+");
//    if(!file){
//        file = fopen("fourthB", "w+");
//    }else{
//        struct Person tempPerson;
//        while(fread(&tempPerson, sizeof(struct Person), 1, file)){
//            numberOfPersons++;
//        }
//        if(numberOfPersons == 0){
//            fclose(file);
//            file = fopen("fourthB", "w+");
//        }
//    }
//
//    
//    int temp;
//    int error;
//    do{
//        printf("\n0: Create a person\n1: Show person and his ancestors \n2: Show all the persons\n3: Remove a person\n4: Save file and close the program\n5: Clean file\n");
//        do{
//            fflush(stdin);
//            error = scanf("%d", &temp);
//        }while(temp < 0 || temp > 5 || !error);
//        switch (temp) {
//            case 0:
//                WritePerson(file, CreatePerson(file, numberOfPersons), numberOfPersons);
//                numberOfPersons++;
//                break;
//            case 1:
//                if(!numberOfPersons){
//                    printf("No persons\n");
//                    break;
//                }
//                int personNumber = ChoosePerson(file, numberOfPersons);
//                char error;
//                do{
//                    printf("Enter the tribe number: ");
//                    error = scanf("%d", &temp);
//                }while(temp < 0 || !error);
//                ShowPerson(file, ReadPerson(file, personNumber), temp);
//                break;
//            case 2:
//                if(!numberOfPersons){
//                    printf("No persons\n");
//                    break;
//                }
//                ShowAllThePersons(file, numberOfPersons);
//                break;
//            case 3:
//                if(!numberOfPersons){
//                    printf("No persons\n");
//                    break;
//                }
//                RemovePerson(file, ChoosePerson(file, numberOfPersons), numberOfPersons);
//                numberOfPersons--;
//                ftruncate(fileno(file), sizeof(struct Person) * numberOfPersons);
//                break;
//            case 4:
//                fclose(file);
//                return 0;
//                break;
//            case 5:
//                fclose(file);
//                file = fopen("fourthB", "w+");
//                numberOfPersons = 0;
//                break;
//        }
//    }while(1);
//}
