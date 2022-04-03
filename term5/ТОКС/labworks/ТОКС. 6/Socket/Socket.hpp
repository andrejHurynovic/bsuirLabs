//
//  Socket.hpp
//  LabWork_6
//
//  Created by Andrej Hurynovič on 22.11.21.
//

#ifndef Socket_hpp
#define Socket_hpp

#include "Error.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <arpa/inet.h>

class Socket {
protected:
    int sDescriptor;

    int domain;
    int type;
    int protocol;
    int port;

    struct sockaddr_in sAddr;

public:
    constexpr Socket() : domain{AF_INET}, protocol{SOCK_STREAM}, type{0}, port(8080), sDescriptor{-1} {
        memset(&sAddr, 0, sizeof(sockaddr));
    }
    constexpr Socket(const int domain, const int protocol,
                     const int type, const unsigned int port) : domain{domain}, protocol{protocol}, type{type}, port(port), sDescriptor{-1} {
        memset(&sAddr, 0, sizeof(sockaddr));
    }

    virtual ~Socket() {
        stop();
    }

    void change_domain(const int domain) noexcept;
    void change_type(const int type) noexcept;
    void change_protocol(const int protocol) noexcept;

    virtual void start();
    virtual void stop();

    virtual bool is_open();

protected:
    void create();
    void init_server_sockaddr() noexcept;
    void init_client_sockaddr() noexcept;
    void bind_name();
};


#endif /* Socket_hpp */
