#pragma once
#include "GLCheckError.h"
#include "VertexBufferLayout.h"

class  VertexArray
{
private:
	unsigned int m_VAO;
	vector<unsigned int>bufferLayoutIndices;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;
};