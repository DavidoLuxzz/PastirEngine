#pragma once
#ifndef __GLOBAL_VARS_HPP
#define __GLOBAL_VARS_HPP

namespace global {
    struct vars {
        bool running;
    };

    vars& get();
} // namespace global


#endif