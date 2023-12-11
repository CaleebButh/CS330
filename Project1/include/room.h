#pragma once
#include <object.h>
#include <model.h>

class Room : public Object {
public:
    Room();
    void Init() override;
    void Update(float deltaTime) override;
private:
    void createShaders();

    void createModel();

private:
    std::shared_ptr<Shader> _basicLitShader;
};
