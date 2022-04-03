//
//  main.cpp
//  LabWork_4
//
//  Created by Belousov Ilya on 28.10.21.
//

#include <iostream>
#include <map>
#include <thread>

#include "Pseudoterminal.hpp"
#include "Package.hpp"
#include "Cropping.hpp"

using namespace::std;

void interface(Pseudoterminal &Ps);

void send_msg(Pseudoterminal &Ps);
void send_pack(Pseudoterminal &Ps);
void send_frame(Pseudoterminal &Ps);

void accept_msg(Pseudoterminal &Ps);
void accept_pack(Pseudoterminal &Ps);
void accept_frame(Pseudoterminal &Ps);

void open_port(Pseudoterminal &Ps);
void change_speed_in(Pseudoterminal &Ps);
void change_speed_out(Pseudoterminal &Ps);
void close_port(Pseudoterminal &Ps);

void connect_port(Pseudoterminal &Ps);
void disconnect_port(Pseudoterminal &Ps);

void start_thread_read(Pseudoterminal &Ps);

void out_list_connect_device(Pseudoterminal &Ps);

void open_dylib();
void clear_buffer();
void clear_terminal();
void confirmation();
bool check_status(Pseudoterminal &Ps, string &str);

int main(int argc, const char * argv[]) {
    Pseudoterminal Ps;
    map<int, function<void(Pseudoterminal &Ps)>> menu {
        {1, send_msg},
        {2, send_pack},
        {3, send_frame},

        {4, accept_msg},
        {5, accept_pack},
        {6, accept_frame},

        {7, open_port},
        {8, change_speed_in},
        {9, change_speed_out},
        {10, close_port},

        {11, connect_port},
        {12, disconnect_port},
        {13, out_list_connect_device}
    };

    unsigned int answer = 0;
    while (true) {
        interface(Ps);

        cin >> answer;
        clear_terminal();

        if (answer == menu.size() + 1)
            break;

        try {
            menu.find(answer)->second(Ps);
            confirmation();
        } catch (...) {
            Error::char_arr_error("Func: main().\nInfo: Incorrect input!");

            if (cin.ios_base::fail())
                clear_buffer();

            confirmation();
        }
    }

    return 0;
}

void clear_buffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.ios_base::clear();
}

void clear_terminal() {
    system("clear");
}

void confirmation() {
    cout << "\nconfirm to continue...";
    clear_buffer();
    getchar();
    clear_terminal();
}

void interface(Pseudoterminal &Ps) {
    cout << "Port name: " << Ps.get_port_name();
    cout << "\n\t---Menu---\n";
    cout << "\n";
    cout << "1. Send msg.\n";
    cout << "2. Send pack.\n";
    cout << "3. Send frame.\n";
    cout << "\n";
    cout << "4. Accept msg.\n";
    cout << "5. Accept pack\n";
    cout << "6. Accept frame.\n";
    cout << "\n";
    cout << "7. Open port.\n";
    cout << "8. Change speed in port.\n";
    cout << "9. Change speed in out.\n";
    cout << "10. Close port\n";
    cout << "\n";
    cout << "11. Connect port.\n";
    cout << "12. Disconnect port.\n";
    cout << "13. List connect device.\n";
    cout << "\n";
    cout << "14. Exit.\n";
    cout << "Answer: ";
}

void send_msg(Pseudoterminal &Ps) {
    if (!Ps.is_open()) {
        Error::char_arr_error("Func: send_msg.\nInfo: The port has not been created!");
        return;
    }
    if (Ps.get_count_connect() == 0) {
        Error::char_arr_error("Func: send_msg.\nInfo: Connect to at least one device to transfer data!");
        return;
    }

    string msg;
    cout << "Input msg: ";
    clear_buffer();
    getline(cin, msg);

    cout << "Select Device:\n";
    out_list_connect_device(Ps);

    unsigned int device;
    cout << "Answer: ";
    cin >> device;
    Ps.write_port(msg, device);
}

void send_pack(Pseudoterminal &Ps) {
    if (!Ps.is_open()) {
        Error::char_arr_error("Func: send_pack.\nInfo: The port has not been created!");
        return;
    }
    if (Ps.get_count_connect() == 0) {
        Error::char_arr_error("Func: send_pack.\nInfo: Connect to at least one device to transfer data!");
        return;
    }

    char data[MAX_SIZE_PACK_DATA];
    cout << "Input data: ";
    clear_buffer();
    fgets(data, MAX_SIZE_PACK_DATA, stdin);

    cout << "Select Device:\n";
    out_list_connect_device(Ps);

    unsigned int device;
    cout << "Answer: ";
    cin >> device;

    Package P;
    P.change_data(data);
    P.set_sender(Ps.get_port_name());
    P.set_recipiend(Ps.get_list_network()[device].first);
    P.start();

    stringstream ss;
    boost::archive::text_oarchive wr(ss);
    wr & P;
    cout << Ps.write_port(ss.str(), device);
}

