
#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <utility>

class Logger {
private:
    std::string message;
    std::chrono::steady_clock::time_point start;

public:
    explicit Logger(std::string msg)
        : message(std::move(msg))
        , start(std::chrono::steady_clock::now()) {
    }
    
    ~Logger() {
        auto finish = std::chrono::steady_clock::now();
        auto duration = finish - start;
        
        std::cerr
            << message
            << std::chrono::duration_cast<std::chrono::microseconds>(duration).count()
            << " ms." << std::endl;
    }
};

#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)

#define LOG_DURATION(message) \
    Logger UNIQ_ID(__LINE__) { message };
