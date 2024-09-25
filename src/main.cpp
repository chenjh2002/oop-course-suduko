//===----------------------------------------------------
//                    SODUKU
// Created by chenjunhao on 2024/9/23.
// SUDUKO src/main.cpp
//
//===-----------------------------------------------------

#include <suduko.h>

auto main(int argc, char **argv) -> int {
  std::string grid_string =
      "009000080601902007000000006000003040008705200040600000500000000300009001060000720";
  suduko::SuDuKo suduko(grid_string);
  auto ans = suduko.GetInference();
  suduko.PrintResult();
  return 0;
}