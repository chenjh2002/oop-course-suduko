//===----------------------------------------------------
//                    SODUKU
// Created by chenjunhao on 2024/9/23.
// SUDUKO src/suduko.cpp
//
//===-----------------------------------------------------

#include <suduko.h>

#include <fmt/core.h>
#include <fmt/color.h>

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

SuDuKo::SuDuKo(suduko::SuDuKo &&other) noexcept {
  if (this != &other) {
    // Father class component
    this->grid_ = std::move(other.grid_);
    this->grid_size_ = other.grid_size_;
    this->box_size_ = other.box_size_;
    //  Flush the inference component
    this->row_grid_bitmap_ = std::move(other.row_grid_bitmap_);
    this->col_grid_bitmap_ = std::move(other.col_grid_bitmap_);
    this->row_mask_ = std::move(other.row_mask_);
    this->col_mask_ = std::move(other.col_mask_);
    this->empty_hole_ = std::move(other.empty_hole_);
    this->ans_ = std::move(other.ans_);
  }
}

SuDuKo &SuDuKo::operator=(suduko::SuDuKo &&other) noexcept {
  if (this != &other) {
    // Father class component
    this->grid_ = std::move(other.grid_);
    this->grid_size_ = other.grid_size_;
    this->box_size_ = other.box_size_;
    //  Flush the inference component
    this->row_grid_bitmap_ = std::move(other.row_grid_bitmap_);
    this->col_grid_bitmap_ = std::move(other.col_grid_bitmap_);
    this->row_mask_ = std::move(other.row_mask_);
    this->col_mask_ = std::move(other.col_mask_);
    this->empty_hole_ = std::move(other.empty_hole_);
    this->ans_ = std::move(other.ans_);
  }

  return *this;
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
  std::cout << "====================Result====================\n";
  for (int i = 0; i < grid_size_; ++i) {
    for (int j = 0; j < grid_size_; ++j) {
      if (!grid_[i * grid_size_ +j]) {
        std::cout << fmt::format(fg(fmt::color::orange_red) | fmt::emphasis::underline, std::to_string(ans_[i * grid_size_ + j])) << " ";
      } else {
        std::cout << static_cast<int>(ans_[i * grid_size_ + j]) << " ";
      }
    }
    std::cout << std::endl;
  }
  std::cout << "==============================================\n";
}

} // namespace suduko