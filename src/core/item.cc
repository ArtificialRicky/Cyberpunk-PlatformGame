#include <core/item.h>

namespace platformgame {

Item::Item(const ItemType& type, const vec2& position, size_t size) :
      type_(type), position_(position), size_(size) {}

ItemType Item::GetItemType() const {
  return type_;
}

vec2 Item::GetPosition() const {
  return position_;
}

size_t Item::GetSize() const {
  return size_;
}
}