void send_frame(Pseudoterminal &Ps) {
    if (!Ps.is_open()) {
        Error::char_arr_error("Func: send_frame.\nInfo: The port has not been created!");
        return;
    }
    if (Ps.get_count_connect() == 0) {
        Error::char_arr_error("Func: send_frame.\nInfo: Connect to at least one device to transfer data!");
        return;
    }

    char data[MAX_SIZE_PACK_DATA];
    cout << "Input data: ";
    clear_buffer();
    fgets(data, MAX_SIZE_FRAME_DATA, stdin);

    cout << "Select Device:\n";
    out_list_connect_device(Ps);

    unsigned int device;
    cout << "Answer: ";
    cin >> device;

    Cropping C;
    C.set_sender(Ps.get_port_name());
    C.set_recipiend(Ps.get_list_network()[device].first);
    C.change_data(data);
    C.start();

    stringstream ss;
    boost::archive::text_oarchive wr(ss);
    wr & C;
    Ps.write_port(ss.str(), device);
}

void accept_msg(Pseudoterminal &Ps) {
    if (!Ps.is_open()) {
        Error::char_arr_error("Func: accept_msg.\nInfo: The port has not been created!");
        return;
    }

    size_t size;
    cout << "Input size msg: ";
    cin >> size;

    cout << "Msg: " << Ps.read_port(size);
}

void accept_pack(Pseudoterminal &Ps) {
    if (!Ps.is_open()) {
        Error::char_arr_error("Func: accept_msg.\nInfo: The port has not been created!");
        return;
    }
    cout << "Waiting for package to be received.\n";
    string str(Ps.read_port(MAX_SIZE_PACK));
    stringstream ss(str);
    Package P;
    try {
        boost::archive::text_iarchive rd(ss);
        rd & P;
    } catch (...) {
        if (check_status(Ps, str))
            return;
        Error::char_arr_error("Func: accept_pack.\nInfo: The package was damaged!");
        Ps.collision();
        return;
    }

    cout << P;
}

void accept_frame(Pseudoterminal &Ps) {
    if (!Ps.is_open()) {
        Error::char_arr_error("Func: accept_msg.\nInfo: The port has not been created!");
        return;
    }
    cout << "Waiting to receive a frame.\n";
    string str = Ps.read_port(MAX_SIZE_FRAME);
    stringstream ss(str);

    Cropping C;
    boost::archive::text_iarchive rd(ss);
    try {
        rd & C;
    } catch (...) {
        if (check_status(Ps, str))
            return;
        Error::char_arr_error("Func: accept_pack.\nInfo: The frame was damaged!");
        Ps.collision();
        return;
    }
    cout << C;
}

void open_port(Pseudoterminal &Ps) {
    if (!Ps.create_port())
        return;

    cout << "The port was created: " << Ps.get_port_name() << endl;
}

void change_speed_in(Pseudoterminal &Ps) {
    speed_t speed;
    cout << "Set speed in: ";
    cin >> speed;
    Ps.change_speed_in(speed);
}

void change_speed_out(Pseudoterminal &Ps) {
    speed_t speed;
    cout << "Set speed out: ";
    cin >> speed;
    Ps.change_speed_out(speed);
}

void close_port(Pseudoterminal &Ps) {
    if (!Ps.is_open()) {
        Error::char_arr_error("Func: Main::close_port.\nInfo: The port is already closed!\n");
        return;
    }

    Ps.close_port();
    cout << "Port closed successfully" << endl;
}

void connect_port(Pseudoterminal &Ps) {
    if (!Ps.is_open()) {
        Error::char_arr_error("Func: send_frame.\nInfo: The port has not been created!");
        return;
    }

    string device;
    cout << "Input device name: ";
    cin >> device;

    if (!Ps.connect(device)) {
        Error::char_arr_error("Func: connect_port.\nInfo: Connection failed!");
        return;
    }
    cout << "Connection successful!\n";
}

void disconnect_port(Pseudoterminal &Ps) {
    if (!Ps.is_open()) {
        Error::char_arr_error("Func: disconnect port.\nInfo: The port has not been created!");
        return;
    }
    if (Ps.get_count_connect() == 0) {
        Error::char_arr_error("Func: disconnect port.\nInfo: Connect to at least one device to transfer data!");
        return;
    }

    cout << "Select Device:\n";
    out_list_connect_device(Ps);

    unsigned int device;
    cout << "Answer: ";
    cin >> device;

    Ps.disconnect(device);
    cout << "Device disconnected successfully!\n";
}

void start_thread_read(Pseudoterminal &Ps) {
    //    thread thRead(&Pseudoterminal::read_port, Ps, MAX_SIZE_PACK_DATA);
    //    thread thWrite(&Pseudoterminal::write_port, Ps);
}

void open_dylib() {

}

void out_list_connect_device(Pseudoterminal &Ps) {
    if (!Ps.is_open()) {
        Error::char_arr_error("Func: out_list_connect_device.\nInfo: The port has not been created!");
        return;
    }
    if (Ps.get_count_connect() == 0) {
        Error::char_arr_error("Func: out_list_connect_device.\nInfo: Connect to at least one device to transfer data!");
        return;
    }
    cout << "\tList device\n";
    map listDevice = Ps.get_list_network();
    int counter = 0;
    for (auto device : listDevice) {
        cout << counter << "." << device.second.first << "\n";
        counter++;
    }
}

bool check_status(Pseudoterminal &Ps, string &str) {
    stringstream ss(str);
    status s;
    try {
        boost::archive::text_iarchive rd(ss);
        rd & s;
        if (s.flag == connect) {
            Ps.accept_connect(s.sender);
        } else if (s.flag == disconnect) {
            Ps.accept_disconnect(Ps.find_device(s.sender));
        } else if (s.flag == error) {
            Ps.resending(s.sender);
        }
    } catch (...) {
        return false;
    }

    return true;
}
