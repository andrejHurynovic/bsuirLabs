//
//  Client.cpp
//  LabWork_6
//
//  Created by Andrej Hurynovič on 23.11.21.
//

#include "Client.hpp"

void Client::start() {
    create();
    init_client_sockaddr();
    convert_ip();
    connect_to_server();
}

void Client::set_ip(const IPv4 &ip) {
    this->ip = ip;
}

void Client::convert_ip() {
    if (inet_pton(AF_INET, this->ip.to_string().c_str(), &this->sAddr.sin_addr) != 1) {
        throw Error("Client::set_ip: inet_pton error");
    }
}
void Client::connect_to_server() {
    if (connect(this->sDescriptor, reinterpret_cast<struct sockaddr *>(&this->sAddr),
                sizeof(sAddr)) < 0)
        throw Error("Client::connect_to_server: Error connect");
}

void Client::send_pack(const Package &pack) {
    std::stringstream ss;
    boost::archive::text_oarchive writer(ss);
    writer & pack;

    std::string s = ss.str();
    if (send(this->sDescriptor, ss.str().c_str(), ss.str().size(), 0) < 0)
        throw Error("Client::send_message: Failed to send message.");

    if (get_status() != PACKAGE_RECEIVED)
        throw Error("Client: Failed to get status.");
}

Package& Client::get_pack() {
    char msg[MAX_SIZE_PACK];

    if (recv(this->sDescriptor, msg, MAX_SIZE_PACK, 0) < 0)
        throw Error("Client::get_message: Failed to receive message.");

    Package P;
    std::stringstream ss(msg);
    boost::archive::text_iarchive reader(ss);
    reader & P;

    Status S;
    S.flag = PACKAGE_RECEIVED;
    send_status(S);

    return P;
}

void Client::send_status(Status &S) {
    std::stringstream ss;
    boost::archive::text_oarchive writer(ss);
    writer & S;

    if (send(this->sDescriptor, ss.str().c_str(), ss.str().size(), 0) < 0)
        throw Error("Client: Failed to send message.");
}

unsigned int Client::get_status() {
    char msg[MAX_SIZE_STATUS];

    if (recv(this->sDescriptor, msg, MAX_SIZE_STATUS, 0) < 0)
        throw Error("Client: Failed to receive message.");

    Status S;
    std::stringstream ss(msg);
    boost::archive::text_iarchive reader(ss);
    reader & S;

    return S.flag;
}
