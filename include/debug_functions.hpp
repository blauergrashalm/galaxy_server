#ifndef DEBUG_FUNCTIONS
#define DEBUG_FUNCTIONS

#include <iostream>
#include <string>

#define DBG_LOG(level, msg) print_log(level, __FILE__, __LINE__, msg)

enum level
{
    LOW,
    MEDIUM,
    HIGH
};

template <typename... Args>
inline void print_log(level l, std::string file, int line, std::string msg)
{
#ifdef DEBUG_HIGH
    std::cout << file << ":" << line << " :\n\t" << msg << std::endl;
#endif
#ifdef DEBUG_MEDIUM
    if (level <= MEDIUM)
        std::cout << file << ":" << line << " :\n\t" << msg << std::endl;
#endif
#ifdef DEBUG_LOW
    if (level == LOW)
        std::cout << file << ":" << line << " :\n\t" << msg << std::endl;
#endif
}

#endif