// Copyright 2023 tcinthia

#include "../s21_containers.h"

TEST(mapCtor, test0) {
  s21::map<char, int> set;
  set.insert('a', 1);
  set.insert('b', 2);
  set.insert('c', 3);
  s21::map<char, int> cpy(set);
  s21::map<char, int> mv(std::move(set));
  EXPECT_EQ(cpy.size(), mv.size());
  auto cpy_it = cpy.begin();
  auto mv_it = mv.begin();
  for (; cpy_it != cpy.end() && mv_it != mv.end(); ++cpy_it, ++mv_it)
    EXPECT_EQ(*cpy_it, *mv_it);
  s21::map<char, int> cpy_ass;
  s21::map<char, int> mv_ass;
  cpy_ass = cpy;
  mv_ass = std::move(mv);
  EXPECT_EQ(cpy_ass.size(), mv_ass.size());
  cpy_it = cpy_ass.begin();
  mv_it = mv_ass.begin();
  for (; cpy_it != cpy_ass.end() && mv_it != mv_ass.end(); ++cpy_it, ++mv_it)
    EXPECT_EQ(*cpy_it, *mv_it);
}

TEST(mapInitListCtor, test0) {
  s21::map<char, int> s21{{'a', 10}, {'b', 53}, {'c', 35},
                          {'v', 6},  {'a', 15}, {'k', 20}};
  std::map<char, int> s{{'a', 10}, {'b', 53}, {'c', 35},
                        {'v', 6},  {'a', 15}, {'k', 20}};
  auto s21it = s21.begin();
  auto it = s.begin();
  EXPECT_EQ(s21.size(), s.size());
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it) {
    EXPECT_EQ(s21it->key, it->first);
    EXPECT_EQ(s21it->value, it->second);
  }
}

TEST(mapTestInsert, test0) {
  s21::map<char, int> s21{{'a', 10}, {'b', 53}, {'c', 35},
                          {'v', 6},  {'g', 15}, {'k', 20}};
  std::map<char, int> s{{'a', 10}, {'b', 53}, {'c', 35},
                        {'v', 6},  {'g', 15}, {'k', 20}};
  auto pos21 = s21.insert('j', 11);
  auto pos = s.insert(std::make_pair('j', 11));
  EXPECT_EQ(pos21.first->key, pos.first->first);
  EXPECT_EQ(pos21.first->value, pos.first->second);
  EXPECT_EQ(pos21.second, pos.second);
  auto s21it = s21.begin();
  auto it = s.begin();
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it) {
    EXPECT_EQ(pos21.first->key, pos.first->first);
    EXPECT_EQ(pos21.first->value, pos.first->second);
    EXPECT_EQ(pos21.second, pos.second);
  }
  pos21 = s21.insert('a', 1);
  pos = s.insert(std::make_pair('a', 1));
  EXPECT_EQ(pos21.first->key, pos.first->first);
  EXPECT_EQ(pos21.first->value, pos.first->second);
  EXPECT_EQ(pos21.second, pos.second);
  s21it = s21.begin();
  it = s.begin();
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it) {
    EXPECT_EQ(pos21.first->key, pos.first->first);
    EXPECT_EQ(pos21.first->value, pos.first->second);
    EXPECT_EQ(pos21.second, pos.second);
  }
  pos21 = s21.insert(std::make_pair('z', 999));
  pos = s.insert(std::make_pair('z', 999));
  EXPECT_EQ(pos21.first->key, pos.first->first);
  EXPECT_EQ(pos21.first->value, pos.first->second);
  EXPECT_EQ(pos21.second, pos.second);
  s21it = s21.begin();
  it = s.begin();
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it) {
    EXPECT_EQ(pos21.first->key, pos.first->first);
    EXPECT_EQ(pos21.first->value, pos.first->second);
    EXPECT_EQ(pos21.second, pos.second);
  }
}

