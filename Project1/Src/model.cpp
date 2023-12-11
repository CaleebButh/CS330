#include <model.h>

Model::Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) : _material{ material }, _mesh{ mesh } {}

