#include <gtest/gtest.h>

#include <stdexcept>

#include "../container/array/s21_array.h"

// Тест конструктора по умолчанию
TEST(ArrayTests, DefaultConstructor) {
  s21::array<int, 5> arr;
  EXPECT_EQ(arr.size(), 5);
  // Для built-in типов, используя value initialization, значения должны быть 0.
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 0);
  }
}

// Тест конструктора через initializer_list
TEST(ArrayTests, InitializerListConstructor) {
  s21::array<int, 5> arr = {1, 2, 3};
  EXPECT_EQ(arr.size(), 5);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
  // Остальные элементы инициализируются по умолчанию (0 для int)
  EXPECT_EQ(arr[3], 0);
  EXPECT_EQ(arr[4], 0);
}

// Тест копирующего конструктора
TEST(ArrayTests, CopyConstructor) {
  s21::array<int, 4> arr = {10, 20, 30, 40};
  s21::array<int, 4> copy(arr);
  EXPECT_EQ(copy.size(), 4);
  for (size_t i = 0; i < copy.size(); ++i) {
    EXPECT_EQ(copy[i], arr[i]);
  }
}

// Тест перемещающего конструктора
TEST(ArrayTests, MoveConstructor) {
  s21::array<int, 3> arr = {5, 6, 7};
  s21::array<int, 3> moved(std::move(arr));
  EXPECT_EQ(moved.size(), 3);
  EXPECT_EQ(moved[0], 5);
  EXPECT_EQ(moved[1], 6);
  EXPECT_EQ(moved[2], 7);
  // После перемещения исходный объект может оказаться в нулевом состоянии
}

// Тест оператора перемещающего присваивания
TEST(ArrayTests, MoveAssignmentOperator) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  s21::array<int, 4> arr2;
  arr2 = std::move(arr);
  EXPECT_EQ(arr2.size(), 4);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
  EXPECT_EQ(arr2[3], 4);
}

// Тест метода at() и проверка выброса исключения при выходе за диапазон
TEST(ArrayTests, AtMethod) {
  s21::array<int, 3> arr = {100, 200, 300};
  EXPECT_EQ(arr.at(0), 100);
  EXPECT_EQ(arr.at(1), 200);
  EXPECT_EQ(arr.at(2), 300);
  EXPECT_THROW(arr.at(3), std::out_of_range);
}

// Тест оператора []
TEST(ArrayTests, BracketOperator) {
  s21::array<int, 3> arr = {10, 20, 30};
  EXPECT_EQ(arr[0], 10);
  EXPECT_EQ(arr[1], 20);
  EXPECT_EQ(arr[2], 30);
}

// Тест методов front() и back()
TEST(ArrayTests, FrontAndBack) {
  s21::array<int, 4> arr = {7, 8, 9, 10};
  EXPECT_EQ(arr.front(), 7);
  EXPECT_EQ(arr.back(), 10);
}

// Тест методов data(), begin() и end()
TEST(ArrayTests, DataAndIterators) {
  s21::array<int, 3> arr = {1, 2, 3};
  auto it = arr.data();
  EXPECT_EQ(*it, 1);
  int sum = 0;
  for (auto iter = arr.begin(); iter != arr.end(); ++iter) {
    sum += *iter;
  }
  EXPECT_EQ(sum, 6);
}

// Тест функций empty(), size() и max_size()
TEST(ArrayTests, EmptySizeMaxSize) {
  s21::array<int, 6> arr;
  EXPECT_FALSE(arr.empty());
  EXPECT_EQ(arr.size(), 6);
  EXPECT_EQ(arr.max_size(), 6);
}

// Тест метода swap()
TEST(ArrayTests, SwapFunction) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2 = {4, 5, 6};
  arr1.swap(arr2);
  EXPECT_EQ(arr1[0], 4);
  EXPECT_EQ(arr1[1], 5);
  EXPECT_EQ(arr1[2], 6);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

// Тест метода fill()
TEST(ArrayTests, FillFunction) {
  s21::array<int, 4> arr;
  arr.fill(99);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 99);
  }
}
