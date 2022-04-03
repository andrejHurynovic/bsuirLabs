//
//  first.c
//  labWorks
//
//  Created by Андрэй Гурыновіч on 2/14/20.
//  Copyright © 2020 Андрэй Гурыновіч. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//15
//1. Реализовать структуру “сообщение”, которая содержит текст сообщения (обязательно), id отправителя (строка, обязательно), id получателя (строка, обязательно), опционально ссылку на вложение и тип вложения (enum - изображение, видео, бинарный файл). Сделать возможность эмулировать в приложении наличие подключения к сети. При отправке сообщения проверяется наличие сети. Если сети нет, то сообщение должно отправиться при следующем появлении сети. Сделать возможность вывода всех неотправленных сообщений. Добавить поиск среди отправленных сообщений по id получателя.
//2. Добавить список существующих идентификаторов пользователей. При отправке несуществующему пользователю выдавать ошибку. Добавить возможность удаления конкретного сообщения. Добавить возможность ответа на конкретное сообщение (при просмотре сообщения должна быть возможность просмотра сообщения, на которое сделан ответ).

char* createAndScanString(char* description){
    int maxinmalStringLenght = 129;
    char *string;
    char error;
    do{
        error = 0;
        if (!(string = (char *)malloc(maxinmalStringLenght))){
            error = 1;
        }
    }while (error == 1);
    printf("%s", description);
    rewind(stdin);
    fgets(string, maxinmalStringLenght, stdin);
    unsigned long lenght = strlen(string);
    if(lenght < maxinmalStringLenght - 1){
        string = (char*)realloc(string, maxinmalStringLenght - lenght);
        string[lenght - 1] = '\0';
    }
    return string;
}


int scanNumber(char* description){
    int number;
    printf("%s", description);
    do{
        rewind(stdin);
    } while (!scanf("%d", &number));
    return number;
}



struct UsersVector{
    char** users;
    int size;
    int filled;
};

struct UsersVector CreateUsersVector(int size){
    struct UsersVector usersVector;
    usersVector.users= (char**)malloc(sizeof(char*) * size);
    usersVector.size = size;
    usersVector.filled = 0;
    return usersVector;
}


void AddUserToVector(struct UsersVector* usersVector){
    char error;
    char* user;
    
    do{
        error = 0;
        user = createAndScanString("Enter username (maximum of 128 characters): ");
        for(int i = 0; i < usersVector->filled; i++){
            if (!strcmp(usersVector->users[i], user)){
                printf("This user is already exists!\n");
                error = 1;
                break;
            }
        }
    } while (error);
    
    usersVector->users[usersVector->filled] = user;
    usersVector->filled++;
    if(usersVector->filled >= usersVector->size){
        usersVector->size *= 2;
        usersVector->users = (char**)realloc(usersVector->users, sizeof(char*) * usersVector->size);
    }
}

void showAllUsers(struct UsersVector* usersVector){
    if(!usersVector->filled){
        printf("No users\n");
        return;
    }
    for(int i = 0; i < usersVector->filled; i++){
        printf("#%d: %s\n", i , usersVector->users[i]);
    };
}




char* chooseUserByID(struct UsersVector* usersVector, char* except){
    showAllUsers(usersVector);
    int number;
    do{
        number = scanNumber("");
        if(except && number > 0 && number < usersVector->filled){
            if(!strcmp(usersVector->users[number], except)){
                number = -1;
                printf("You can't send a message to yourself\n");
                continue;
            }
        }
        printf("No such user!\n");
    }while(number < 0 || number > usersVector->filled - 1);
    return usersVector->users[number];
}

char* chooseUserManylly(struct UsersVector* usersVector, char* except){
    int error;
    char* user;
    do{
        error = 0;
        user = createAndScanString("Enter username (maximum of 128 characters): ");
        
        if(except && !strcmp(user, except)){
            error = 1;
            printf("You can't send a message to yourself!\n");
            continue;
        }
        for(int i = 0; i < usersVector->filled; i++){
            if(!strcmp(user, usersVector->users[i])){
                return user;
            }
        }
        error = 1;
        printf("No such user, try again!\n");
    }while(error);
    return user;
}


char* chooseUser(struct UsersVector* usersVector, char* except){
    int manually = scanNumber("\nManually? (0/1) ");
    if(manually){
        return chooseUserManylly(usersVector, except);
    } else {
        return chooseUserByID(usersVector, except);
    }
    
}



enum typeOfContent{
    image,
    video,
    binaryFile,
    empty
};

struct Massage{
    char* senderId;
    char* reciverId;

    char* text;

    enum typeOfContent type;
    char* link;

    struct Massage* responseTo;

    int uploaded;
};

struct MassagesVector{
    struct Massage* massages;
    int size;
    int filled;
};

struct MassagesVector CreateMassagesVector(int size){
    struct MassagesVector massagesVector;
    massagesVector.massages = (struct Massage*)malloc(sizeof(struct Massage) * size);
    massagesVector.size = size;
    massagesVector.filled = 0;
    return massagesVector;
}

void AddMassageToVector(struct MassagesVector* massagesVector, struct Massage massage){
    massagesVector->massages[massagesVector->filled] = massage;
    massagesVector->filled++;
    if(massagesVector->filled >= massagesVector->size){
        massagesVector->size *= 2;
        massagesVector->massages = realloc(massagesVector->massages, sizeof(struct Massage) * massagesVector->size);
    }
}

