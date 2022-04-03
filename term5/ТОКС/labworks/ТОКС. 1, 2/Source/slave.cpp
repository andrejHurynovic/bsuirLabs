//
//  smain.cpp
//  TFCN, 2
//
//  Created by Andrej Hurynovič on 23.10.21.
//

#include <iostream>
#include "SerialPorts.hpp"
#include <array>
#include <sstream>

using namespace::std;

int portMode = 2;
string namePort;

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

void menuOut(SerialPorts &S) {
    cout << "Port name: " << namePort;
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

void changeSpeed(SerialPorts &S) {
    std::string speed;
    cout << "Set speed: ";
    cin >> speed;

    S.changeSpeed(stoi(speed));

    confirmation();
}

void changeMode(SerialPorts &S) {
    cout << "\tPort mode\n";
    cout << "1. Read. " << "2. Write";
    cin >> portMode;

    confirmation();
}

void sendPackage(SerialPorts &S) {
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
    S.writePort(ss.str());

    confirmation();
    return;
}

void sendMessage(SerialPorts &S) {
    if (portMode != 2) {
        cout << "Port mode: Read.\n";
        cout << "In this mode, you cannot send a message.";
        confirmation();
        return;
    }

    std::string message;
    cout << "Set message: ";
    cin >> message;
    S.writePort(message);

    confirmation();
}

void closePort(SerialPorts &S) {
    S.closePort();
    portMode = 0;

    confirmation();
}

void acceptMessage(SerialPorts &S) {
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

    string message = S.readPort(size);
    clearTerm();
    cout << "Message: " << message;

    confirmation();
}

void acceptPackage(SerialPorts &S) {
    if (portMode != 1) {
        cout << "Port mode: Write.\n";
        cout << "It is impossible to receive a pack in this mode.";
        confirmation();
        return;
    }

    Package pack;

    stringstream ss(S.readPort(maxPackSize));
    boost::archive::text_iarchive rd(ss);

    rd & pack;
    cout << pack;

    confirmation();
}

int main(int argc, const char * argv[]) {
    try {
        SerialPorts S;

        cout << "Set name port: ";
        cin >> namePort;

        S.openPort(namePort);

        array<function<void(SerialPorts &)>, 7> menu = {
            sendMessage,
            acceptMessage,
            sendPackage,
            acceptPackage,
            changeSpeed,
            changeMode
        };

        unsigned int answer = 0;
        while(true) {
            menuOut(S);
            cin >> answer;
            answer--;

            if (answer > 6)
                break;
            clearTerm();
            menu[answer](S);
        }

    } catch (std::string const &message) {
        std::cout << "\t-Error-\n" << std::endl;
        std::cout << message << std::endl;
    }

    return 0;
}

