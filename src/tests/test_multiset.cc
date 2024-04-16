// Copyright 2023 tcinthia

#include "../s21_containers.h"

TEST(multisetCtor, test0) {
  s21::multiset<int> multiset;
  multiset.insert(1);
  multiset.insert(2);
  multiset.insert(3);
  s21::multiset<int> cpy(multiset);
  s21::multiset<int> mv(std::move(multiset));
  EXPECT_EQ(cpy.size(), mv.size());
  auto cpy_it = cpy.begin();
  auto mv_it = mv.begin();
  for (; cpy_it != cpy.end() && mv_it != mv.end(); ++cpy_it, ++mv_it)
    EXPECT_EQ(*cpy_it, *mv_it);
  s21::multiset<int> cpy_ass;
  s21::multiset<int> mv_ass;
  cpy_ass = cpy;
  mv_ass = std::move(mv);
  EXPECT_EQ(cpy_ass.size(), mv_ass.size());
  cpy_it = cpy_ass.begin();
  mv_it = mv_ass.begin();
  for (; cpy_it != cpy_ass.end() && mv_it != mv_ass.end(); ++cpy_it, ++mv_it)
    EXPECT_EQ(*cpy_it, *mv_it);
}

TEST(multisetInitListCtor, test0) {
  s21::multiset<int> s21{10, 53, 35, 6, 15, 20};
  std::multiset<int> s{10, 53, 35, 6, 15, 20};
  auto s21it = s21.begin();
  auto it = s.begin();
  EXPECT_EQ(s21.size(), s.size());
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
}

TEST(multisetTestInsert, test0) {
  s21::multiset<int> s21{10, 53, 35, 6, 6, 6};
  std::multiset<int> s{10, 53, 35, 6, 6, 6};
  auto pos21 = s21.insert(11);
  auto pos = s.insert(11);
  EXPECT_EQ(*pos21, *pos);
  auto s21it = s21.begin();
  auto it = s.begin();
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
  pos21 = s21.insert(1);
  pos = s.insert(1);
  EXPECT_EQ(*pos21, *pos);
  s21it = s21.begin();
  it = s.begin();
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
  pos21 = s21.insert(999);
  pos = s.insert(999);
  EXPECT_EQ(*pos21, *pos);
  s21it = s21.begin();
  it = s.begin();
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
}

TEST(multisetTestClear, test0) {
  s21::multiset<int> s21{10, 53, 35, 6, 15, 20};
  std::multiset<int> s{10, 53, 35, 6, 15, 20};
  s21.clear();
  s.clear();
  EXPECT_EQ(s21.size(), s.size());
}

TEST(multisetTestErase, test0) {
  s21::multiset<int> s21{10, 53, 35, 6, 6, 6};
  std::multiset<int> s{10, 53, 35, 6, 6, 6};
  auto s21it = s21.begin();
  auto it = s.begin();
  ++it;
  ++s21it;
  s21.erase(s21it);
  s.erase(it);
  EXPECT_EQ(s21.size(), s.size());
  s21it = s21.begin();
  it = s.begin();
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
}

TEST(multisetUtility, test0) {
  const s21::multiset<int> s21{10, 53, 35, 6, 6, 6, 7, 7};
  const std::multiset<int> s{10, 53, 35, 6, 6, 6, 7, 7};

  auto s21it = s21.begin();
  auto it = s.begin();
  EXPECT_EQ(s21.size(), s.size());
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
  EXPECT_FALSE(s21.empty());
  EXPECT_NE(s21.max_size(), 0);
  EXPECT_EQ(s21.count(6), s.count(6));
  EXPECT_EQ(s21.count(10), s.count(10));
  EXPECT_EQ(s21.count(7), s.count(7));
  EXPECT_EQ(s21.count(8), s.count(8));
}

TEST(multisetRange, test0) {
  s21::multiset<int> s21{10, 53, 35, 6, 6, 6, 7, 7};
  std::multiset<int> s{10, 53, 35, 6, 6, 6, 7, 7};
  auto range21 = s21.equal_range(6);
  auto range = s.equal_range(6);
  EXPECT_EQ(*range21.first, *range.first);
  EXPECT_EQ(*range21.second, *range.second);
  range21 = s21.equal_range(7);
  range = s.equal_range(7);
  EXPECT_EQ(*range21.first, *range.first);
  EXPECT_EQ(*range21.second, *range.second);
  range21 = s21.equal_range(53);
  range = s.equal_range(53);
  EXPECT_EQ(*range21.first, *range.first);
  EXPECT_EQ(range.second, s.end());
  EXPECT_EQ(range21.second, s21.end());
}

