#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <unordered_map>

struct ShaderProgramSource {
    std::string vertex_source;
    std::string fragment_source;
};

class Shader {
private:
    unsigned int m_renderer_id;
    std::string file_path;
    std::unordered_map<std::string, int> m_uniform_location_cache;

public:
    Shader(const std::string& file);
    ~Shader();

    void bind() const;
    void unbind() const;

    // Set uniforms
    void set_uniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
    static ShaderProgramSource parse_shader(const std::string& file);
    static unsigned int create_shader(const std::string& vertexShader, const std::string& fragmentShader);
    static unsigned int compile_shader(unsigned int type, const std::string& source);
    unsigned int get_uniform_location(const std::string& name);
};

#endif // SHADER_H