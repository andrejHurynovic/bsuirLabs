////
////  lessonOne.c
////  labWorks
////
////  Created by Андрэй Гурыновіч on 2/11/20.
////  Copyright © 2020 Андрэй Гурыновіч. All rights reserved.
////
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//
////вектор
//
//struct Student{
//    int id;
//    int name;
//};
//
//struct StudentsVector{
//    struct Student* students;
//    int size;
//    int filled;
//};
//
//struct StudentsVector CreateStudentVector(int size){
//    struct StudentsVector studentsVector;
//    studentsVector.students = malloc(sizeof(struct Student) * size);
//    studentsVector.size = size;
//    studentsVector.filled = 0;
//    return studentsVector;
//}
//
//void AddStudentToVector(struct StudentsVector* studentsVector, struct Student student){
//    studentsVector->students[studentsVector->filled] = student;
//    studentsVector->filled++;
//    if(studentsVector->filled >= studentsVector->size){
//        studentsVector->size *= 2;
//        studentsVector->students = realloc(studentsVector->students, sizeof(struct Student) * studentsVector->size);
//    }
//}
//
//
//
////Вывести наиболее часто встречающуюся букву
//
//
//
//struct SymbolWithCounter{
//    char symbol;
//    int counter;
//};
//
//struct SymbolWithCounter func(char* string){
//    struct SymbolWithCounter symbolWithCounter;
//    int array[256] = {};
//    for(int i = 0; i < strlen(string); i++){
//        array[(int)string[i]]++;
//    }
//
//    int temp = array[0];
//    char symbol = (char)0;
//
//    for(int i = 1; i < 256; i++){
//        if(array[i] > temp){
//            temp = array[i];
//            symbol = (char)i;
//        }
//        symbolWithCounter.symbol = symbol;
//        symbolWithCounter.counter = temp;
//    }
//    return symbolWithCounter;
//}
