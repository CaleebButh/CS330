#include <material.h>

#include <utility>

Material::Material(std::shared_ptr<Shader> shader)
    : _shader{ std::move(shader) } {}

void Material::AddTexture(const std::shared_ptr<Texture>& texture) {
    _textures.emplace_back(texture);
}

void Material::Bind(const SceneParameters& sceneParams, const glm::mat4& model) {
    _shader->Bind();
    _shader->SetMat4("projection", sceneParams.ProjectionMatrix);
    _shader->SetMat4("view", sceneParams.ViewMatrix);

    // Set Camera Position
    _shader->SetVec3("eyePos", sceneParams.CameraPosition);

    // handle lights
    for (auto i = 0; i < MAX_POINT_LIGHTS; i++) {
        std::string baseUniformName = "pointLights[";
        baseUniformName += std::to_string(i) + "]";

        PointLightStruct pointLight = i < sceneParams.PointLights.size() ? sceneParams.PointLights[i] : PointLightStruct{};

        _shader->SetVec3(baseUniformName + ".Position", pointLight.Position);
        _shader->SetVec3(baseUniformName + ".Diffuse", pointLight.DiffuseColor);
        _shader->SetVec3(baseUniformName + ".Ambient", pointLight.AmbientColor);
        _shader->SetVec3(baseUniformName + ".Specular", pointLight.SpecularColor);

        _shader->SetFloat(baseUniformName + ".Constant", pointLight.Constant);
        _shader->SetFloat(baseUniformName + ".Linear", pointLight.Linear);
        _shader->SetFloat(baseUniformName + ".Quadratic", pointLight.Quadratic);
    }

    for (auto i = 0; i < MAX_DIR_LIGHTS; i++) {
        std::string baseUniformName = "dirLights[";
        baseUniformName += std::to_string(i) + "]";

        DirectionalLight dirLight = i < sceneParams.DirLights.size() ? sceneParams.DirLights[i] : DirectionalLight{};

        _shader->SetVec3(baseUniformName + ".Position", dirLight.Position);
        _shader->SetVec3(baseUniformName + ".Diffuse", dirLight.DiffuseColor);
        _shader->SetVec3(baseUniformName + ".Ambient", dirLight.AmbientColor);
        _shader->SetVec3(baseUniformName + ".Specular", dirLight.SpecularColor);

        _shader->SetFloat(baseUniformName + ".AmbientIntensity", dirLight.AmbientIntensity);
        _shader->SetFloat(baseUniformName + ".DiffuseIntensity", dirLight.DiffuseIntensity);
        _shader->SetFloat(baseUniformName + ".SpecularIntensity", dirLight.SpecularIntensity);
    }

    _shader->SetFloat("materialProperties.Roughness", Roughness);
    _shader->SetFloat("materialProperties.Shininess", Shininess);
    _shader->SetMat4("model", model);

    for (auto i = 0; i < _textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        _textures[i]->Bind();
    }
}
