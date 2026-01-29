#include <logger.hpp>

#include <iostream>

void logger::info(const char* msg) {
    fprintf(stdout, "%s\n", msg);
}

void logger::warn(const char* msg) {
    fprintf(stdout, "[WARN] %s\n", msg);
}

void logger::err(const char* msg) {
    fprintf(stderr, "[ERROR] %s\n", msg);
}