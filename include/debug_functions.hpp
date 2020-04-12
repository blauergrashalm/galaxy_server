#ifndef DEBUG_FUNCTIONS
#define DEBUG_FUNCTIONS

#include <iostream>
#include <string>

#define DBG_LOG(level, msg) print_log(level, __FILE__, __LINE__, __PRETTY_FUNCTION__, msg)

enum level
{
    LOW,
    MEDIUM,
    HIGH
};

template <typename m_t>
inline void print_log(level l, std::string file, int line, std::string func, m_t msg)
{
#ifdef DEBUG_HIGH
    std::cout << file << ":" << line << " in " << func << ":\n"
              << msg << std::endl;
#endif
#ifdef DEBUG_MEDIUM
    if (l <= MEDIUM)
        std::cout << file << ":" << line << " in " << func << ":\n"
                  << msg << std::endl;
#endif
#ifdef DEBUG_LOW
    if (l == LOW)
        std::cout << file << ":" << line << " in " << func << ":\n"
                  << msg << std::endl;
#endif
}

#endif