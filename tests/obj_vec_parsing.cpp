#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "loaders/obj_loader.hpp"
#include "physics/vector.hpp"
#include "renderer/vertex.hpp"

TEST(VecParsing, Simple1) {
  ObjLoaderConfig config("");
  ObjLoader loader(config);

  std::string input = "1.0000 0.0000 -3.0000";
  Vector3 expected{1.0, 0.0, -3.0};

  ASSERT_EQ(loader.parse_vector3(input, 0, input.length() - 1), expected);
}

TEST(VecParsing, Simple2) {
  ObjLoaderConfig config("");
  ObjLoader loader(config);

  std::string input = "1.0000 2.50000";
  Vector2 expected{1.0, 2.5};

  ASSERT_EQ(loader.parse_vector2(input, 0, input.length() - 1), expected);
}

TEST(VecParsing, Simple3) {
  ObjLoaderConfig config("");
  ObjLoader loader(config);

  std::string input = "vt 0.888 3.333 -0.5";
  Vector3 expected{0.888, 3.333, -0.5};

  Vector3 result = loader.parse_vector3(input, 3, input.length() - 1);

  ASSERT_EQ(result, expected);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}