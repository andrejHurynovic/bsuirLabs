////
////  lessonThree.c
////  labWorks
////
////  Created by Андрэй Гурыновіч on 3/24/20.
////  Copyright © 2020 Андрэй Гурыновіч. All rights reserved.
////
//
//#include <unistd.h>
//#include <stdio.h>
//
//
//struct Interval{
//    int left;
//    int right;
//};
//
//
//void deleteIntervalInInterval(FILE* file, struct Interval searchInterval){
//    struct Interval interval;
//    long firstPoint = - 1;
//    long secondPoint = - 1;
//
//    fseek(file, 0, SEEK_SET);
//
//    do{
//        if(fread(&interval, sizeof(struct Interval), 1, file) != 1){
//            break;
//        }
//        if ((searchInterval.left >= interval.left && searchInterval.left <= interval.right) || (searchInterval.right >= interval.left && searchInterval.right <= interval.right)) {
//            if(firstPoint == -1){
//                firstPoint = ftell(file) - sizeof(struct Interval);
//            }
//            secondPoint = ftell(file);
//        }
//    }while(1);
//
//    if(firstPoint == -1){
//        return;
//    }
//    fseek(file, secondPoint, SEEK_SET);
//    long shift = secondPoint - firstPoint;
//    while(fread(&interval, sizeof(struct Interval), 1, file) == 1){
//        fseek(file, -shift - sizeof(struct Interval), SEEK_CUR);
//        fwrite(&interval, sizeof(struct Interval), 1, file);
//        fseek(file, shift, SEEK_CUR);
//    }
//    fseek(file, 0, SEEK_END);
//    shift = ftell(file) - shift;
//    ftruncate(fileno(file), shift);
//}
//
//struct Interval createInterval( int left, int right){
//    struct Interval interval;
//    interval.left = left;
//    interval.right = right;
//    return interval;
//}
//
//void WriteInterval(FILE* file, struct Interval interval){
//    fwrite(&interval, sizeof(struct Interval), 1, file);
//}
//
//
//void showInterval(struct Interval intrerval){
//    printf("\nleft: %d, right: %d", intrerval.left, intrerval.right);
//}
//
//void showAllTheInterval(FILE* file){
//    fseek(file, 0, SEEK_SET);
//    struct Interval interval;
//    do{
//        if(fread(&interval, sizeof(interval), 1, file) != 1){
//            break;
//        }
//        showInterval(interval);
//    }while(1);
//}
//
//
//
//int main(){
//    FILE *file  = fopen("Try", "w+b");
//    if(file == NULL){
//        printf("Cannot open file.\n");
//        return 0;
//    }
//
//    WriteInterval(file, createInterval(0, 3));
//    WriteInterval(file, createInterval(4, 7));
//    WriteInterval(file, createInterval(9, 12));
//    WriteInterval(file, createInterval(14, 16));
//
//    deleteIntervalInInterval(file, createInterval(2, 6));
//
//    showAllTheInterval(file);
//}
