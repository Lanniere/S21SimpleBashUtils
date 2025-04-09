#include <gtest/gtest.h>

#include "../container/set/s21_set.h"

TEST(SetTest, InsertAndSize) {
  s21::set<int> new_set;
  new_set.insert(2);
  new_set.insert(1);
  new_set.insert(3);
  new_set.insert(4);
  new_set.insert(5);
  new_set.insert(6);
  EXPECT_EQ(new_set.size(), 6);
}

// Test 2: Проверка инициализации списком и размера
TEST(SetTest, InitializerList) {
  s21::set<int> new_set = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(new_set.size(), 6);
}

// Test 3: Проверка конструктора копирования
TEST(SetTest, CopyConstructor) {
  s21::set<int> old_set = {1, 2, 3, 4, 5, 6};
  s21::set<int> new_set(old_set);
  EXPECT_EQ(new_set.size(), old_set.size());
}

// Test 4: Проверка итератора end()
TEST(SetTest, EndIterator) {
  s21::set<int> old_set = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(*old_set.end(), 6);
}

// Test 5: Проверка empty(), insert() и erase()
TEST(SetTest, EmptyInsertErase) {
  s21::set<int> old_set;
  EXPECT_TRUE(old_set.empty());
  old_set.insert(1);
  EXPECT_FALSE(old_set.empty());
  old_set.erase(old_set.begin());
  EXPECT_TRUE(old_set.empty());
}

// Test 6: Проверка clear()
TEST(SetTest, Clear) {
  s21::set<int> old_set = {1, 2, 3, 4, 5, 6};
  old_set.clear();
  EXPECT_EQ(old_set.size(), 0);
}

// Test 7: Проверка перемещающего оператора присваивания
TEST(SetTest, MoveAssignment) {
  s21::set<int> new_set = {1, 2, 3, 4, 5, 6};
  s21::set<int> old_set = {7, 8, 9, 10, 11};
  old_set = std::move(new_set);
  EXPECT_EQ(old_set.size(), 6);
  EXPECT_EQ(*old_set.begin(), 1);
  EXPECT_EQ(new_set.size(), 0);
}

// Test 8: Проверка swap()
TEST(SetTest, Swap) {
  s21::set<int> new_set = {1, 2, 3, 4, 5, 6};
  s21::set<int> old_set = {7, 8, 9, 10, 11};
  new_set.swap(old_set);
  EXPECT_EQ(new_set.size(), 5);
  EXPECT_EQ(old_set.size(), 6);
  EXPECT_EQ(*new_set.begin(), 7);
  EXPECT_EQ(*old_set.begin(), 1);
}

// Test 9: Проверка merge()
TEST(SetTest, Merge) {
  s21::set<int> new_set = {1, 2, 3, 4, 5, 6};
  s21::set<int> old_set = {7, 8, 9, 10, 11};
  new_set.merge(old_set);
  EXPECT_EQ(new_set.size(), 11);
  EXPECT_EQ(*new_set.end(), 11);
}

// Test 10: Проверка find()
TEST(SetTest, Find) {
  s21::set<int> new_set = {1, 2, 3, 4, 5, 6};
  s21::set<int> old_set = {7, 8, 9, 10, 11};
  new_set.merge(old_set);
  EXPECT_EQ(*new_set.find(5), 5);
  EXPECT_EQ(new_set.find(50), new_set.end());
}

// Test 11: Проверка contains()
TEST(SetTest, Contains) {
  s21::set<int> new_set = {1, 2, 3, 4, 5, 6};
  s21::set<int> old_set = {7, 8, 9, 10, 11};
  new_set.merge(old_set);
  EXPECT_TRUE(new_set.contains(6));
  EXPECT_TRUE(new_set.contains(11));
  EXPECT_FALSE(new_set.contains(50));
  EXPECT_FALSE(new_set.contains(-1));
}

// test 12: проверка инсерт мани
TEST(SetTest, InsertManyBack) {
  s21::set<int> my_set;
  my_set.insert_many_back(1, 2, 3, 4, 5, 6);
  EXPECT_EQ(*my_set.begin(), 1);
  EXPECT_EQ(*my_set.end(), 6);
}
// Тест 13 на выброс ошибки при вставке уже существующего элемента
TEST(SetTest, InsertDuplicateThrowsException) {
  s21::set<int> my_set = {1, 2, 3, 4, 5};
  EXPECT_THROW(my_set.insert(3), std::out_of_range);
}

// Тест 14 для функции insert_many
TEST(SetTest, InsertMany) {
  s21::set<int> my_set = {1, 2, 3};
  auto results = my_set.insert_many_back(4, 5, 6);

  EXPECT_EQ(my_set.size(), 6);  // Проверяем, что размер увеличился
}