void showMassage(struct Massage massage){
    printf("\nFrom: %s   To: %s", massage.senderId, massage.reciverId);
    printf("\n': %s'", massage.text);
    if(massage.type != empty){
        printf("\nlink: %s", massage.link);
    }
    if (massage.responseTo != NULL){
        printf("\nResponse to: ");
        showMassage(*massage.responseTo);
    }
}

void showAllMassages(struct MassagesVector* massagesVector){
    if(!massagesVector->filled){
        printf("\nNo massages!\n");
        return;
    }
    for(int i = 0; i < massagesVector->filled; i++){
        printf("\n\n#%d:",i);
        showMassage(massagesVector->massages[i]);
    }
}


int chooseMassage(struct MassagesVector* massagesVector){
    showAllMassages(massagesVector);
    if(!massagesVector->filled){
        return -1;
    }
    int number;
    do{
        number = scanNumber("\nChoose massage ID: ");
    }while(number < 0 || number >= massagesVector->filled);
    return number;
}


void removeMassage(struct MassagesVector* massagesVector){
    int massageID = chooseMassage(massagesVector);
    if (massageID == -1){
        return;
    }
    for(int i = massageID; i <= massagesVector->filled - 1; i++){
        if (massagesVector->massages[i].responseTo == &massagesVector->massages[massageID]){
            massagesVector->massages[i].responseTo = NULL;
        }
    }
    massagesVector->filled--;
    for(;massageID < massagesVector->filled; massageID++){
        massagesVector->massages[massageID] = massagesVector->massages[massageID + 1];
    }
}

struct Massage createMassage(struct UsersVector* usersVector, struct MassagesVector* massagesVector, int isResponse){
    struct Massage massage;
    
    if(isResponse){
        isResponse = chooseMassage(massagesVector);
        massage.responseTo = &massagesVector->massages[isResponse];
        massage.senderId = massagesVector->massages[isResponse].reciverId;
        massage.reciverId = massagesVector->massages[isResponse].senderId;
    } else {
        massage.responseTo = NULL;
        
        printf("\nEnter sender username");
        massage.senderId = chooseUser(usersVector, 0);
        
        printf("\nEnter reciver username");
        massage.reciverId = chooseUser(usersVector, massage.senderId);
    }
    
    massage.text = createAndScanString("Enter massage text (maximum of 128 characters): ");
    
    char error = 0;
    do{
        error = 0;
        switch (scanNumber("\nType of content? \n0: Empty \n1: Image \n2: Video \n3: Binary file\n")) {
            case 0:
                massage.type = empty;
                break;
            case 1:
                massage.type = image;
                massage.link = createAndScanString("\nEnter URL (maximum of 128 characters): ");
                break;
            case 2:
                massage.type = video;
                massage.link = createAndScanString("\nEnter URL (maximum of 128 characters): ");
                break;
            case 3:
                massage.type = binaryFile;
                massage.link = createAndScanString("\nEnter URL (maximum of 128 characters): ");
                break;
            default:
                error = 1;
                break;
        }
    }while(error);
    return massage;
};

int main(){
    int haveConection = scanNumber("Have connection? (0/1) ");
    
    
    struct UsersVector usersVector = CreateUsersVector(10);
    printf("\nAdd first two users: \n");
    AddUserToVector(&usersVector);
    AddUserToVector(&usersVector);
    
    
    struct MassagesVector massagesVector = CreateMassagesVector(10);
    struct Massage massage;
    
    
    int error;
    while(1){
        error = 0;
        switch (scanNumber("\n0: Set conection \n1: Create a new user \n2: Show all users \n3: Create a new message  \n4: Show all unuploaded massages \n5: Show all uploaded massages by recivers user ID \n6: Show all massages \n7: Remove a massage\n")) {
            case 0:
                haveConection = scanNumber("\nHave connection? (0/1) ");
                if(haveConection == 1){
                    for(int i = 0; i < massagesVector.filled; i++){
                        massagesVector.massages[i].uploaded = 1;
                    }
                }
                break;
            case 1:
                AddUserToVector(&usersVector);
                break;
                
            case 2:
                showAllUsers(&usersVector);
                break;
            case 3: {}
                int isResponse = 0;
                if(massagesVector.filled){
                    isResponse = scanNumber("Is this a response to another message? (0/1) ");
                }
                
                massage = createMassage(&usersVector, &massagesVector, isResponse);
                if(haveConection == 0){
                    massage.uploaded = 0;
                } else {
                    massage.uploaded = 1;
                }
                
                
                AddMassageToVector(&massagesVector, massage);
                break;
            case 4:{}
                int check = 0;
                for(int i = 0; i < massagesVector.filled; i++){
                    if(massagesVector.massages[i].uploaded == 0){
                        showMassage(massagesVector.massages[i]);
                        check = 1;
                    }
                }
                if(!check){
                    printf("\nNo such massages!\n");
                }
                break;
            case 5:
                if(!massagesVector.filled){
                    printf("\nNo massages!\n");
                    break;
                }
                char* user = chooseUser(&usersVector, 0);
                
                for(int i = 0; i < massagesVector.filled; i++){
                    if(!strcmp(massagesVector.massages[i].reciverId, user) && massagesVector.massages[i].uploaded){
                        showMassage(massagesVector.massages[i]);
                    }
                }
                break;
            case 6:
                showAllMassages(&massagesVector);
                break;
            case 7:
                removeMassage(&massagesVector);
            default:
                error = 1;
                break;
        }
    }
}
