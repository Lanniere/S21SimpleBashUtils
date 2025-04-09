#include <gtest/gtest.h>

#include "../container/vector/s21_vector.h"

TEST(VectorTests, DefaultConstructor) {
  s21::vector<int> vec;
  EXPECT_EQ(vec.size(), 0);
  EXPECT_TRUE(vec.empty());
}

TEST(VectorTests, SizeConstructor) {
  s21::vector<int> vec(5);
  EXPECT_EQ(vec.size(), 5);
}

TEST(VectorTests, InitializerListConstructor) {
  s21::vector<int> vec = {1, 2, 3, 4};
  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
}

TEST(VectorTests, CopyConstructor) {
  s21::vector<int> vec = {10, 20, 30};
  s21::vector<int> copy(vec);
  EXPECT_EQ(copy.size(), vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(copy[i], vec[i]);
  }
}

TEST(VectorTests, MoveConstructor) {
  s21::vector<int> vec = {5, 6, 7};
  s21::vector<int> moved(std::move(vec));
  EXPECT_EQ(moved.size(), 3);
  EXPECT_EQ(moved[0], 5);
  EXPECT_EQ(vec.size(), 0);
}

TEST(VectorTests, CopyAssignmentOperator) {
  s21::vector<int> vec1 = {1, 2, 3};
  s21::vector<int> vec2;
  vec2 = vec1;
  EXPECT_EQ(vec2.size(), vec1.size());
  for (size_t i = 0; i < vec1.size(); ++i) {
    EXPECT_EQ(vec2[i], vec1[i]);
  }
}

TEST(VectorTests, MoveAssignmentOperator) {
  s21::vector<int> vec1 = {4, 5, 6};
  s21::vector<int> vec2;
  vec2 = std::move(vec1);
  EXPECT_EQ(vec2.size(), 3);
  EXPECT_EQ(vec2[0], 4);
  EXPECT_EQ(vec2[1], 5);
  EXPECT_EQ(vec2[2], 6);
  EXPECT_EQ(vec1.size(), 0);
}

TEST(VectorTests, AtMethod) {
  s21::vector<int> vec = {100, 200, 300};
  EXPECT_EQ(vec.at(1), 200);
  EXPECT_THROW(vec.at(3), std::out_of_range);
}

TEST(VectorTests, FrontAndBack) {
  s21::vector<int> vec = {10, 20, 30};
  EXPECT_EQ(vec.front(), 10);
  EXPECT_EQ(vec.back(), 30);
}

TEST(VectorTests, DataMethod) {
  s21::vector<int> vec = {1, 2, 3};
  EXPECT_NE(vec.data(), nullptr);
  EXPECT_EQ(vec.data(), &vec[0]);
}

TEST(VectorTests, BeginEndIterators) {
  s21::vector<int> vec = {1, 2, 3, 4, 5};
  int sum = 0;
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, 15);
}

TEST(VectorTests, ReserveAndCapacity) {
  s21::vector<int> vec = {1, 2, 3};
  size_t oldCapacity = vec.capacity();
  vec.reserve(oldCapacity + 10);
  EXPECT_GE(vec.capacity(), oldCapacity + 10);
}

TEST(VectorTests, ShrinkToFit) {
  s21::vector<int> vec = {1, 2, 3, 4, 5};
  vec.reserve(100);
  EXPECT_GE(vec.capacity(), 100);
  vec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), vec.size());
}

TEST(VectorTests, Clear) {
  s21::vector<int> vec = {1, 2, 3};
  vec.clear();
  EXPECT_EQ(vec.size(), 0);
  EXPECT_TRUE(vec.empty());
}

TEST(VectorTests, PushBack) {
  s21::vector<int> vec;
  vec.push_back(42);
  EXPECT_EQ(vec.size(), 1);
  EXPECT_EQ(vec[0], 42);
  vec.push_back(100);
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[1], 100);
}

TEST(VectorTests, PopBack) {
  s21::vector<int> vec = {1, 2, 3};
  vec.pop_back();
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec.back(), 2);
  vec.pop_back();
  vec.pop_back();
  EXPECT_THROW(vec.pop_back(), std::out_of_range);
}

TEST(VectorTests, Resize) {
  s21::vector<int> vec = {1, 2, 3};
  vec.resize(5);
  EXPECT_EQ(vec.size(), 5);
  vec.resize(2);
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
}

// Тест erase() для удаления элемента
TEST(VectorTests, Erase) {
  s21::vector<int> vec = {10, 20, 30, 40};
  auto it = vec.begin();
  ++it;  // Указатель на второй элемент (20)
  vec.erase(it);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], 10);
  EXPECT_EQ(vec[1], 30);
  EXPECT_EQ(vec[2], 40);
}

TEST(VectorTests, Insert) {
  s21::vector<int> vec = {1, 2, 4, 5};
  auto it = vec.begin();
  it += 2;
  vec.insert(it, 3);
  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
}

TEST(VectorTests, SwapFunction) {
  s21::vector<int> vec1 = {1, 2, 3};
  s21::vector<int> vec2 = {4, 5};
  vec1.swap(vec2);
  EXPECT_EQ(vec1.size(), 2);
  EXPECT_EQ(vec2.size(), 3);
  EXPECT_EQ(vec1[0], 4);
  EXPECT_EQ(vec2[0], 1);
}

TEST(VectorTests, InsertMany) {
  s21::vector<int> vec = {1, 2, 7, 8};
  auto it = vec.begin();
  it += 2;
  vec.insert_many(it, 3, 4, 5, 6);
  EXPECT_EQ(vec.size(), 8);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
  EXPECT_EQ(vec[5], 6);
  EXPECT_EQ(vec[6], 7);
  EXPECT_EQ(vec[7], 8);
}

TEST(VectorTests, InsertManyBack) {
  s21::vector<int> vec = {1, 2, 3};
  vec.insert_many_back(4, 5, 6);
  EXPECT_EQ(vec.size(), 6);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
  EXPECT_EQ(vec[5], 6);
}
