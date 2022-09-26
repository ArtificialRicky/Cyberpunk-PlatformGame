#pragma once

#include "cinder/gl/gl.h"

namespace platformgame {

using glm::vec2;

enum class ItemType {
  SoulGem,
  Diamond,
};

class Item {
 public:

  Item(const ItemType& type, const vec2& position, size_t size);

  vec2 GetPosition() const;

  ItemType GetItemType() const;

  size_t GetSize() const;

 private:
  ItemType type_;
  vec2 position_;
  size_t size_;

};
}
