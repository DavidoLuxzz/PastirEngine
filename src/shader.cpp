#include <shader.hpp>
#include <allegro5/allegro_opengl.h>
#include <iostream>

namespace shader
{
    ALLEGRO_SHADER* shaders[NUM_SHADERS];

    constexpr const char* sources[NUM_SHADERS] = {
        "",

        "#ifdef GL_ES\n"
        "precision lowp float;\n"
        "#endif\n"
        "uniform sampler2D " ALLEGRO_SHADER_VAR_TEX ";\n"
        "uniform bool " ALLEGRO_SHADER_VAR_USE_TEX ";\n"
        "uniform bool " ALLEGRO_SHADER_VAR_ALPHA_TEST ";\n"
        "uniform int " ALLEGRO_SHADER_VAR_ALPHA_FUNCTION ";\n"
        "uniform float " ALLEGRO_SHADER_VAR_ALPHA_TEST_VALUE ";\n"
        "varying vec4 varying_color;\n"
        "varying vec2 varying_texcoord;\n"
        "\n"
        "bool alpha_test_func(float x, int op, float compare);\n"
        "\n"
        "void main()\n"
        "{\n"
        "  vec4 c;\n"
        "  if (" ALLEGRO_SHADER_VAR_USE_TEX ")\n"
        "    c = varying_color * texture2D(" ALLEGRO_SHADER_VAR_TEX ", varying_texcoord);\n"
        "  else\n"
        "    c = varying_color;\n"
        "  if (!" ALLEGRO_SHADER_VAR_ALPHA_TEST " || alpha_test_func(c.a, " ALLEGRO_SHADER_VAR_ALPHA_FUNCTION ", "
                                ALLEGRO_SHADER_VAR_ALPHA_TEST_VALUE "))\n"
        "    gl_FragColor = c;\n"
        "  else\n"
        "    discard;\n"
        "}\n"
        "\n"
        "bool alpha_test_func(float x, int op, float compare)\n"
        "{\n"
        // Note: These must be aligned with the ALLEGRO_RENDER_FUNCTION enum values.
        "  if (op == 0) return false;\n" // ALLEGRO_RENDER_NEVER
        "  else if (op == 1) return true;\n" // ALLEGRO_RENDER_ALWAYS
        "  else if (op == 2) return x < compare;\n" // ALLEGRO_RENDER_LESS
        "  else if (op == 3) return x == compare;\n" // ALLEGRO_RENDER_EQUAL
        "  else if (op == 4) return x <= compare;\n" // ALLEGRO_RENDER_LESS_EQUAL
        "  else if (op == 5) return x > compare;\n" // ALLEGRO_RENDER_GREATER
        "  else if (op == 6) return x != compare;\n" // ALLEGRO_RENDER_NOT_EQUAL
        "  else if (op == 7) return x >= compare;\n" // ALLEGRO_RENDER_GREATER_EQUAL
        "  return false;\n"
        "}\n"
    };

    constexpr const char* default_vertex_source =   "attribute vec4 " ALLEGRO_SHADER_VAR_POS ";\n"
                                                    "attribute vec4 " ALLEGRO_SHADER_VAR_COLOR ";\n"
                                                    "attribute vec2 " ALLEGRO_SHADER_VAR_TEXCOORD ";\n"
                                                    "uniform mat4 " ALLEGRO_SHADER_VAR_PROJVIEW_MATRIX ";\n"
                                                    "uniform bool " ALLEGRO_SHADER_VAR_USE_TEX_MATRIX ";\n"
                                                    "uniform mat4 " ALLEGRO_SHADER_VAR_TEX_MATRIX ";\n"
                                                    "varying vec4 varying_color;\n"
                                                    "varying vec2 varying_texcoord;\n"
                                                    "void main()\n"
                                                    "{\n"
                                                    "  varying_color = " ALLEGRO_SHADER_VAR_COLOR ";\n"
                                                    "  if (" ALLEGRO_SHADER_VAR_USE_TEX_MATRIX ") {\n"
                                                    "    vec4 uv = " ALLEGRO_SHADER_VAR_TEX_MATRIX " * vec4(" ALLEGRO_SHADER_VAR_TEXCOORD ", 0, 1);\n"
                                                    "    varying_texcoord = vec2(uv.x, uv.y);\n"
                                                    "  }\n"
                                                    "  else\n"
                                                    "    varying_texcoord = " ALLEGRO_SHADER_VAR_TEXCOORD";\n"
                                                    "  gl_Position = " ALLEGRO_SHADER_VAR_PROJVIEW_MATRIX " * " ALLEGRO_SHADER_VAR_POS ";\n"
                                                    "}\n";

} // namespace shader

int shader::buildAll() {
    shaders[shader::NONE] = NULL;
    for (int i=1; i<NUM_SHADERS; i++) {
        shaders[i] = al_create_shader(ALLEGRO_SHADER_GLSL);
        al_attach_shader_source(shaders[i], ALLEGRO_PIXEL_SHADER, sources[i]);
        al_attach_shader_source(shaders[i], ALLEGRO_VERTEX_SHADER, default_vertex_source);
        bool err = al_build_shader(shaders[i]);
        printf("Error loading shader[%d]: %d\n", i, err);
        printf("log: %s\n", al_get_shader_log(shaders[i]));
    }
    return 0;
}

void shader::use(shader_e e) {
    // printf("using %d\n", e);
    if (!al_use_shader(shaders[e])) {
        fprintf(stderr, "Failed to activate shader! Falling back to default.\n");
        // Read the log to see why it failed:
        fprintf(stderr, "Shader log: %s\n", al_get_shader_log(shaders[e]));
    }
}

void shader::destroyAll() {
    for (int i=1; i<NUM_SHADERS; i++) al_destroy_shader(shaders[i]);
}