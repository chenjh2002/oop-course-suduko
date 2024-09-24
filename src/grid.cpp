//===----------------------------------------------------
//                    SODUKU
// Created by chenjunhao on 2024/9/23.
// SUDUKO src/grid.cpp
//
//===-----------------------------------------------------

#include <grid.h>

#include <cctype>

namespace suduko {

Grid::Grid(const std::string& grid_string, int32_t grid_size, int32_t box_size)
  : grid_size_(grid_size), box_size_(box_size) {
  if (grid_size_ > MAX_GRID_SIZE || box_size_ > MAX_BOX_SIZE || grid_size_ < 1 || box_size_ < 1) {
    throw Exception(ExceptionType::INVALID_ARGUMENT, "Invalid grid size or box size");
  }

  grid_ = std::make_shared<grid_element_t []>(grid_size_ * grid_size_);

  // Judge if the input string is valid
  auto row_index{0};
  auto col_index{0};
  for (const char& c : grid_string) {
    if (row_index >= grid_size_) {
      throw Exception(ExceptionType::INVALID_ARGUMENT, "Invalid grid string, the size is too big.");
    }
    if (!isdigit(c)) {
      throw Exception(ExceptionType::INVALID_ARGUMENT, "Invalid grid string");
    }

    grid_[row_index * grid_size_ + col_index] = static_cast<uint8_t>(c - '0');
    row_index = row_index + (col_index == grid_size_ - 1 ? 1 : 0);
    col_index = ++col_index % grid_size_;
  }

  if (row_index < grid_size_ || col_index != 0) {
    throw Exception(ExceptionType::INVALID_ARGUMENT, "Invalid grid string, the size is too small.");
  }

}

Grid::Grid(suduko::Grid &&other) noexcept {
  if (this != &other) {
    grid_ = std::move(other.grid_);
    grid_size_ = other.grid_size_;
    box_size_ = other.box_size_;
    other.grid_size_ = 0;
    other.box_size_ = 0;
  }
}

Grid &Grid::operator=(Grid &&other) noexcept {
  if (this != &other) {
    grid_ = std::move(other.grid_);
    grid_size_ = other.grid_size_;
    box_size_ = other.box_size_;
    other.grid_size_ = 0;
    other.box_size_ = 0;
  }

  return *this;
}

} // namespace suduko