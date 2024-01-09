#include "vertex_array.hpp"
#include "renderer.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_renderer_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_renderer_id);
}

void VertexArray::add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    bind();
    vb.bind();
    const auto& elements = layout.get_elements();
    unsigned int offset = 0;

    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.get_stride(), (const void*)offset);
        offset += element.count * VertexBufferElement::get_size_of_type(element.type);
    }
}

void VertexArray::bind() const
{
    glBindVertexArray(m_renderer_id);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}