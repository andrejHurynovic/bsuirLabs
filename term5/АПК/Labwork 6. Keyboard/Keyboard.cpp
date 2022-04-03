//
//  main.cpp
//  Labwork 6. Keyboard
//
//  Created by Andrej Hurynovič on 9.05.21.
//

#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <iostream.h>

void interrupt far IRQ1(...);
void interrupt far (*originalIRQ1)(...);

void indicator(unsigned char mask);
void blinking(void);

int isResend = 1;
int quitFlag = 0;
int blinkingFlag = 0;

int main() {
    //save original interrupton and setup own
    originalIRQ1 = getvect(0x09);
    setvect(0x09, IRQ1);
    while(!quitFlag) {
        if(blinkingFlag)
            blinking();
    }
    setvect(0x09, originalIRQ1);
    cout << "Press any key to continue..." << endl;
    getch();
    return 0;
}
void interrupt far IRQ1(...) {
    unsigned char value = 0;
    value = inp(0x60);      //get value from 60h port
    if(value == 0x10) {     //10 == 'Q' scan-code
        quitFlag = 1;
    }
    
    if(value == 0x39 && blinkingFlag == 0) {      // 39 == ' ' scan-code
    blinkingFlag = 1;
    } else {
    if(value == 0x39 && blinkingFlag == 1) {
        blinkingFlag = 0;
    }
    }

    if(value != 0xfa && blinkingFlag == 1) {      //no success code
    isResend = 1;
    } else {
    isResend = 0;
    }

    cout << "Key scan-code: "<< hex << (int)value << endl;
    outp(0x20, 0x20);                           //reset interruption controller
}

void indicator(unsigned char mask) {
    isResend = 1;
    while(isResend) {                           //no success command code
        while((inp(0x64)&0x02) != 0x00);        //wait for keyboard bufer update
        outp(0x60, 0xED);                       //indicator control command
        delay(50);
    }
    isResend = 1;
    while(isResend) {                           //no success command code
        while((inp(0x64)&0x02) != 0x00);
        outp(0x60, mask);                       //write mask for this indicator
        delay(50);
    }
}
void blinking(){
    indicator(0x02);                            //enable Num Lock indicator
    delay(150);
    indicator(0x04);                            //enable Caps Lock
    delay(150);
    indicator(0x06);                            //enable Num Lock i Caps Lock
    delay(200);
    indicator(0x00);                            //disable all indicators
    delay(50);
    indicator(0x06);                            //enable Num Lock & Caps Lock indicator
    delay(100);
    indicator(0x00);                            //disable all indicators
    cout << "Blinking end!" << endl;
}
