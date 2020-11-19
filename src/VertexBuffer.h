#pragma once
#include "GLCheckError.h"

class VertexBuffer
{
private:
	unsigned int m_BufferID;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

};