//
//  StationMonitor.hpp
//  main
//
//  Created by Andrej Hurynovič on 16.11.21.
//

#ifndef StationMonitor_hpp
#define StationMonitor_hpp

#include <list>
#include <sstream>

#include "ThreadControl.hpp"
#include "Pseudoterminal.hpp"
#include "Error.hpp"

class StationMonitor : public Pseudoterminal {
private:
    unsigned int id;
    unsigned int priority;
    unsigned int regime;
public:
    StationMonitor();
   ~StationMonitor();

    bool start(const std::string &adress);
    void stop();

    void send_marker();

    void set_priority_mode(const unsigned int &priority);
    void set_early_release_regime(const unsigned int &flag);

    bool get_priority_mode();
    bool get_early_release_regime();
private:
    void create_marker();
    void check_marker();

    void check_early_release_regime();

    void thread_start() override;
    void thread_read() override;
    void send_status(Status &S);
};

#endif /* StationMonitor_hpp */
