#include <room.h>
#include <types.h>
#include <glm/gtc/matrix_transform.hpp>
#include <shapes.h>
#include "../shapes.h"

Room::Room() {
    createShaders();
    createModel();
}

void Room::Init() {

}

void Room::Update(float deltaTime) {
    //    Transform = glm::rotate(Transform, glm::radians(45.f) * deltaTime, glm::vec3(0, 1, 0));
}

void Room::createShaders() {
    _basicLitShader = std::make_shared<Shader>(Path("basic_lit.vert"), Path("basic_lit.frag"));
}

void Room::createModel() {
    const float wallScale = 25.f;
    // Create hilt
    auto leftWall = std::make_shared<Mesh>(Shapes::planeVertices, Shapes::planeElements, glm::vec3(1.f, 1.f, 1.f));
    auto rightWall = std::make_shared<Mesh>(Shapes::planeVertices, Shapes::planeElements, glm::vec3(1.f, 1.f, 1.f));
    auto floor = std::make_shared<Mesh>(Shapes::planeVertices, Shapes::planeElements, glm::vec2{ 2.f, 2.f });
    auto ceiling = std::make_shared<Mesh>(Shapes::planeVertices, Shapes::planeElements, glm::vec3(1.f, 1.f, 1.f));

    auto wallTexture = std::make_shared<Texture>("wall.jpg",
        Texture::SamplerSettings{
                .S = Texture::SamplerTileMode::Repeat,
                .T = Texture::SamplerTileMode::Repeat
        });
    auto floorTexture = std::make_shared<Texture>("floor.jpg",
        Texture::SamplerSettings{
              .S = Texture::SamplerTileMode::MirroredRepeat,
              .T = Texture::SamplerTileMode::MirroredRepeat
        });

    auto leftWallMaterial = std::make_shared<Material>(_basicLitShader);
    leftWallMaterial->AddTexture(wallTexture);
    leftWallMaterial->Shininess = 0.1f;
    auto rightWallMaterial = std::make_shared<Material>(_basicLitShader);
    rightWallMaterial->AddTexture(wallTexture);
    rightWallMaterial->Shininess = 0.1f;

    auto floorMaterial = std::make_shared<Material>(_basicLitShader);
    floorMaterial->AddTexture(floorTexture);
    floorMaterial->Shininess = 0.1f;

    auto ceilingMaterial = std::make_shared<Material>(_basicLitShader);
    ceilingMaterial->AddTexture(wallTexture);
    ceilingMaterial->Shininess = 0.1f;


    _models.emplace_back(leftWall, leftWallMaterial);
    _models.emplace_back(rightWall, rightWallMaterial);
    _models.emplace_back(floor, floorMaterial);
    _models.emplace_back(ceiling, ceilingMaterial);

    leftWall->Transform = glm::translate(leftWall->Transform, glm::vec3(-wallScale / 2, wallScale / 2, 0.f));
    leftWall->Transform = glm::rotate(leftWall->Transform, glm::radians(90.f), glm::vec3(0, 1, 0));
    leftWall->Transform = glm::scale(leftWall->Transform, glm::vec3(wallScale, wallScale, wallScale));

    rightWall->Transform = glm::translate(rightWall->Transform, glm::vec3(0.f, wallScale / 2, -wallScale / 2));
    rightWall->Transform = glm::rotate(rightWall->Transform, glm::radians(0.f), glm::vec3(0, 1, 0));
    rightWall->Transform = glm::scale(rightWall->Transform, glm::vec3(wallScale, wallScale, wallScale));

    floor->Transform = glm::translate(floor->Transform, glm::vec3(0.f, 0.f, 0.f));
    floor->Transform = glm::rotate(floor->Transform, glm::radians(-90.f), glm::vec3(1, 0, 0));
    floor->Transform = glm::scale(floor->Transform, glm::vec3(wallScale, wallScale, wallScale));

    ceiling->Transform = glm::translate(ceiling->Transform, glm::vec3(0.f, wallScale, 0.f));
    ceiling->Transform = glm::rotate(ceiling->Transform, glm::radians(90.f), glm::vec3(1, 0, 0));
    ceiling->Transform = glm::scale(ceiling->Transform, glm::vec3(wallScale, wallScale, wallScale));

}

