#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

namespace Render{

#ifndef DEBUG
    #define LOG(M, ...)
    #define INFO(M, ...)
    #define WARN(M, ...)
    #define FATAL(M, ...)
#else
    #define LOG(M, ...)     fprintf(stdout, "[LOG] (%s:%d): " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
    #define INFO(M, ...)    fprintf(stdout, "[INFO] (%s:%d): " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
    #define WARN(M, ...)    fprintf(stdout, "[WARN] (%s:%d): " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
    #define FATAL(M, ...)   fprintf(stderr, "[FATAL] (%s:%d): " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

}

#endif