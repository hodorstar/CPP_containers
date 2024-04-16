// Copyright 2023 tcinthia

#include "../s21_containers.h"

TEST(setCtor, test0) {
  s21::set<int> set;
  set.insert(1);
  set.insert(2);
  set.insert(3);
  s21::set<int> cpy(set);
  s21::set<int> mv(std::move(set));
  EXPECT_EQ(cpy.size(), mv.size());
  auto cpy_it = cpy.begin();
  auto mv_it = mv.begin();
  for (; cpy_it != cpy.end() && mv_it != mv.end(); ++cpy_it, ++mv_it)
    EXPECT_EQ(*cpy_it, *mv_it);
  s21::set<int> cpy_ass;
  s21::set<int> mv_ass;
  cpy_ass = cpy;
  mv_ass = std::move(mv);
  EXPECT_EQ(cpy_ass.size(), mv_ass.size());
  cpy_it = cpy_ass.begin();
  mv_it = mv_ass.begin();
  for (; cpy_it != cpy_ass.end() && mv_it != mv_ass.end(); ++cpy_it, ++mv_it)
    EXPECT_EQ(*cpy_it, *mv_it);
}

TEST(setInitListCtor, test0) {
  s21::set<int> s21{10, 53, 35, 6, 15, 20};
  std::set<int> s{10, 53, 35, 6, 15, 20};
  auto s21it = s21.begin();
  auto it = s.begin();
  EXPECT_EQ(s21.size(), s.size());
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
}

TEST(setTestInsert, test0) {
  s21::set<int> s21{10, 53, 35, 6, 15, 20};
  std::set<int> s{10, 53, 35, 6, 15, 20};
  auto pos21 = s21.insert(11);
  auto pos = s.insert(11);
  EXPECT_EQ(*pos21.first, *pos.first);
  EXPECT_EQ(pos21.second, pos.second);
  auto s21it = s21.begin();
  auto it = s.begin();
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
  pos21 = s21.insert(1);
  pos = s.insert(1);
  EXPECT_EQ(*pos21.first, *pos.first);
  EXPECT_EQ(pos21.second, pos.second);
  s21it = s21.begin();
  it = s.begin();
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
  pos21 = s21.insert(999);
  pos = s.insert(999);
  EXPECT_EQ(*pos21.first, *pos.first);
  EXPECT_EQ(pos21.second, pos.second);
  s21it = s21.begin();
  it = s.begin();
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
}

TEST(setTestClear, test0) {
  s21::set<int> s21{10, 53, 35, 6, 15, 20};
  std::set<int> s{10, 53, 35, 6, 15, 20};
  s21.clear();
  s.clear();
  EXPECT_EQ(s21.size(), s.size());
}

TEST(setTestErase, test0) {
  s21::set<int> s21{10, 53, 35, 6, 15, 20};
  std::set<int> s{10, 53, 35, 6, 15, 20};
  auto s21it = s21.begin();
  auto it = s.begin();
  ++ ++ ++ ++s21it;
  ++ ++ ++ ++it;
  s21.erase(s21it);
  s.erase(it);
  EXPECT_EQ(s21.size(), s.size());
  s21it = s21.begin();
  it = s.begin();
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
}

TEST(setTestErase, test1) {
  s21::set<int> s21{-3, -1, -5, -7, -6, -8, -9};
  s21.erase(s21.find(-1));
}

TEST(setTestErase, test2) {
  s21::set<int> s21{-3, -1, -5, -7};
  s21.erase(s21.find(-1));
}

TEST(setTestErase, test3) {
  s21::set<int> s21{-3, -1, -5, -4};
  s21.erase(s21.find(-1));
}

TEST(setUtility, test0) {
  const s21::set<int> s21{10, 53, 35, 6, 15, 20};
  const s21::set<int> empty;
  const std::set<int> s{10, 53, 35, 6, 15, 20};
  auto s21it = empty.begin();
  s21it = empty.end();
  s21it = s21.begin();
  auto it = s.begin();
  EXPECT_EQ(s21.size(), s.size());
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
  EXPECT_FALSE(s21.empty());
  EXPECT_NE(s21.max_size(), 0);
}

