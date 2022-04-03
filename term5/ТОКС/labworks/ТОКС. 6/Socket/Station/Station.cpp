//
//  Station.cpp
//  LabWork_6
//
//  Created by Andrej Hurynovič on 22.11.21.
//

#include "Station.hpp"

void Station::start() {
    create();
    init_server_sockaddr();
    bind_name();
    set_queue_connect(20);
    accept_connection();
}

void Station::stop() {
    if (is_open()) {
        shutdown(this->cDescriptor, SHUT_RDWR);
        this->cDescriptor = -1;
    }
}

bool Station::is_open() {
    return this->cDescriptor > 0;
}

void Station::set_queue_connect(const unsigned int &queue) {
    this->queue = queue;
    if (listen(this->sDescriptor, this->queue) < 0)
        throw Error("Station: Failed set queue connect.");
}

void Station::accept_connection() {
    socklen_t len = sizeof(this->sAddr);
    this->cDescriptor = accept(this->sDescriptor, reinterpret_cast<struct sockaddr *>(&this->sAddr), &len);

    if (this->cDescriptor < 0)
        throw Error("Station: Failed to accept connections.");
}

void Station::send_pack(Package &P) {
    std::stringstream ss;
    boost::archive::text_oarchive writer(ss);
    writer & P;

    if (send(this->cDescriptor, ss.str().c_str(), MAX_SIZE_PACK, 0) < 0)
        throw Error("Station: Failed to send message.");

    if (get_status() != PACKAGE_RECEIVED)
        throw Error("Station: Failed to get status.");

}

Package& Station::get_pack() {
    char msg[MAX_SIZE_PACK];

    if (recv(this->cDescriptor, msg, MAX_SIZE_PACK, 0) < 0)
        throw Error("Station: Failed to receive message.");

    Package P;
    std::stringstream ss(msg);
    boost::archive::text_iarchive reader(ss);
    reader & P;

    Status S;
    S.flag = PACKAGE_RECEIVED;
    send_status(S);

    return P;
}

void Station::send_status(Status &S) {
    std::stringstream ss;
    boost::archive::text_oarchive writer(ss);
    writer & S;

    if (send(this->cDescriptor, ss.str().c_str(), ss.str().size(), 0) < 0)
        throw Error("Station: Failed to send message.");
}

unsigned int Station::get_status() {
    char msg[MAX_SIZE_STATUS];

    if (recv(this->cDescriptor, msg, MAX_SIZE_STATUS, 0) < 0)
        throw Error("Station: Failed to receive message.");

    Status S;
    std::stringstream ss(msg);
    boost::archive::text_iarchive reader(ss);
    reader & S;

    return S.flag;
}
