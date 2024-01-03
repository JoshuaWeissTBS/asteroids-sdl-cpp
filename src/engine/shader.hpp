#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

struct ShaderProgramSource {
    std::string vertex_source;
    std::string fragment_source;
};

class Shader {
public:
    static ShaderProgramSource parse_shader(const std::string& file);
    static unsigned int compile_shader(unsigned int type, const std::string& source);
    static unsigned int create_shader(const std::string& vertexShader, const std::string& fragmentShader);
};

#endif // SHADER_H