TEST(mapTestInsertAssign, test0) {
  s21::map<char, int> s21{{'a', 10}, {'b', 53}, {'c', 35},
                          {'v', 6},  {'g', 15}, {'k', 20}};
  std::map<char, int> s{{'a', 10}, {'b', 53}, {'c', 35},
                        {'v', 6},  {'g', 15}, {'k', 20}};
  auto pos21 = s21.insert_or_assign('j', 11);
  auto pos = s.insert_or_assign('j', 11);
  EXPECT_EQ(pos21.first->key, pos.first->first);
  EXPECT_EQ(pos21.first->value, pos.first->second);
  EXPECT_EQ(pos21.second, pos.second);
  auto s21it = s21.begin();
  auto it = s.begin();
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it) {
    EXPECT_EQ(pos21.first->key, pos.first->first);
    EXPECT_EQ(pos21.first->value, pos.first->second);
    EXPECT_EQ(pos21.second, pos.second);
  }
  pos21 = s21.insert_or_assign('a', 1);
  pos = s.insert_or_assign('a', 1);
  EXPECT_EQ(pos21.first->key, pos.first->first);
  EXPECT_EQ(pos21.first->value, pos.first->second);
  EXPECT_EQ(pos21.second, pos.second);
  s21it = s21.begin();
  it = s.begin();
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it) {
    EXPECT_EQ(pos21.first->key, pos.first->first);
    EXPECT_EQ(pos21.first->value, pos.first->second);
    EXPECT_EQ(pos21.second, pos.second);
  }
  pos21 = s21.insert_or_assign('z', 999);
  pos = s.insert_or_assign('z', 999);
  EXPECT_EQ(pos21.first->key, pos.first->first);
  EXPECT_EQ(pos21.first->value, pos.first->second);
  EXPECT_EQ(pos21.second, pos.second);
  s21it = s21.begin();
  it = s.begin();
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it) {
    EXPECT_EQ(pos21.first->key, pos.first->first);
    EXPECT_EQ(pos21.first->value, pos.first->second);
    EXPECT_EQ(pos21.second, pos.second);
  }
}

TEST(mapTestClear, test0) {
  s21::map<char, int> s21{{'a', 10}, {'b', 53}, {'c', 35},
                          {'v', 6},  {'g', 15}, {'k', 20}};
  std::map<char, int> s{{'a', 10}, {'b', 53}, {'c', 35},
                        {'v', 6},  {'g', 15}, {'k', 20}};
  s21.clear();
  s.clear();
  EXPECT_EQ(s21.size(), s.size());
}

TEST(mapTestErase, test0) {
  s21::map<char, int> s21{{'a', 10}, {'b', 53}, {'c', 35},
                          {'v', 6},  {'g', 15}, {'k', 20}};
  std::map<char, int> s{{'a', 10}, {'b', 53}, {'c', 35},
                        {'v', 6},  {'g', 15}, {'k', 20}};
  auto s21it = s21.begin();
  auto it = s.begin();
  ++ ++ ++ ++s21it;
  ++ ++ ++ ++it;
  s21.erase(s21it);
  s.erase(it);
  EXPECT_EQ(s21.size(), s.size());
  s21it = s21.begin();
  it = s.begin();
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it) {
    EXPECT_EQ(s21it->key, it->first);
    EXPECT_EQ(s21it->value, it->second);
  }
}

TEST(mapUtility, test0) {
  const s21::map<char, int> s21{{'a', 10}, {'b', 53}, {'c', 35},
                                {'v', 6},  {'g', 15}, {'k', 20}};
  const s21::map<char, int> empty;
  const std::map<char, int> s{{'a', 10}, {'b', 53}, {'c', 35},
                              {'v', 6},  {'g', 15}, {'k', 20}};
  auto s21it = empty.begin();
  s21it = empty.end();
  s21it = s21.begin();
  auto it = s.begin();
  EXPECT_EQ(s21.size(), s.size());
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it) {
    EXPECT_EQ(s21it->key, it->first);
    EXPECT_EQ(s21it->value, it->second);
  }
  EXPECT_FALSE(s21.empty());
  EXPECT_NE(s21.max_size(), 0);
}

