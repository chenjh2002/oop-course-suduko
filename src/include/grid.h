//===----------------------------------------------------
//                    SODUKU
// Created by chenjunhao on 2024/9/23.
// SUDUKO src/include/grid.h
//
//===-----------------------------------------------------

#pragma once

#include <config.h>
#include <exception.h>

#include <memory>
#include <string>

namespace suduko {
/**
 * @class Grid is a class that contain and valid data, which is the father class of suduko
 */
class Grid {
 public:
  Grid() = delete;
  explicit Grid(const std::string& grid_string, int32_t grid_size, int32_t box_size);
  /** Move constructor */
  Grid(Grid &&other) noexcept ;
  ~Grid() = default;

  /** Move assignment operator. */
  Grid &operator=(Grid &&other) noexcept ;


 protected:
  std::shared_ptr<grid_element_t []> grid_;
  int32_t grid_size_;
  int32_t box_size_;
};
} // namespace suduko
