//===----------------------------------------------------
//                    SODUKU
// Created by chenjunhao on 2024/9/23.
// SUDUKO src/main.cpp
//
//===-----------------------------------------------------

#include <suduko.h>

auto main(int argc, char **argv) -> int {
  std::string grid_string =
      "000704090023000000400006003276000100000108000001000564900500007000000930050302000";
  suduko::SuDuKo suduko(grid_string);
  auto ans = suduko.GetInference();
  suduko.PrintResult();
  return 0;
}