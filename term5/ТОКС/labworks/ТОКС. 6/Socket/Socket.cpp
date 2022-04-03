//
//  Socket.cpp
//  LabWork_6
//
//  Created by Andrej Hurynovič on 22.11.21.
//

#include "Socket.hpp"

void Socket::change_domain(const int domain) noexcept {
    this->domain = domain;
}

void Socket::change_type(const int type) noexcept {
    this->type = type;
}

void Socket::change_protocol(const int protocol) noexcept {
    this->protocol = protocol;
}

void Socket::start() {
    create();
    init_server_sockaddr();
    bind_name();
}

void Socket::stop() {
    if (is_open()) {
        shutdown(this->sDescriptor, SHUT_RDWR);
        this->sDescriptor = -1;
    }
}

bool Socket::is_open() {
    return this->sDescriptor > 0;
}

void Socket::create() {
    this->sDescriptor = socket(this->domain, this->protocol, this->type);

    if (this->sDescriptor < 0)
        throw Error("Socket: Unable to create socket.");
}

void Socket::init_server_sockaddr() noexcept {
    this->sAddr.sin_family = this->domain;
    this->sAddr.sin_port = this->port;
    this->sAddr.sin_addr.s_addr = htonl(INADDR_ANY);
}

void Socket::init_client_sockaddr() noexcept {
    this->sAddr.sin_family = this->domain;
    this->sAddr.sin_port = this->port;
}

void Socket::bind_name() {
    if (bind(this->sDescriptor, reinterpret_cast<struct sockaddr *>(&this->sAddr),
             sizeof(this->sAddr)) < 0)
        throw Error("Socket: bind.");
}
