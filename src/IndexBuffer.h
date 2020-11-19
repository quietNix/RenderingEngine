#pragma once
#include "GLCheckError.h"

class IndexBuffer
{
private:
	unsigned int m_IBO;
	unsigned int m_Count;

public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }
};