#include "shader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glad/glad.h>

using namespace std;

ShaderProgramSource Shader::parse_shader(const string& file) {
    ifstream stream(file);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    string line;
    stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != string::npos) {
            if (line.find("vertex") != string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != string::npos) {
                type = ShaderType::FRAGMENT;
            }
        } else {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
};

unsigned int Shader::compile_shader(unsigned int type, const string& source)
{
    unsigned int id = glCreateShader(type);
    // OpenGL expects a pointer to an array of pointers to chars
    const char* src = source.c_str();
    // Pass in the shader source code
    glShaderSource(id, 1, &src, nullptr);
    // Compile the shader
    glCompileShader(id);

    // Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        // Get length of error message
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        // Allocate memory on the stack for the error message
        char* message = (char*)alloca(length * sizeof(char));
        // Copy error message to message variable
        glGetShaderInfoLog(id, length, &length, message);
        // Print error message
        cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << endl;
        cout << message << endl;
        // Delete shader
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::create_shader(const string& vertexShader, const string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    // Delete shaders after linking
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
