//
//  Client.hpp
//  LabWork_6
//
//  Created by Andrej Hurynovič on 23.11.21.
//

#ifndef Client_hpp
#define Client_hpp

#include "Status.h"
#include "Socket.hpp"
#include "IPv4.hpp"
#include "Package.hpp"

#include <arpa/inet.h>

class Client : public Socket {
private:
    IPv4 ip;
public:
    constexpr Client() : ip{} {
        memset(&sAddr, 0, sizeof(sAddr));
    }
    constexpr Client(const IPv4 &ip) : ip(ip) {
        memset(&sAddr, 0, sizeof(sAddr));
    }

    void start() override;
    void convert_ip();

    void send_pack(const Package &pack);
    Package& get_pack();

    void set_ip(const IPv4 &ip);
private:
    void connect_to_server();

    unsigned int get_status();
    void send_status(Status &S);
};

#endif /* Client_hpp */
