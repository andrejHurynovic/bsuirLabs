////
////  union.c
////  lections
////
////  Created by Андрэй Гурыновіч on 2/15/20.
////  Copyright © 2020 Андрэй Гурыновіч. All rights reserved.
////
//
//#include <stdio.h>
//
//
////Фактически для объявления структуры с разными вариантами содержащихся переменных
//
////Выделет памяти под максимальный элемент
//
//struct all {
//    int type;
//    union {
//        struct {
//            char a;
//        } first;
//        struct{
//            int b;
//        } second;
//    } allInUnion;
//};
//
//
//
////struct bitField{
////    int i1: 1, i2: 1, i3: 1, i4: 1, i5: 1, i6: 1, i7: 1, i8: 1, i9: 1, i10: 1, i11: 1, i12: 1, i13: 1, i14: 1, i15: 1, i16: 1;
////};
////
////int main(){
////    struct bitField field;
////    int number = 1;
////    (int)field.i1 = number;
////
////}
//
//#include <stdio.h>
// 
// 
//union code {
//    int number;
//    struct{
//        unsigned a0:1, a1:1, a2:1, a3:1, a4:1, a5:1, a6:1, a7:1, a8:1, a9:1, a10:1, a11:1, a12:1, a13:1, a14:1, a15:1, a16:1, a17:1, a18:1, a19:1, a20:1, a21:1, a22:1, a23:1, a24:1, a25:1, a26:1, a27:1, a28:1, a29:1, a30:1, a31:1;
//    } byte;
//};
// 
//
////В любых кодах положительные числа выглядят одинаково, вывод внизу - дополнительный код, вот так вот!
//
//
// 
//int main() {
//    union code code;
//    code.number = -2147483647;
//    printf("31  30  29  28  27  26  25  24  23  22  21  20  19  18  17  16  15  14  13  12  11  10   9   8   7   6   5   4   3   2   1   0\n");
//    printf(" %d\t %d \t %d \t %d \t %d \t %d \t %d \t %d\t %d\t %d \t %d \t %d \t %d \t %d \t %d \t %d \t %d \t %d \t %d \t %d \t %d \t %d \t %d \t %d\t %d\t %d \t %d \t %d \t %d \t %d \t %d \t %d \n", code.byte.a31, code.byte.a30, code.byte.a29, code.byte.a28, code.byte.a27, code.byte.a26, code.byte.a25, code.byte.a24, code.byte.a23, code.byte.a22, code.byte.a21, code.byte.a20, code.byte.a19, code.byte.a18, code.byte.a17, code.byte.a16, code.byte.a15, code.byte.a14, code.byte.a13, code.byte.a12, code.byte.a11, code.byte.a10, code.byte.a9, code.byte.a8, code.byte.a7, code.byte.a6, code.byte.a5, code.byte.a4, code.byte.a3, code.byte.a2, code.byte.a1, code.byte.a0);
//    return 0;
//}
