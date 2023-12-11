#include <application.h>
#include <iostream>
#include <shapes.h>
#include <pyramid.h>
#include <point_light.h>
#include <dir_light.h>
#include <desk.h>

#include <utility>
#include <glm/gtc/matrix_transform.hpp>
#include <room.h>

Application::Application(std::string WindowTitle, int width, int height)
    : _applicationName{ std::move(WindowTitle) },
    _camera{ width, height, {12.0f, 15.f, 20.f}, true },
    _cameraLookSpeed{ 0.15f, 0.15f }
{}

void Application::Run() {
    // Open the window
    if (!openWindow()) {
        return;
    }

    setupInputs();

    _running = true;

    // Set up the scene
    setupScene();

    // Run application
    while (_running) {
        auto currentTime = static_cast<float>(glfwGetTime());

        // on initial start up, there will be no last frame time.
        if (_lastFrameTime == -1.f) {
            _lastFrameTime = currentTime;
        }

        // calculate time between frames
        auto deltaTime = currentTime - _lastFrameTime;
        _lastFrameTime = currentTime;

        // if window was requested to be closed, shutdown the application
        if (glfwWindowShouldClose(_window)) {
            _running = false;
            continue;
        }

        // Update game objects
        update(deltaTime);

        // Draw game objects
        draw();
    }

    glfwTerminate();
}

bool Application::openWindow() {
    // Initialize OpenGL with version 4.2, using the CORE profile
    // I use OpenGL 4.2 to use a newer texture data upload function
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    _window = glfwCreateWindow(1000, 600, "Caleb Buth", nullptr, nullptr);

    if (!_window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
    }

    // This sets the glfw opengl context to current
    glfwMakeContextCurrent(_window);

    // Allows glfw callbacks to access the application class
    glfwSetWindowUserPointer(_window, (void*)this);

    // Callback on window resize that resizes the OpenGL viewport and stores the new framebuffer size
    glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
        // This gets called whenever the window is resized
        glViewport(0, 0, width, height);

        auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));

        // To maintain appropriate aspect ratio
        app->_camera.SetSize(width, height);
        });

    // Loads all OpenGL function pointers into memory using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return false;
    }


    glfwSwapInterval(1);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // cull back faces
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    // enable MSAA
    glEnable(GL_MULTISAMPLE);
    return true;
}

void Application::setupInputs() {
    // Input callback for key presses
    glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));

        switch (key) {
        case GLFW_KEY_ESCAPE: {
            if (action == GLFW_PRESS) {
                app->_running = false;
            }
            break;
        }
        case GLFW_KEY_P: {
            if (action == GLFW_PRESS) {
                app->_camera.SetIsPerspective(!app->_camera.IsPerspective());
            }
        }
        default: {}
        }
        });

    // input callback for mouse scroll
    glfwSetScrollCallback(_window, [](GLFWwindow* window, double xOffset, double yOffset) {
        auto* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));

        app->_moveSpeed += static_cast<float>(yOffset * 0.5f);
        app->_moveSpeed = std::clamp(app->_moveSpeed, 0.5f, 40.f);

        std::cout << "New move speed: " << app->_moveSpeed << " units per second." << std::endl;
        });

    glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xpos, double ypos) {
        auto* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));

        app->mousePositionCallback(xpos, ypos);
        });
}

void Application::setupScene() {
    _camera.RotateBy(-30.f, -10.f);


    _objects.emplace_back(std::make_unique<Room>());

    auto& desk = _objects.emplace_back(std::make_unique<Desk>());
    desk->Transform = glm::translate(desk->Transform, glm::vec3(-6.f, 12.f, 5.f));
    desk->Transform = glm::rotate(desk->Transform, glm::radians(90.f), glm::vec3(0.f, 1.f, 0.f));
    desk->Transform = glm::scale(desk->Transform, glm::vec3(2.f, 2.f, 2.f));

    // Add the main light 0.f, 24.7f, 0.f
    auto& pointLight = _objects.emplace_back(std::make_unique<PointLight>());
    pointLight->Transform = glm::translate(pointLight->Transform, glm::vec3(0.f, 24.7f, 2.f));
    auto* castLight = reinterpret_cast<PointLight*>(pointLight.get());
    castLight->Constant = 1.0f; // overriding constant to make it brighter
    castLight->Linear = 0.14f;
    castLight->Quadratic = 0.07f;
    //castLight->AmbientColor = { 0.f,1.f,0.f };


    auto& ambientDirLight = _objects.emplace_back(std::make_unique<DirLight>());
    ambientDirLight->Transform = glm::translate(ambientDirLight->Transform, glm::vec3(50.f, 50.f, -50.f));

    auto* dirLightObj = reinterpret_cast<DirLight*>(ambientDirLight.get());
    dirLightObj->AmbientIntensity = 0.15f;
    dirLightObj->AmbientColor = { 1.f, 1.f, 1.f };
}

void Application::update(float deltaTime) {
    // poll for window events
    glfwPollEvents();

    // handle all input events
    handleInput(deltaTime);

    // Call update function on all objects in scene
    for (auto& object : _objects) {
        object->Update(deltaTime);
    }
}

void Application::draw() {
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // camera
    glm::mat4 view = _camera.GetViewMatrix();
    glm::mat4 projection = _camera.GetProjectionMatrix();

    // Scene parameters that will hold data required by shaders.
    SceneParameters sceneParams{
        .ProjectionMatrix = projection,
        .ViewMatrix = view,
        .CameraPosition = _camera.GetPosition(),
    };

    // Gathers any lighting data in the scene and stores them in sceneParams
    for (auto& model : _objects) {
        model->ProcessLighting(sceneParams);
    }

    // Draw all models in the scene
    for (auto& model : _objects) {
        model->Draw(sceneParams);
    }

    // present the rendered image to the window.
    glfwSwapBuffers(_window);
}

void Application::handleInput(float deltaTime) {

    auto moveAmount = _moveSpeed * deltaTime;

    if (glfwGetKey(_window, GLFW_KEY_W)) {
        _camera.MoveCamera(Camera::MoveDirection::Forward, moveAmount);
    }
    if (glfwGetKey(_window, GLFW_KEY_S)) {
        _camera.MoveCamera(Camera::MoveDirection::Backward, moveAmount);
    }
    if (glfwGetKey(_window, GLFW_KEY_A)) {
        _camera.MoveCamera(Camera::MoveDirection::Left, moveAmount);
    }
    if (glfwGetKey(_window, GLFW_KEY_D)) {
        _camera.MoveCamera(Camera::MoveDirection::Right, moveAmount);
    }
    if (glfwGetKey(_window, GLFW_KEY_Q)) {
        _camera.MoveCamera(Camera::MoveDirection::Up, moveAmount);
    }
    if (glfwGetKey(_window, GLFW_KEY_E)) {
        _camera.MoveCamera(Camera::MoveDirection::Down, moveAmount);
    }
}

void Application::mousePositionCallback(double xpos, double ypos) {
    if (!_firstMouse) {
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        _lastMousePosition.x = static_cast<float>(xpos);
        _lastMousePosition.y = static_cast<float>(ypos);
        _firstMouse = true;
    }

    glm::vec2 moveAmount{
            xpos - _lastMousePosition.x,
            _lastMousePosition.y - ypos,
    };

    _lastMousePosition.x = static_cast<float>(xpos);
    _lastMousePosition.y = static_cast<float>(ypos);

    _camera.RotateBy(moveAmount.x * _cameraLookSpeed.x, moveAmount.y * _cameraLookSpeed.y);
}

