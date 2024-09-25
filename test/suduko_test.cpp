//===----------------------------------------------------
//                    SODUKU
// Created by chenjunhao on 2024/9/25.
// SUDUKO test/suduko_test.cpp
//
//===-----------------------------------------------------

#include <gtest/gtest.h>
#include <suduko.h>

namespace suduko {

TEST(SudukoTest, InferenceTest1) {
  std::string grid_strings[] = {
    "009000080601902007000000006000003040008705200040600000500000000300009001060000720",
    "000704090023000000400006003276000100000108000001000564900500007000000930050302000",
    "200700009300401000010030080800006007060000050100200004030020070000807002900005008",
    "020000300900075002000900500008000003010000060705060900007003000600720001002000040"
  };


  for (const auto &grid_string: grid_strings) {
    SuDuKo suduko(grid_string);
    auto ans = suduko.GetInference();
    suduko.PrintResult();
    // Test for rows
    for (int i = 0; i < MAX_GRID_SIZE; ++i) {
      auto row_grid_bitmap = 0;
      for (int j = 0; j < MAX_GRID_SIZE; ++j) {
        row_grid_bitmap |= __number_to_mask(ans[i * MAX_GRID_SIZE + j]);
      }

      EXPECT_EQ(static_cast<uint16_t>(row_grid_bitmap), FULL_MASK);
    }

    // Test for columns
    for (int i = 0; i < MAX_GRID_SIZE; ++i) {
      auto column_grid_bitmap = 0;
      for (int j = 0; j < MAX_GRID_SIZE; ++j) {
        column_grid_bitmap |= __number_to_mask(ans[i + j * MAX_GRID_SIZE]);
      }

      EXPECT_EQ(static_cast<uint16_t>(column_grid_bitmap), FULL_MASK);
    }

    // Test for box
    auto box_bitmap = std::make_shared<uint16_t[]>(MAX_GRID_SIZE * MAX_GRID_SIZE / MAX_BOX_SIZE / MAX_BOX_SIZE);
    memset(box_bitmap.get(), 0, MAX_GRID_SIZE * MAX_GRID_SIZE / MAX_BOX_SIZE / MAX_BOX_SIZE);
    for (int i = 0; i < MAX_GRID_SIZE; ++i) {
      for (int j = 0; j < MAX_GRID_SIZE; ++j) {
        box_bitmap[i / MAX_BOX_SIZE * MAX_GRID_SIZE / MAX_BOX_SIZE  + j / MAX_BOX_SIZE]
            |= __number_to_mask(ans[i + j * MAX_GRID_SIZE]);
      }
    }


    for (int i = 0; i < MAX_GRID_SIZE * MAX_GRID_SIZE / MAX_BOX_SIZE / MAX_BOX_SIZE; ++i) {
      EXPECT_EQ(static_cast<uint16_t>(box_bitmap[i]), FULL_MASK);
    }
  }
}

} // namespace suduko