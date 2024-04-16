// Copyright 2023 sallieam

#include "../s21_containers.h"

TEST(top, test0) {
  s21::stack<int> test;
  test.push(1);
  test.push(2);
  std::stack<int> testS;
  testS.push(1);
  testS.push(2);
  ASSERT_EQ(test.top(), testS.top());
}

TEST(pop, test0) {
  s21::stack<int> test;
  test.push(1);
  test.push(2);
  test.push(3);
  test.pop();
  std::stack<int> testS;
  testS.push(1);
  testS.push(2);
  testS.push(3);
  testS.pop();
  ASSERT_EQ(test.top(), testS.top());
}

TEST(empty, test1) {
  s21::stack<int> test;
  std::stack<int> testS;
  ASSERT_EQ(test.empty(), testS.empty());
}

TEST(size, test1) {
  s21::stack<int> test;
  std::stack<int> testS;
  ASSERT_EQ(test.size(), testS.size());
}

TEST(swap, test1) {
  s21::stack<int> test;
  test.push(1);
  s21::stack<int> other;
  other.push(3);
  test.swap(other);
  std::stack<int> testS;
  testS.push(1);
  std::stack<int> otherS;
  otherS.push(3);
  testS.swap(otherS);
  ASSERT_EQ(test.top(), testS.top());
}

TEST(insert_many, test0) {
  s21::stack<int> test;
  test.insert_many_front(1, 2, 3, 4, 5);
  ASSERT_EQ(test.size(), 5);
  ASSERT_EQ(test.top(), 5);
  test.insert_many_front(6, 7, 8, 9, 0);
  ASSERT_EQ(test.size(), 10);
  ASSERT_EQ(test.top(), 0);
  test.insert_many_front(22, 23, 24, 25, 26);
  ASSERT_EQ(test.size(), 15);
  ASSERT_EQ(test.top(), 26);
}

TEST(ctors, test0) {
  s21::stack<int> st{1, 2, 3, 4, 5};
  s21::stack<int> cpy(st);
  EXPECT_EQ(st.top(), cpy.top());
  s21::stack<int> mv(std::move(st));
  EXPECT_EQ(mv.top(), cpy.top());
  s21::stack<int> cpy_ass;
  cpy_ass = cpy;
  s21::stack<int> mv_ass;
  mv_ass = std::move(mv);
  EXPECT_EQ(mv_ass.top(), cpy_ass.top());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
