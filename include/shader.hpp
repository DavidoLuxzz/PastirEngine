#pragma once
#ifndef __SHADER_HPP
#define __SHADER_HPP


namespace shader {

    enum shader_e {
        NONE,
        CUSTOM_COLOR,

        NUM_SHADERS
    };

    int buildAll();
    void use(shader_e);
    void destroyAll();
    
} // namespace shader



#endif