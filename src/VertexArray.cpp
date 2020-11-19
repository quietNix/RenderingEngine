#include "VertexArray.h"
#include <iostream>


VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &m_VAO));
	GLCall(glBindVertexArray(m_VAO));
}

VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &m_VAO));
}

void VertexArray::AddBuffer(const VertexBufferLayout& layout)
{
	//Bind();
	//vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		bufferLayoutIndices.push_back(i);
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalised, layout.GetStride(), (const void*)offset));
		//offset += element.count*VertexBufferElement::GetSizeOfType(element.type);
		offset += element.count * sizeof(element.type);
	}
}

void VertexArray::Bind() const{
	GLCall(glBindVertexArray(m_VAO));
}

void VertexArray::Unbind() const{
	GLCall(glBindVertexArray(0));
	for (unsigned int i = 0; i < bufferLayoutIndices.size(); i++) {
		glDisableVertexAttribArray(i);
	}
	
}