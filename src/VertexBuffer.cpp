#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(const void* data, unsigned int size) 
{
    //generating buffer and getting id("buffer") back so we can bind it afterwards
    glGenBuffers(1, &m_BufferID);
    //binding that buffer id
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1, &m_BufferID));
}

void VertexBuffer::Bind() const{
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
}

void VertexBuffer::Unbind() const{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}