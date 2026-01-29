#pragma once
#ifndef __LOGGER_HPP
#define __LOGGER_HPP

namespace logger {
    void info(const char* message);
    void warn(const char* message);
    void err(const char* message);

} // namespace logger


#endif