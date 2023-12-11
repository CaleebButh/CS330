#pragma once
#include <glm/glm.hpp>
#include <types.h>
#include <model.h>

// Game objects,
class Object {
public:
    ~Object() = default;
    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw(const SceneParameters& sceneParams) {
        for (auto& model : _models) {
            auto* mesh = model.GetMesh();

            model.GetMaterial()->Bind(sceneParams, Transform * mesh->Transform);
            mesh->Draw();
        }
    };

    virtual void ProcessLighting(SceneParameters& sceneParams) {};
public:
    glm::mat4 Transform{ 1.f }; // default model matrix
    std::vector<Model> _models{};
};