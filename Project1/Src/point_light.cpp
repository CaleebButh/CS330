#include <point_light.h>
#include <glm/ext/matrix_transform.hpp>
#include "../shapes.h"

PointLight::PointLight() {
    createShader();
    createMesh();
}

void PointLight::Init() {
}

void PointLight::Update(float deltaTime) {
    //    auto cos = std::cos(totalTime);
    //    auto sin = std::sin(totalTime);
    //
    //    Transform = glm::translate(Transform, glm::vec3(cos / 10, 0, sin / 10));
    //
    //    totalTime += deltaTime;
}

void PointLight::ProcessLighting(SceneParameters& sceneParams) {
    if (sceneParams.PointLights.size() < MAX_POINT_LIGHTS) {
        PointLightStruct pointLight{
            .Position = glm::vec3(Transform[3]),
            .AmbientColor = AmbientColor,
            .DiffuseColor = DiffuseColor,
            .SpecularColor = SpecularColor,
            .Constant = Constant,
            .Linear = Linear,
            .Quadratic = Quadratic
        };

        sceneParams.PointLights.emplace_back(pointLight);
    }
}

void PointLight::createShader() {
    _basicUnlitShader = std::make_shared<Shader>(Path("basic_unlit_color.vert"), Path("basic_unlit_color.frag"));
}

void PointLight::createMesh() {
    auto cube = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements, glm::vec3(1.f, 1.f, 1.f));

    auto lightMaterial = std::make_shared<Material>(_basicUnlitShader);
    auto& cubeModel = _models.emplace_back(cube, lightMaterial);
    cubeModel.GetMesh()->Transform = glm::scale(cubeModel.GetMesh()->Transform, glm::vec3(0.5f, 0.5f, 0.5f));
}
