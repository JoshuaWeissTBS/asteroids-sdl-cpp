#pragma once

#include <glad/glad.h>
#include <vector>
#include "renderer.hpp"

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int get_size_of_type(unsigned int type) {
        switch (type) {
            case GL_FLOAT:          return sizeof(GLfloat);
            case GL_UNSIGNED_INT:   return sizeof(GLuint);
            case GL_UNSIGNED_BYTE:  return sizeof(GLubyte);
        }
        // ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout()
        : m_Stride(0) {}
    ~VertexBufferLayout();

    void push(unsigned int type, unsigned int count) {
        m_Elements.push_back({ type, count, GL_FALSE });
        m_Stride += count * VertexBufferElement::get_size_of_type(type);
    }

    inline const std::vector<VertexBufferElement>& get_elements() const& { return m_Elements; }
    inline unsigned int get_stride() const { return m_Stride; }

};