TEST(mapSwap, test0) {
  s21::map<char, int> s21{{'a', 10}, {'b', 53}, {'c', 35},
                          {'v', 6},  {'g', 15}, {'k', 20}};
  s21::map<char, int> s21_swap{{'z', 10}, {'x', 53}, {'c', 35}};
  std::map<char, int> s{{'a', 10}, {'b', 53}, {'c', 35},
                        {'v', 6},  {'g', 15}, {'k', 20}};
  std::map<char, int> s_swap{{'z', 10}, {'x', 53}, {'c', 35}};
  s.swap(s_swap);
  s21.swap(s21_swap);
  auto s21it = s21.begin();
  auto it = s.begin();
  EXPECT_EQ(s21.size(), s.size());
  for (; s21it != s21.end() && it != s.end(); ++it, ++s21it) {
    EXPECT_EQ(s21it->key, it->first);
    EXPECT_EQ(s21it->value, it->second);
    EXPECT_EQ(s21[s21it->key], s[it->first]);
    EXPECT_EQ(s21.at(s21it->key), s.at(it->first));
  }
  EXPECT_ANY_THROW(s21.at('.'));
  s21['.'] = 100;
  EXPECT_EQ(s21['.'], 100);
}

TEST(mapFind, test0) {
  s21::map<char, int> s21{{'a', 10}, {'b', 53}, {'c', 35},
                          {'v', 6},  {'g', 15}, {'k', 20}};
  EXPECT_EQ(s21.find('g')->value, 15);
  EXPECT_EQ(s21.find('b')->value, 53);
  EXPECT_EQ(s21.find('v')->value, 6);
  EXPECT_EQ(s21.find('k')->value, 20);
  EXPECT_EQ(s21.find('z'), s21.end());
  EXPECT_TRUE(s21.contains('a'));
  EXPECT_TRUE(s21.contains('b'));
  EXPECT_TRUE(s21.contains('c'));
  EXPECT_TRUE(s21.contains('g'));
  EXPECT_FALSE(s21.contains('z'));
}

TEST(mapMerge, test0) {
  s21::map<char, int> s21{{'a', 10}, {'b', 53}, {'c', 35},
                          {'v', 6},  {'g', 15}, {'k', 20}};
  s21::map<char, int> merges21{{'z', 10}, {'x', 53}, {'c', 35}, {'v', 55}};
  std::map<char, int> ma{{'a', 10}, {'b', 53}, {'c', 35},
                         {'v', 6},  {'g', 15}, {'k', 20}};
  std::map<char, int> merges{{'z', 10}, {'x', 53}, {'c', 35}, {'v', 55}};
  s21.merge(merges21);
  ma.merge(merges);
  auto s21it = s21.begin();
  auto it = ma.begin();
  for (; s21it != s21.end() && it != ma.end(); ++it, ++s21it) {
    EXPECT_EQ(s21it->key, it->first);
    EXPECT_EQ(s21it->value, it->second);
  }
}

TEST(mapMerge, test1) {
  s21::map<char, int> s21{{'a', 10}, {'b', 53}, {'c', 35},
                          {'v', 6},  {'g', 15}, {'k', 20}};
  s21::map<char, int> merges21;
  std::map<char, int> ma{{'a', 10}, {'b', 53}, {'c', 35},
                         {'v', 6},  {'g', 15}, {'k', 20}};
  std::map<char, int> merges;
  s21.merge(merges21);
  ma.merge(merges);
  auto s21it = s21.begin();
  auto it = ma.begin();
  for (; s21it != s21.end() && it != ma.end(); ++it, ++s21it) {
    EXPECT_EQ(s21it->key, it->first);
    EXPECT_EQ(s21it->value, it->second);
  }
}

TEST(mapInsertMany, test0) {
  s21::map<char, int> s21{{'a', 10}, {'b', 53}, {'c', 35},
                          {'v', 6},  {'g', 15}, {'k', 20}};
  std::map<char, int> se{{'a', 10}, {'b', 53}, {'c', 35},
                         {'v', 6},  {'g', 15}, {'k', 20}};
  s21.insert_many(std::make_pair('z', 11), std::make_pair('x', 14),
                  std::make_pair('c', 11), std::make_pair('z', 11));
  se.insert(std::make_pair('z', 11));
  se.insert(std::make_pair('x', 14));
  se.insert(std::make_pair('c', 11));
  se.insert(std::make_pair('z', 11));
  auto s21it = s21.begin();
  auto it = se.begin();
  for (; s21it != s21.end() && it != se.end(); ++it, ++s21it) {
    EXPECT_EQ(s21it->key, it->first);
    EXPECT_EQ(s21it->value, it->second);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
