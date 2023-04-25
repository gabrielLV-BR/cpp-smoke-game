#include "./material_server.hpp"

MaterialServer::MaterialServer() {}

MaterialServer::~MaterialServer() {}

uint32_t MaterialServer::store_material(const Material& material) {
  if (material_index.count(material) > 0)
    return;

  uint32_t index = materials.size() - 1;

  material_index[material] = index;
  materials.emplace_back(material);

  return index;
}

Material& MaterialServer::get_material(uint32_t index) {
  return materials.at(index);
}

uint32_t MaterialServer::get_index(const Material& mat) {
  return material_index.at(mat);
}