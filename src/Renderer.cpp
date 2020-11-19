#include <iostream>
#include "Renderer.h"


Renderer::Renderer() {

}
Renderer::~Renderer() {

}

void Renderer::Bind(const VertexArray& va, const IndexBuffer& ib, const Shader& sd) const {
    va.Bind();
    ib.Bind();
    sd.Bind();
}


void Renderer::Draw(const IndexBuffer& ib) const {
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);      //ActualDrawCall
}

