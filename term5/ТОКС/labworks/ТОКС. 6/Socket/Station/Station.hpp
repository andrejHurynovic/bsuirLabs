//
//  Station.hpp
//  LabWork_6
//
//  Created by Andrej Hurynovič on 22.11.21.
//

#ifndef Station_hpp
#define Station_hpp

#include "Socket.hpp"
#include "IPv4.hpp"
#include "Package.hpp"
#include "Status.h"

class Station : public Socket {
private:
    int cDescriptor;
    unsigned int queue;

public:
    constexpr Station() : cDescriptor(-1), queue(20) {}
    constexpr Station(const unsigned int queue) : cDescriptor(-1), queue(queue) {
    }

    ~Station() {
        stop();
    }

    void change_queue(const unsigned int queue) noexcept;

    void start() override;
    void stop() override;

    bool is_open() override;

    void send_pack(Package &P);
    Package& get_pack();

    void set_queue_connect(const unsigned int &queue);
    void accept_connection();
private:

    unsigned int get_status();
    void send_status(Status &S);
};

#endif /* Station_hpp */
