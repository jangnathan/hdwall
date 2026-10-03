#include <iostream>

using namespace std;

#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"

#define LOG_INFO(msg) cout << "INFO: " << msg << "\n";
#define LOG_ERROR(msg) cout << COLOR_RED "ERROR: " << msg << "\n" COLOR_RESET;

#ifndef DEBUG_MODE
#define LOG_DEBUG(msg) cout << COLOR_YELLOW "DEBUG: " << msg << "\n" COLOR_RESET;
#else
#define LOG_DEBUG(msg) do {} while (0);
#endif
