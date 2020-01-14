#include <time.h>
#include <timer.hpp>

#include <iostream>

//TODO: make a version of this that uses windows instead of POSIX?

namespace Render{

    Timer::Timer(){
        lastTime = currTime = 0;
        
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        startTime = ((uint64_t) ts.tv_sec * 1000000000 + (uint64_t) ts.tv_nsec);

        #if defined(_POSIX_TIMERS) && defined(_POSIX_MONOTONIC_CLOCK)
            if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0){
                frequency = 1000000000;
            }else
        #endif
            {
                frequency = 1000000;
            }
    }

    float Timer::getDelta(){
        return (currTime - lastTime)/(float)frequency;
    }

    void Timer::update(){
        lastTime = currTime;

        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        currTime = ((uint64_t) ts.tv_sec * 1000000000 + (uint64_t) ts.tv_nsec);
    }

    float Timer::getTime(){
        return (currTime - startTime)/(float)frequency;
    }

}