//===----------------------------------------------------
//                    SODUKU
// Created by chenjunhao on 2024/9/23.
// SUDUKO src/suduko.cpp
//
//===-----------------------------------------------------

#include <suduko.h>

namespace suduko {
SuDuKo::SuDuKo(const std::string &grid_string, int32_t grid_size, int32_t box_size)
  : Grid(grid_string, grid_size, box_size) {
  row_grid_bitmap_ = std::make_shared<uint16_t []>(grid_size_);
  col_grid_bitmap_ = std::make_shared<uint16_t []>(grid_size_);
  memset(row_grid_bitmap_.get(), 0, grid_size_);
  memset(col_grid_bitmap_.get(), 0, grid_size_);

  // Initialize the mask
  row_mask_ = std::make_shared<uint16_t []>(grid_size_);
  col_mask_ = std::make_shared<uint16_t []>(grid_size_);
  memset(row_mask_.get(), 0, grid_size_);
  memset(col_mask_.get(), 0, grid_size_);

  ans_ = std::make_shared<grid_element_t []>(grid_size_ * grid_size_);

  for (int i = 0; i < grid_size_; ++i) {
    for (int j = 0; j < grid_size_; ++j) {
      if (!grid_[i * grid_size_ + j]) {
        empty_hole_.emplace_back(i, j);
      } else {
        row_grid_bitmap_[i] |= __number_to_mask(grid_[i * grid_size_ + j]);
        col_grid_bitmap_[j] |= __number_to_mask(grid_[i * grid_size_ + j]);
      }
    }
  }
}

auto SuDuKo::GetInference() -> std::shared_ptr<grid_element_t[]> {
  size_t dfs_index = 0;
  auto cache_mask = std::vector<uint16_t>();
  auto path_record = std::vector<uint16_t >(empty_hole_.size(), 0);
  while (dfs_index < empty_hole_.size()) {
    // Get avaliable point
    auto avaliable{-1};
    uint16_t current_mask = row_mask_[empty_hole_[dfs_index].first] | col_mask_[empty_hole_[dfs_index].second]
        | row_grid_bitmap_[empty_hole_[dfs_index].first] | col_grid_bitmap_[empty_hole_[dfs_index].second];
    if (current_mask == FULL_MASK) {
      dfs_index--;
      row_mask_[empty_hole_[dfs_index].first] &= ~__number_to_mask(cache_mask.back());
      col_mask_[empty_hole_[dfs_index].second] &= ~__number_to_mask(cache_mask.back());
      cache_mask.pop_back();
      continue;
    }

    for (int candidate = 1; candidate < 10; candidate++) {
      if ((__number_to_mask(candidate) & (current_mask | path_record[dfs_index])) == 0) {
        avaliable = candidate;
        break;
      }
    }

    if (avaliable == -1) {
      if (dfs_index == 0) {
        throw Exception(ExceptionType::INVALID_ARGUMENT, "Invalid suduko problem");
      }

      path_record[dfs_index] = 0;
      dfs_index--;
      row_mask_[empty_hole_[dfs_index].first] &= ~__number_to_mask(cache_mask.back());
      col_mask_[empty_hole_[dfs_index].second] &= ~__number_to_mask(cache_mask.back());
      cache_mask.pop_back();
      continue;
    }

    row_mask_[empty_hole_[dfs_index].first] |= __number_to_mask(avaliable);
    col_mask_[empty_hole_[dfs_index].second] |= __number_to_mask(avaliable);
    path_record[dfs_index] |= __number_to_mask(avaliable);
    cache_mask.emplace_back(avaliable);
    dfs_index++;
  }

  // Insert the res into the ans
  auto mask_index{0};
  for (int i = 0; i < grid_size_; ++i) {
    for (int j = 0; j < grid_size_; ++j) {
      ans_[i * grid_size_ + j] = grid_[i * grid_size_ + j];
      if (!grid_[i * grid_size_ + j]) {
        ans_[i * grid_size_ + j] = cache_mask[mask_index++];
      }
    }
  }

  return ans_;
}

void SuDuKo::PrintResult() {
  for (int i = 0; i < grid_size_; ++i) {
    for (int j = 0; j < grid_size_; ++j) {
      std::cout << static_cast<int>(ans_[i * grid_size_ + j]) << " ";
    }
    std::cout << std::endl;
  }
}

} // namespace suduko