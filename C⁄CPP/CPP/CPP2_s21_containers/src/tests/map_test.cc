#include <gtest/gtest.h>

#include "../container/map/s21_map.h"

// Test 1: Проверка инициализации списком и размера
TEST(MapTest, InitializerList) {
  s21::map<int, int> map1 = {{1, 2}, {3, 4}, {5, 6}};
  EXPECT_EQ(map1.size(), 3);
}

// Test 2: Проверка конструктора копирования
TEST(MapTest, CopyConstructor) {
  s21::map<int, int> map1 = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> map2(map1);
  EXPECT_EQ(map2.size(), 3);
  EXPECT_EQ(map1.size(), 3);
}

// Test 3: Проверка перемещающего конструктора
TEST(MapTest, MoveConstructor) {
  s21::map<int, int> map1 = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> map2(std::move(map1));
  EXPECT_EQ(map2.size(), 3);
  EXPECT_EQ(map1.size(), 0);
}

// Test 4: Проверка оператора присваивания
TEST(MapTest, AssignmentOperator) {
  s21::map<int, int> map1 = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> map2;
  map2 = map1;
  EXPECT_EQ(map2.size(), 3);
  EXPECT_EQ(map1.size(), 3);
}

// Test 5: Проверка перемещающего оператора присваивания
TEST(MapTest, MoveAssignmentOperator) {
  s21::map<int, int> map1 = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> map2;
  map2 = std::move(map1);
  EXPECT_EQ(map2.size(), 3);
  EXPECT_EQ(map1.size(), 0);
}

// Test 6: Проверка begin()
TEST(MapTest, Begin) {
  s21::map<int, int> map1 = {{1, 2}, {3, 4}, {5, 6}};
  EXPECT_EQ((*map1.begin()).first, 1);
  EXPECT_EQ((*map1.begin()).second, 2);
}

// Test 7: Проверка end()
TEST(MapTest, End) {
  s21::map<int, int> map1 = {{1, 2}, {3, 4}, {5, 6}};
  EXPECT_EQ((*map1.end()).first, 5);
  EXPECT_EQ((*map1.end()).second, 6);
}

// Test 8: Проверка at()
TEST(MapTest, At) {
  s21::map<int, int> map1 = {{1, 2}, {3, 4}, {5, 6}};
  EXPECT_EQ(map1.at(1), 2);
  EXPECT_THROW(map1.at(10),
               std::out_of_range);  // Проверка на выброс исключения
}

// Test 9: Проверка operator[]
TEST(MapTest, OperatorBrackets) {
  s21::map<int, int> map1 = {{1, 2}, {3, 4}, {5, 6}};
  EXPECT_EQ(map1[5], 6);
}

// Test 10: Проверка clear()
TEST(MapTest, Clear) {
  s21::map<int, int> map1 = {{1, 2}, {3, 4}, {5, 6}};
  map1.clear();
  EXPECT_EQ(map1.size(), 0);
}

// Test 11: Проверка insert()
TEST(MapTest, Insert) {
  s21::map<int, int> map1;
  map1.insert({1, 2});
  map1.insert({3, 4});
  map1.insert({5, 6});
  EXPECT_EQ(map1.size(), 3);
}

// Test 12: Проверка insert_or_assign()
TEST(MapTest, InsertOrAssign) {
  s21::map<int, int> map1;
  map1.insert_or_assign(1, 2);
  map1.insert_or_assign(3, 4);
  map1.insert_or_assign(1, 5);  // Обновление значения
  EXPECT_EQ(map1.size(), 2);
  EXPECT_EQ(map1[1], 5);
}

// Test 13: Проверка erase()
TEST(MapTest, Erase) {
  s21::map<int, int> map1 = {{1, 2}, {3, 4}, {5, 6}};
  map1.erase(map1.begin());
  EXPECT_EQ(map1.size(), 2);
  EXPECT_EQ((*map1.begin()).first, 3);
}

// Test 14: Проверка swap()
TEST(MapTest, Swap) {
  s21::map<int, int> map1 = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> map2 = {{7, 8}, {9, 10}};
  map1.swap(map2);
  EXPECT_EQ(map1.size(), 2);
  EXPECT_EQ(map2.size(), 3);
}

// Test 15: Проверка merge()
TEST(MapTest, Merge) {
  s21::map<int, int> map1 = {{1, 2}, {3, 4}};
  s21::map<int, int> map2 = {{5, 6}, {7, 8}};
  map1.merge(map2);
  EXPECT_EQ(map1.size(), 4);
  EXPECT_EQ(map2.size(), 2);
}

// Test 16: Проверка contains()
TEST(MapTest, Contains) {
  s21::map<int, int> map1 = {{1, 2}, {3, 4}, {5, 6}};
  EXPECT_TRUE(map1.contains(1));
  EXPECT_FALSE(map1.contains(10));
}

// Test 17: Проверка insert_many()
TEST(MapTest, InsertMany) {
  s21::map<int, int> map1 = {{1, 2}, {3, 4}};
  auto results =
      map1.insert_many_back(std::make_pair(5, 6), std::make_pair(7, 8));

  EXPECT_EQ(map1.size(), 4);  // Проверяем, что размер увеличился
}