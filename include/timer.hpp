#ifndef TIMER_H
#define TIMER_H

#include <cstdint>

namespace Render{

    class Timer{
    public:
        Timer();
        ~Timer() = default;
        uint64_t frequency, lastTime, currTime, startTime;

        float getDelta();
        float getTime();
        void update();
    };

}

#endif