TEST(multisetBounds, test0) {
  s21::multiset<int> s21{10, 53, 35, 6, 6, 6, 7, 7};
  std::multiset<int> s{10, 53, 35, 6, 6, 6, 7, 7};
  auto range21 = s21.lower_bound(6);
  auto range = s.lower_bound(6);
  EXPECT_EQ(*range21, *range);
  range21 = s21.lower_bound(7);
  range = s.lower_bound(7);
  EXPECT_EQ(*range21, *range);
  range21 = s21.lower_bound(53);
  range = s.lower_bound(53);
  EXPECT_EQ(*range21, *range);
  range21 = s21.upper_bound(6);
  range = s.upper_bound(6);
  EXPECT_EQ(*range21, *range);
  range21 = s21.upper_bound(7);
  range = s.upper_bound(7);
  EXPECT_EQ(*range21, *range);
  range21 = s21.upper_bound(53);
  range = s.upper_bound(53);
  EXPECT_EQ(range21, s21.end());
  EXPECT_EQ(range, s.end());
}

TEST(multisetFind, test0) {
  s21::multiset<int> s21{10, 53, 35, 6, 15, 20};
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

TEST(multisetMerge, test0) {
  s21::multiset<int> s21{10, 53, 35, 6, 15, 20};
  s21::multiset<int> merges21{11, 14, 6, 6, 6};
  std::multiset<int> se{10, 53, 35, 6, 15, 20};
  std::multiset<int> merges{11, 14, 6, 6, 6};
  s21.merge(merges21);
  se.merge(merges);
  auto s21it = s21.begin();
  auto it = se.begin();
  for (; s21it != s21.end() && it != se.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
}

TEST(multisetMerge, test1) {
  s21::multiset<int> s21{10, 53, 35, 6, 15, 20};
  s21::multiset<int> merges21{11, 14, 15, 7, 100};
  std::multiset<int> se{10, 53, 35, 6, 15, 20};
  std::multiset<int> merges{11, 14, 15, 7, 100};
  s21.merge(merges21);
  se.merge(merges);
  auto s21it = s21.begin();
  auto it = se.begin();
  for (; s21it != s21.end() && it != se.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
}

TEST(multisetMerge, test2) {
  s21::multiset<int> s21{10, 53, 35, 6, 15, 20};
  s21::multiset<int> merges21;
  std::multiset<int> se{10, 53, 35, 6, 15, 20};
  std::multiset<int> merges;
  s21.merge(merges21);
  se.merge(merges);
  auto s21it = s21.begin();
  auto it = se.begin();
  for (; s21it != s21.end() && it != se.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
}

TEST(multisetInsertMany, test0) {
  s21::multiset<int> s21{10, 53, 35, 6, 15, 20};
  std::multiset<int> se{10, 53, 35, 6, 15, 20};

  s21.insert_many(11, 14, 22);
  se.insert(11);
  se.insert(14);
  se.insert(22);
  auto s21it = s21.begin();
  auto it = se.begin();
  for (; s21it != s21.end() && it != se.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
}

TEST(multisetInsertMany, test1) {
  s21::multiset<int> s21;
  std::multiset<int> se;
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

TEST(multisetInsertMany, test2) {
  s21::multiset<int> s21{10, 53, 35, 6, 15, 20};
  std::multiset<int> se{10, 53, 35, 6, 15, 20};
  s21.insert_many(10, 53, 35);
  se.insert(10);
  se.insert(53);
  se.insert(35);
  auto s21it = s21.begin();
  auto it = se.begin();
  for (; s21it != s21.end() && it != se.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
}

TEST(multisetSwap, test0) {
  s21::multiset<int> s21{10, 53, 35, 6, 15, 20};
  s21::multiset<int> s21_swap{10, 53, 35};
  std::multiset<int> s{10, 53, 35, 6, 15, 20};
  std::multiset<int> s_swap{10, 53, 35};
  s.swap(s_swap);
  s21.swap(s21_swap);
  auto s21it = s21.begin();
  auto it = s.begin();
  EXPECT_EQ(s21.size(), s.size());
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it)
    EXPECT_EQ(*s21it, *it);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
