#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <object.h>
#include <memory>
#include <camera.h>

class Application {
public:
    Application(std::string WindowTitle, int width, int height);
    void Run();

private:
    bool openWindow();
    void setupInputs();

    void setupScene();
    void update(float deltaTime);
    void draw();

    void handleInput(float deltaTime);
    void mousePositionCallback(double xpos, double ypos);
private:
    std::string _applicationName{};
    GLFWwindow* _window{ nullptr };

    float _moveSpeed{ 15.f };
    Camera _camera;
    std::vector<std::unique_ptr<Object>> _objects{};

    bool _running{ false };

    bool _firstMouse{ false };
    glm::vec2 _lastMousePosition{};
    glm::vec2 _cameraLookSpeed{};

    float _lastFrameTime{ -1.f };

    // lighting variables
    float _ambientStrength{ 0.1f };
    glm::vec3 _ambientLightColor{ 1.f, 1.f, 1.f };
};