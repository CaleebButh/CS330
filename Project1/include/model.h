#pragma once


#include <mesh.h>
#include <material.h>

// The Model class is a wrapper around a mesh and a material, so that many objects can be set up
// each having distinct shaders if necessary.
class Model {
public:
    Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);
    Material* GetMaterial() { return _material.get(); }
    Mesh* GetMesh() { return _mesh.get(); }

private:
    std::shared_ptr<Material> _material;
    std::shared_ptr<Mesh> _mesh;
};
