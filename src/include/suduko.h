//===----------------------------------------------------
//                    SODUKU
// Created by chenjunhao on 2024/9/23.
// SUDUKO src/include/suduko.h
//
//===-----------------------------------------------------

#pragma once

#include <grid.h>
#include <utility>
#include <vector>

namespace suduko {

class SuDuKo : public Grid {
 public:
  explicit SuDuKo(const std::string &grid_string, int32_t grid_size = MAX_GRID_SIZE, int32_t box_size  = MAX_BOX_SIZE);

  SuDuKo(SuDuKo && other) noexcept;

  SuDuKo &operator=(SuDuKo &&other) noexcept;

  ~SuDuKo() = default;

  auto GetInference() -> std::shared_ptr<grid_element_t []>;

  void PrintResult();

 private:

  /** Bitmap for the grid */
  std::shared_ptr<uint16_t []> row_grid_bitmap_;
  std::shared_ptr<uint16_t []> col_grid_bitmap_;
  std::shared_ptr<uint16_t[]> box_bitmap_;
  /** Bitmap for the mask*/
  std::shared_ptr<uint16_t []> row_mask_;
  std::shared_ptr<uint16_t []> col_mask_;
  std::shared_ptr<uint16_t []> box_mask_;
  /** Empty hole of the grid */
  std::vector<std::pair<int, int>> empty_hole_;
  /** Answer of the suduko */
  std::shared_ptr<grid_element_t []> ans_;
};

} // namespace suduko