TEST(setSwap, test0) {
  s21::set<int> s21{10, 53, 35, 6, 15, 20};
  s21::set<int> s21_swap{10, 53, 35};
  std::set<int> s{10, 53, 35, 6, 15, 20};
  std::set<int> s_swap{10, 53, 35};
  s.swap(s_swap);
  s21.swap(s21_swap);
  auto s21it = s21.begin();
  auto it = s.begin();
  EXPECT_EQ(s21.size(), s.size());
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
}

TEST(setFind, test0) {
  s21::set<int> s21{10, 53, 35, 6, 15, 20};
  EXPECT_EQ(*s21.find(15), 15);
  EXPECT_EQ(*s21.find(53), 53);
  EXPECT_EQ(*s21.find(6), 6);
  EXPECT_EQ(*s21.find(20), 20);
  EXPECT_EQ(s21.find(66), s21.end());
  EXPECT_TRUE(s21.contains(15));
  EXPECT_TRUE(s21.contains(53));
  EXPECT_TRUE(s21.contains(6));
  EXPECT_TRUE(s21.contains(20));
  EXPECT_FALSE(s21.contains(66));
}

TEST(setMerge, test0) {
  s21::set<int> s21{10, 53, 35, 6, 15, 20};
  s21::set<int> merges21{11, 14, 6, 6, 6};
  std::set<int> se{10, 53, 35, 6, 15, 20};
  std::set<int> merges{11, 14, 6, 6, 6};
  s21.merge(merges21);
  se.merge(merges);
  auto s21it = s21.begin();
  auto it = se.begin();
  for (; s21it != s21.end() && it != se.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
}

TEST(setMerge, test1) {
  s21::set<int> s21{10, 53, 35, 6, 15, 20};
  s21::set<int> merges21{11, 14, 15, 7, 100};
  std::set<int> se{10, 53, 35, 6, 15, 20};
  std::set<int> merges{11, 14, 15, 7, 100};
  s21.merge(merges21);
  se.merge(merges);
  auto s21it = s21.begin();
  auto it = se.begin();
  for (; s21it != s21.end() && it != se.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
}

TEST(setMerge, test2) {
  s21::set<int> s21{10, 53, 35, 6, 15, 20};
  s21::set<int> merges21;
  std::set<int> se{10, 53, 35, 6, 15, 20};
  std::set<int> merges;
  s21.merge(merges21);
  se.merge(merges);
  auto s21it = s21.begin();
  auto it = se.begin();
  for (; s21it != s21.end() && it != se.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
}

TEST(setInsertMany, test0) {
  s21::set<int> s21{10, 53, 35, 6, 15, 20};
  std::set<int> se{10, 53, 35, 6, 15, 20};
  s21.insert_many(11, 14, 22);
  se.insert(11);
  se.insert(14);
  se.insert(22);
  auto s21it = s21.begin();
  auto it = se.begin();
  for (; s21it != s21.end() && it != se.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
}

TEST(setInsertMany, test1) {
  s21::set<int> s21;
  std::set<int> se;
  s21.insert_many(10, 53, 35, 6, 15, 20);
  se.insert(10);
  se.insert(53);
  se.insert(35);
  se.insert(6);
  se.insert(15);
  se.insert(20);
  auto s21it = s21.begin();
  auto it = se.begin();
  for (; s21it != s21.end() && it != se.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
}

TEST(setInsertMany, test2) {
  s21::set<int> s21{10, 53, 35, 6, 15, 20};
  std::set<int> se{10, 53, 35, 6, 15, 20};
  s21.insert_many(10, 53, 35);
  se.insert(10);
  se.insert(53);
  se.insert(35);
  auto s21it = s21.begin();
  auto it = se.begin();
  for (; s21it != s21.end() && it != se.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
