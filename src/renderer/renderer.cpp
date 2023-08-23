#include "renderer.hpp"

#include "mesh.hpp"
#include "model.hpp"
#include "material.hpp"
#include "math/transform.hpp"

#include "glad/glad.h"

void RenderSystem(const Model& model, const Material& material) {
    // for now, we'll only render one mesh
    material.Bind();

    const Mesh& mesh = model.meshes[0];

    glBindVertexArray(mesh.vao);
    glDrawElements(GL_TRIANGLES, mesh.index_count(), GL_UNSIGNED_INT, NULL);

    material.Unbind();
}

Renderer::Renderer(flecs::world& world) {
    world.system<const Model, const Material>().each(RenderSystem);
}