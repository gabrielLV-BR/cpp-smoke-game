#pragma once

#include <cstdint>
#include <unordered_map>
#include <vector>

#include "renderer/material.hpp"

class MaterialServer {
  static MaterialServer* _instance;

  std::unordered_map<Material, size_t> material_index;
  std::vector<Material> materials;

 public:
  MaterialServer();
  ~MaterialServer();

  uint32_t store_material(const Material& material);
  Material& get_material(uint32_t index);
  uint32_t get_index(const Material& mat);

  static MaterialServer* MaterialServer::get_global_instance() {
    if (_instance == nullptr) {
      *_instance = MaterialServer();
    }
    return _instance;
  }
};