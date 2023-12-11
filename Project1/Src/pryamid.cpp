#include <pyramid.h>
#include <types.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "../shapes.h"

Pyramid::Pyramid() {
    createShaders();
    createModel();
}

void Pyramid::Init() {

}

void Pyramid::Update(float deltaTime) {
    //    Transform = glm::rotate(Transform, glm::radians(45.f) * deltaTime, glm::vec3(0, 1, 0));
}

void Pyramid::createShaders() {
    _basicLitShader = std::make_shared<Shader>(Path("basic_lit.vert"), Path("basic_lit.frag"));
}

void Pyramid::createModel() {
    // Create hilt
    auto pyramidMesh = std::make_shared<Mesh>(Shapes::pyramidVertices, Shapes::pyramidIndices, glm::vec3(1.f, 1.f, 1.f));

    auto pyramidMaterial = std::make_shared<Material>(_basicLitShader);

    auto pyramidTexture = std::make_shared<Texture>("cloth.jpg");
    pyramidMaterial->AddTexture(pyramidTexture);

    _models.emplace_back(pyramidMesh, pyramidMaterial);

}
