// Copyright 2023 sallieam

#include "../s21_containers.h"

TEST(front, test0) {
  s21::queue<int> test;
  test.push(1);
  test.push(2);
  std::queue<int> testS;
  testS.push(1);
  testS.push(2);
  ASSERT_EQ(test.front(), testS.front());
}

TEST(back, test0) {
  s21::queue<int> test;
  test.push(1);
  test.push(2);
  std::queue<int> testS;
  testS.push(1);
  testS.push(2);
  ASSERT_EQ(test.back(), testS.back());
}

TEST(empty, test0) {
  s21::queue<int> test;
  test.push(1);
  test.pop();
  std::queue<int> testS;
  testS.push(1);
  testS.pop();
  ASSERT_EQ(test.empty(), testS.empty());
}

TEST(empty, test1) {
  s21::queue<int> test;
  std::queue<int> testS;
  ASSERT_EQ(test.empty(), testS.empty());
}

TEST(size, test1) {
  s21::queue<int> test;
  std::queue<int> testS;
  ASSERT_EQ(test.size(), testS.size());
}

TEST(swap, test1) {
  s21::queue<int> test;
  test.push(1);
  s21::queue<int> other;
  other.push(3);
  test.swap(other);
  std::queue<int> testS;
  testS.push(1);
  std::queue<int> otherS;
  otherS.push(3);
  testS.swap(otherS);
  ASSERT_EQ(test.back(), testS.back());
}

TEST(insert_many, test0) {
  s21::queue<int> test;
  test.insert_many_back(1, 2, 3, 4, 5);
  ASSERT_EQ(test.size(), 5);
  ASSERT_EQ(test.back(), 5);
  test.insert_many_back(6, 7, 8, 9, 0);
  ASSERT_EQ(test.size(), 10);
  ASSERT_EQ(test.back(), 0);
  test.insert_many_back(22, 23, 24, 25, 26);
  ASSERT_EQ(test.size(), 15);
}

TEST(ctors, test0) {
  s21::queue<int> st{1, 2, 3, 4, 5};
  s21::queue<int> cpy(st);
  EXPECT_EQ(st.front(), cpy.front());
  EXPECT_EQ(st.back(), cpy.back());
  s21::queue<int> mv(std::move(st));
  EXPECT_EQ(mv.front(), cpy.front());
  EXPECT_EQ(mv.back(), cpy.back());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
