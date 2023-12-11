#pragma once
#include<object.h>

class Desk : public Object {
public:
	Desk();
	void Init() override;

	void Update(float deltaTime) override;

private:
	void createShaders();
	void createMesh();

private:
	std::shared_ptr<Shader> _basicLitShader{ nullptr };
	void createTop();
	void createLegs();
};