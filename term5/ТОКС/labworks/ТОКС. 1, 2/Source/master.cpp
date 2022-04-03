//
//  cmain.cpp
//  TFCN, 2
//
//  Created by Andrej Hurynovič on 23.10.21.
//
//
#include <iostream>
#include "Package.hpp"
#include "Pseudoports.hpp"

#include <array>
#include <sstream>

using namespace::std;

static int portMode = 1;

void clearTerm() {
    system("clear");
}

void confirmation() {
    cout << "\nconfirm to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.ios_base::clear();
    getchar();
    clearTerm();
}

void menuOut(Pseudoports &port) {
    cout << "Port name: " << port.getPortName();
    cout << endl << "Port mode: " << portMode;
    cout << endl;
    cout << "1. Send message." << endl;
    cout << "2. Accept message." << endl;
    cout << endl;
    cout << "3. Send package." << endl ;
    cout << "4. Accept package." << endl;
    cout << endl;
    cout << "5. Change speed." << endl;
    cout << "6. Change mode." << endl;
    cout << endl;
    cout << "7. Exit." << endl;
}

void changeSpeed(Pseudoports &port) {
    std::string speed;
    cout << "Type speed: ";
    cin >> speed;

    port.changeSpeed(stoi(speed));

    confirmation();
}

void changeMode(Pseudoports &P) {
    cout << "\tPort mode\n";
    cout << "1. Read. " << "2. Write";
    cin >> portMode;

    confirmation();
}

void sendPackage(Pseudoports &P) {
    if (portMode != 2) {
        cout << "Port mode: Read.\n";
        cout << "In this mode, you cannot send a pack.";
        confirmation();
        return;
    }

    char message[packDataMaximalSize];
    cout << "Set message pack: ";
    cin >> message;

    Package pack;
    pack.changeData(message);
    pack.start();

    std::stringstream ss;
    boost::archive::text_oarchive wr(ss);
    wr & pack;
    cout << "\ndispatch...." << endl;
    P.writePort(ss.str());

    confirmation();
    return;
}

void sendMessage(Pseudoports &P) {
    if (portMode != 2) {
        cout << "Port mode: Read.\n";
        cout << "In this mode, you cannot send a message.";
        confirmation();
        return;
    }

    std::string message;
    cout << "Set message: ";
    cin >> message;
    P.writePort(message);

    confirmation();
}

void closePort(Pseudoports &P) {
    P.closePort();
    portMode = 0;

    confirmation();
}

void acceptMessage(Pseudoports &P) {
    if (portMode != 1) {
        cout << "Port mode: Write.\n";
        cout << "It is impossible to receive a message in this mode.";
        confirmation();
        return;
    }

    size_t size;
    cout << "Set size: ";
    cin >> size;
    cout << "Waiting for a message....";

    string message = P.readPort(size);
    clearTerm();
    cout << "Message: " << message;

    confirmation();
}

void acceptPack(Pseudoports &P) {
    if (portMode != 1) {
        cout << "Port mode: Write.\n";
        cout << "It is impossible to receive a pack in this mode.";
        confirmation();
        return;
    }

    Package pack;

    stringstream ss(P.readPort(maxPackSize));
    boost::archive::text_iarchive rd(ss);

    rd & pack;

    cout << pack;

    confirmation();
}

int main(int argc, const char * argv[]) {
    try {
        Pseudoports P;
        P.create_port();

        array<function<void(Pseudoports &)>, 7> menu = {
            sendMessage,
            acceptMessage,
            sendPackage,
            acceptPack,
            changeSpeed,
            changeMode
        };

        unsigned int answer = 0;
        while(true) {
            menuOut(P);
            cin >> answer;
            answer--;

            if (answer > 6)
                break;
            clearTerm();
            menu[answer](P);
        }

    } catch (std::string const &message) {
        std::cout << "\t-Error-\n" << std::endl;
        std::cout << message << std::endl;
    }
    
    return 0;
}

