#include <dir_light.h>
#include <shapes.h>
#include <glm/ext/matrix_transform.hpp>
#include "../shapes.h"

DirLight::DirLight() {
    createShader();
    createMesh();
}

void DirLight::Init() {
}

void DirLight::Update(float deltaTime) {
    //    auto cos = std::cos(totalTime);
    //    auto sin = std::sin(totalTime);
    //
    //    Transform = glm::translate(Transform, glm::vec3(cos / 10, 0, sin / 10));
    //
    //    totalTime += deltaTime;
}

void DirLight::ProcessLighting(SceneParameters& sceneParams) {
    if (sceneParams.DirLights.size() < MAX_DIR_LIGHTS) {
        DirectionalLight directionalLight{
            .Position = glm::vec3(Transform[3]),
            .AmbientColor = AmbientColor,
            .DiffuseColor = DiffuseColor,
            .SpecularColor = SpecularColor,
            .AmbientIntensity = AmbientIntensity,
            .DiffuseIntensity = DiffuseIntensity,
            .SpecularIntensity = SpecularIntensity,
        };

        sceneParams.DirLights.emplace_back(directionalLight);
    }
}

void DirLight::SetRenderColor(const glm::vec3& renderColor) {
    _renderColor = renderColor;

    _models.clear();
    createMesh();
}

void DirLight::createShader() {
    _basicUnlitShader = std::make_shared<Shader>(Path("basic_unlit_color.vert"), Path("basic_unlit_color.frag"));
}

void DirLight::createMesh() {
    auto cube = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements, _renderColor);

    auto lightMaterial = std::make_shared<Material>(_basicUnlitShader);
    auto& cubeModel = _models.emplace_back(cube, lightMaterial);
    cubeModel.GetMesh()->Transform = glm::scale(cubeModel.GetMesh()->Transform, glm::vec3(0.5f, 0.5f, 0.5f));
}

void DirLight::Draw(const SceneParameters& sceneParams) {
    //    GameObject::Draw(sceneParams);
}