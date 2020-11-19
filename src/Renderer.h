#pragma once
#include "GLCheckError.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
private:

public:
	Renderer();
	~Renderer();
	void Bind(const VertexArray& va, const IndexBuffer& ib, const Shader& sd) const;
	void Draw(const IndexBuffer& ib) const;
};