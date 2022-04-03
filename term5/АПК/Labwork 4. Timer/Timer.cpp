#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <iostream.h>


int frequencies[] = {196, 261, 329, 196, 261, 329, 196, 261, 329};

int duration[] = {400, 400, 400, 400, 400, 400, 400, 400, 400};

void sound(int frequency, int time) {
    int cnt;

    // b6 = 10100110    10 – channel 2, 11 – read / write low and high bytes 011 – rectangular pulses, 0 – 16 bits code
    outp(0x43, 0xb6);  //timer mode 2


    cnt = (int)(1193180L / frequency);
    //out two bits of port 42h
    outp(0x42, cnt & 0x00ff );
    outp(0x42, (cnt & 0xff00) >> 8);

    //enable system speaker, 3 = 00000011
    outp(0x61, inp(0x61) | 3);

    delay(time);

    //disable system speaker, fc = 11111100
    outp(0x61, inp(0x61) & 0xfc);
}

void stateChannel() {
    unsigned char temp;
    char* string = new char[9];
    unsigned i;

    //state word 0
    //e2 = 11100010
    outp(0x43, 0xe2);

    temp = inp(0x40); // получение слова состояния канала
    itoa(temp, string, 2);
    cout << "0 channel state word: " << string << endl;

    //state word 1
    //e4 = 01001110
    outp(0x43, 0xe4);

    temp = inp(0x40);
    itoa(temp, string, 2);
    cout << "1 channel state word: " << string << endl;

    //state word 2
    //e8 = 11101000
    outp(0x43, 0xe8);

    temp = inp(0x40);
    itoa(temp, string, 2);
    cout << "2 channel state word: " << string << endl;

    free(string);
}

int main(){
    for(int i = 0; i != 8; i++) {
        sound(frequencies[i], duration[i]);
    }
    stateChannel();
    return 0;
}
