//
//  ThreadControl.hpp
//  main
//
//  Created by Andrej Hurynovič on 16.11.21.
//

#ifndef ThreadControl_hpp
#define ThreadControl_hpp

#include <thread>
#include <mutex>
#include <condition_variable>

#define THREAD_RUN  1
#define THREAD_STOP 2
#define THREAD_WAIT 3

#define THREAD_SET_FLAG(mut, condition, flag, status) {  \
    std::lock_guard<std::mutex> lq(mut);                 \
    flag = status;                                       \
    condition.notify_one();                              \
}

#define THREAD_SET_FLAG_RUN(mut, condition, flag) {      \
    std::lock_guard<std::mutex> lq(mut);                 \
    flag = THREAD_RUN;                                   \
    condition.notify_one();                              \
}

#define THREAD_SET_FLAG_STOP(mut, condition, flag) {     \
    std::lock_guard<std::mutex> lq(mut);                 \
    flag = THREAD_STOP;                                  \
    condition.notify_one();                              \
}

#define THREAD_SET_FLAG_WAIT(mut, condition, flag) {     \
    std::lock_guard<std::mutex> lq(mut);                 \
    flag = THREAD_WAIT;                                  \
    condition.notify_one();                              \
}


#endif /* ThreadControl_hpp */
