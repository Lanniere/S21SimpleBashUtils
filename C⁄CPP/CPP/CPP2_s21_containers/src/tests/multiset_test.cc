#include <gtest/gtest.h>

#include "../container/multiset/s21_multiset.h"

// Test 1: Вставка элементов и проверка размера
TEST(MultisetTest, InsertAndSize) {
  s21::multiset<int> new_multiset;
  new_multiset.insert(2);
  new_multiset.insert(1);
  new_multiset.insert(3);
  new_multiset.insert(4);
  new_multiset.insert(5);
  new_multiset.insert(6);
  new_multiset.insert(3);
  EXPECT_EQ(new_multiset.size(), 7);
}

// Test 2: Проверка инициализации списком и размера
TEST(MultisetTest, InitializerList) {
  s21::multiset<int> new_multiset = {1, 2, 3, 4, 5, 6, 3};
  EXPECT_EQ(new_multiset.size(), 7);
}

// Test 3: Проверка конструктора копирования
TEST(MultisetTest, CopyConstructor) {
  s21::multiset<int> old_multiset = {1, 2, 3, 4, 5, 6, 3};
  s21::multiset<int> new_multiset(old_multiset);
  EXPECT_EQ(new_multiset.size(), old_multiset.size());
}

// Test 4: Проверка итератора end()
TEST(MultisetTest, EndIterator) {
  s21::multiset<int> old_multiset = {1, 2, 3, 4, 5, 6, 3};
  EXPECT_EQ(*(old_multiset.end()), 6);
}

// Test 5: Проверка empty(), insert() и erase()
TEST(MultisetTest, EmptyInsertErase) {
  s21::multiset<int> old_multiset;
  EXPECT_TRUE(old_multiset.empty());
  old_multiset.insert(1);
  EXPECT_FALSE(old_multiset.empty());
  old_multiset.erase(old_multiset.begin());
  EXPECT_TRUE(old_multiset.empty());
}

// Test 6: Проверка clear()
TEST(MultisetTest, Clear) {
  s21::multiset<int> old_multiset = {1, 2, 3, 4, 5, 6, 3};
  old_multiset.clear();
  EXPECT_EQ(old_multiset.size(), 0);
}

// Test 7: Проверка count()
TEST(MultisetTest, Count) {
  s21::multiset<int> my_multiset = {1, 2, 3, 3, 3, 4, 5};
  EXPECT_EQ(my_multiset.count(3), 3);
  EXPECT_EQ(my_multiset.count(6), 0);
}

// Test 8: Проверка lower_bound()
TEST(MultisetTest, LowerBound) {
  s21::multiset<int> my_multiset = {1, 2, 3, 3, 3, 4, 5};
  EXPECT_EQ(*my_multiset.lower_bound(3), 3);
  EXPECT_EQ(*my_multiset.lower_bound(2), 2);
}

// Test 9: Проверка upper_bound()
TEST(MultisetTest, UpperBound) {
  s21::multiset<int> my_multiset = {1, 2, 3, 3, 3, 4, 5};
  EXPECT_EQ(*my_multiset.upper_bound(5), 5);
}

// Test 10: Проверка equal_range()
TEST(MultisetTest, EqualRange) {
  s21::multiset<int> my_multiset = {1, 2, 3, 3, 3, 4, 5};
  auto range = my_multiset.equal_range(3);
  EXPECT_EQ(*range.first, 3);
  EXPECT_EQ(*(range.second), 3);
}
