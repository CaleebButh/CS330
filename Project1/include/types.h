#pragma once
#include <glm/glm.hpp>
#include <vector>

constexpr uint8_t MAX_POINT_LIGHTS = 4;
constexpr uint8_t MAX_DIR_LIGHTS = 4;

struct Vertex {
    glm::vec3 Position{ 0.f, 0.f, 0.f };
    glm::vec3 Color{ 1.f, 1.f, 1.f };
    glm::vec3 Normal{ 0.f, 0.f, 0.f };
    glm::vec2 Uv{ 1.f, 1.f };
};

struct DirectionalLight {
    glm::vec3 Position{ 0.f, 0.f, 0.f };

    glm::vec3 AmbientColor{ 0.f };
    glm::vec3 DiffuseColor{ 0.f };
    glm::vec3 SpecularColor{ 0.f };

    float AmbientIntensity{ 0.f };
    float DiffuseIntensity{ 0.f };
    float SpecularIntensity{ 0.f };
};

struct PointLightStruct {
    glm::vec3 Position;

    glm::vec3 AmbientColor{};
    glm::vec3 DiffuseColor{};
    glm::vec3 SpecularColor{};

    float Constant{ 1.f };
    float Linear{ 0.f };
    float Quadratic{ 0.f };
};

struct SceneParameters {
    glm::mat4 ProjectionMatrix{ 1.f };
    glm::mat4 ViewMatrix{ 1.f };

    glm::vec3 CameraPosition{};

    std::vector<DirectionalLight> DirLights{};
    std::vector<PointLightStruct> PointLights{};
};