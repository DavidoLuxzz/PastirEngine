#include <logger.hpp>
#include <iostream>
#include <cstdarg>

#include <colors.h>

void logger::info(const char* msg) {
    fprintf(stdout, "%s%s\n", LOGGER_INFO_PREFIX, msg);
}
void logger::warn(const char* msg) {
    fprintf(stdout, "%s%s%s%s\n", TERMINAL_COLOR_YELLOW_BOLD, LOGGER_WARN_PREFIX, TERMINAL_COLOR_RESET, msg);
}
void logger::err(const char* msg) {
    fprintf(stderr, "%s%s%s%s\n", TERMINAL_COLOR_RED_BOLD, LOGGER_ERROR_PREFIX, TERMINAL_COLOR_RESET, msg);
}