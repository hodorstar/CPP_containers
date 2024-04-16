// Copyright 2023 tcinthia

#include "../s21_containers.h"

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);

  s21::multi_avl_tree<int, const char *> A(100, "test");
  // s21::multi_avl_tree<int, int> B;
  A.insert(50, "test");
  A.insert(150, "test");

  A.insert(25, "test");
  A.insert(175, "test");
  A.insert(75, "test");
  A.insert(125, "test");

  // A.insert(12, "test");
  // A.insert(187, "test");
  // A.insert(63, "test");
  // A.insert(137, "test");
  // A.insert(37, "test");
  // A.insert(163, "test");
  // A.insert(87, "test");
  // A.insert(113, "test");

  // A.insert(6, "test");
  // A.insert(188, "test");
  // A.insert(40, "test");
  // A.insert(162, "test");
  // A.insert(64, "test");
  // A.insert(138, "test");
  // A.insert(86, "test");
  // A.insert(112, "test");
  A.print();

  A.insert(100, "test");
  A.insert(100, "test");
  A.insert(150, "test");
  A.insert(150, "test");
  A.insert(75, "test");
  A.insert(75, "test");
  A.print();

  A.remove(150);
  A.remove(150);
  A.print();

  A.remove(50);
  A.remove(500);
  A.remove(75);
  A.remove(75);
  A.print();

  A.remove(100);
  A.remove(100);
  A.print();

  std::set<char> B;
  s21::avl_tree<int, int> AA;
  AA.count();
  // s21::set C;
  // B.insert(6);
  // auto C = B.begin();

  // s21::tree::iterator it = A.find(75);

  // return 0;
  return RUN_ALL_TESTS();
}
