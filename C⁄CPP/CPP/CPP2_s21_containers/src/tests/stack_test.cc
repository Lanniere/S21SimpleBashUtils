#include <gtest/gtest.h>

#include <stdexcept>

#include "../container/stack/s21_stack.h"

TEST(StackTests, DefaultConstructor) {
  s21::stack<int> st;
  EXPECT_TRUE(st.empty());
  EXPECT_EQ(st.size(), 0);
}

TEST(StackTests, InitializerListConstructor) {
  s21::stack<int> st = {1, 2, 3, 4};
  EXPECT_FALSE(st.empty());
  EXPECT_EQ(st.size(), 4);
  EXPECT_EQ(st.top(), 4);
}

TEST(StackTests, CopyConstructor) {
  s21::stack<int> st = {10, 20, 30};
  s21::stack<int> st_copy(st);
  EXPECT_EQ(st_copy.size(), st.size());
  EXPECT_EQ(st_copy.top(), st.top());
}

TEST(StackTests, MoveConstructor) {
  s21::stack<int> st = {5, 6, 7};
  s21::stack<int> st_move(std::move(st));
  EXPECT_EQ(st_move.size(), 3);
  EXPECT_EQ(st_move.top(), 7);
  EXPECT_TRUE(st.empty());
}

TEST(StackTests, MoveAssignmentOperator) {
  s21::stack<int> st1 = {1, 2, 3};
  s21::stack<int> st2;
  st2 = std::move(st1);
  EXPECT_EQ(st2.size(), 3);
  EXPECT_EQ(st2.top(), 3);
  EXPECT_TRUE(st1.empty());
}

TEST(StackTests, PushAndTop) {
  s21::stack<int> st;
  st.push(10);
  EXPECT_EQ(st.top(), 10);
  st.push(20);
  EXPECT_EQ(st.top(), 20);
  st.push(30);
  EXPECT_EQ(st.top(), 30);
}

TEST(StackTests, Pop) {
  s21::stack<int> st = {1, 2, 3};
  st.pop();
  EXPECT_EQ(st.size(), 2);
  EXPECT_EQ(st.top(), 2);
  st.pop();
  EXPECT_EQ(st.size(), 1);
  EXPECT_EQ(st.top(), 1);
  st.pop();
  EXPECT_TRUE(st.empty());
  EXPECT_THROW(st.pop(), std::out_of_range);
}

TEST(StackTests, SwapFunction) {
  s21::stack<int> st1 = {1, 2, 3};
  s21::stack<int> st2 = {4, 5};
  st1.swap(st2);
  EXPECT_EQ(st1.size(), 2);
  EXPECT_EQ(st2.size(), 3);
  EXPECT_EQ(st1.top(), 5);
  EXPECT_EQ(st2.top(), 3);
}

TEST(StackTests, SizeAndEmpty) {
  s21::stack<int> st;
  EXPECT_TRUE(st.empty());
  EXPECT_EQ(st.size(), 0);
  st.push(42);
  EXPECT_FALSE(st.empty());
  EXPECT_EQ(st.size(), 1);
}
