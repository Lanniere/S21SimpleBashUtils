#include <gtest/gtest.h>

#include <queue>

#include "../container/queue/s21_queue.h"

TEST(QueueTest, DefaultConstructor) {
  s21::queue<int> q;
  EXPECT_EQ(q.size(), 0);
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, InitializerListConstructor) {
  s21::queue<int> q({1, 2, 3});
  EXPECT_EQ(q.size(), 3);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, CopyConstructor) {
  s21::queue<int> original({10, 20, 30});
  s21::queue<int> copy(original);
  EXPECT_EQ(copy.size(), 3);
  EXPECT_EQ(copy.front(), 10);
  EXPECT_EQ(copy.back(), 30);
}

TEST(QueueTest, MoveConstructor) {
  s21::queue<int> original({10, 20, 30});
  s21::queue<int> moved(std::move(original));
  EXPECT_EQ(moved.size(), 3);
  EXPECT_EQ(moved.front(), 10);
  EXPECT_EQ(moved.back(), 30);
  EXPECT_TRUE(original.empty());
}

TEST(QueueTest, MoveAssignment) {
  s21::queue<int> source({100, 200, 300});
  s21::queue<int> target;
  target = std::move(source);
  EXPECT_EQ(target.size(), 3);
  EXPECT_EQ(target.front(), 100);
  EXPECT_EQ(target.back(), 300);
  EXPECT_TRUE(source.empty());
}

TEST(QueueTest, Push) {
  s21::queue<int> q;
  q.push(5);
  EXPECT_EQ(q.size(), 1);
  EXPECT_EQ(q.front(), 5);
  EXPECT_EQ(q.back(), 5);
  q.push(15);
  EXPECT_EQ(q.size(), 2);
  EXPECT_EQ(q.front(), 5);
  EXPECT_EQ(q.back(), 15);
}

TEST(QueueTest, Pop) {
  s21::queue<int> q({10, 20, 30});
  q.pop();
  EXPECT_EQ(q.size(), 2);
  EXPECT_EQ(q.front(), 20);
  EXPECT_EQ(q.back(), 30);
  q.pop();
  EXPECT_EQ(q.size(), 1);
  EXPECT_EQ(q.front(), 30);
  EXPECT_EQ(q.back(), 30);
}

TEST(QueueTest, FrontThrowsOnEmpty) {
  s21::queue<int> q;
  EXPECT_THROW(q.front(), std::out_of_range);
}

TEST(QueueTest, BackThrowsOnEmpty) {
  s21::queue<int> q;
  EXPECT_THROW(q.back(), std::out_of_range);
}

TEST(QueueTest, PopThrowsOnEmpty) {
  s21::queue<int> q;
  EXPECT_THROW(q.pop(), std::out_of_range);
}

TEST(QueueTest, Empty) {
  s21::queue<int> q;
  EXPECT_TRUE(q.empty());
  q.push(10);
  EXPECT_FALSE(q.empty());
  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, Swap) {
  s21::queue<int> q1({1, 2, 3});
  s21::queue<int> q2({4, 5});

  q1.swap(q2);

  EXPECT_EQ(q1.size(), 2);
  EXPECT_EQ(q1.front(), 4);
  EXPECT_EQ(q1.back(), 5);

  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

TEST(QueueTest, MultiplePushPop) {
  s21::queue<int> q;
  for (int i = 0; i < 100; i++) {
    q.push(i);
  }
  EXPECT_EQ(q.size(), 100);
  for (int i = 0; i < 50; i++) {
    EXPECT_EQ(q.front(), i);
    q.pop();
  }
  EXPECT_EQ(q.size(), 50);
  for (int i = 50; i < 100; i++) {
    EXPECT_EQ(q.front(), i);
    q.pop();
  }
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, SwapWithEmptyQueue) {
  s21::queue<int> q1({1, 2, 3});
  s21::queue<int> q2;
  q1.swap(q2);
  EXPECT_TRUE(q1.empty());
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

TEST(QueueTest, SelfSwap) {
  s21::queue<int> q({1, 2, 3});
  q.swap(q);
  EXPECT_EQ(q.size(), 3);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, PrintFunction) {
  s21::queue<int> q({10, 20, 30});
  std::streambuf* old_buf = std::cout.rdbuf();
  std::stringstream ss;
  std::cout.rdbuf(ss.rdbuf());
  q.print();
  std::cout.rdbuf(old_buf);
  std::string output = ss.str();
  size_t pos1 = output.find("10");
  size_t pos2 = output.find("20");
  size_t pos3 = output.find("30");
  EXPECT_NE(pos1, std::string::npos);
  EXPECT_NE(pos2, std::string::npos);
  EXPECT_NE(pos3, std::string::npos);
  EXPECT_TRUE(pos1 < pos2 && pos2 < pos3);
}

TEST(QueueTest, InterleavedOperations) {
  s21::queue<int> q;
  q.push(1);
  q.push(2);
  EXPECT_EQ(q.front(), 1);
  q.pop();
  q.push(3);
  EXPECT_EQ(q.front(), 2);
  q.pop();
  EXPECT_EQ(q.front(), 3);
  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, InsertManyBackEmptyQueue) {
  s21::queue<int> q;
  q.insert_many_back(5, 6, 7);

  EXPECT_EQ(q.size(), 3);

  int expected = 5;
  while (!q.empty()) {
    EXPECT_EQ(q.front(), expected);
    q.pop();
    expected++;
  }
}

TEST(QueueTest, InsertManyBackNonEmptyQueue) {
  s21::queue<int> q;
  q.push(1);
  q.insert_many_back(2, 3, 4);

  EXPECT_EQ(q.size(), 4);

  int expected = 1;
  while (!q.empty()) {
    EXPECT_EQ(q.front(), expected++);
    q.pop();
  }
}

TEST(QueueTest, InsertManyBackNoElements) {
  s21::queue<int> q;
  q.push(1);
  q.insert_many_back();
  EXPECT_EQ(q.size(), 1);
  EXPECT_EQ(q.front(), 1);
  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, InsertManyBackSingleElement) {
  s21::queue<int> q;
  q.push(1);
  q.insert_many_back(2);

  EXPECT_EQ(q.size(), 2);

  EXPECT_EQ(q.front(), 1);
  q.pop();
  EXPECT_EQ(q.front(), 2);
  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, InsertManyBackOrderPreservation) {
  s21::queue<int> q;
  q.insert_many_back(1, 2, 3);

  EXPECT_EQ(q.front(), 1);
  q.pop();
  EXPECT_EQ(q.front(), 2);
  q.pop();
  EXPECT_EQ(q.front(), 3);
  q.pop();
}

TEST(QueueTest, InsertManyBackLargeElements) {
  s21::queue<std::string> q;
  q.insert_many_back("hello", "world");

  EXPECT_EQ(q.front(), "hello");
  q.pop();
  EXPECT_EQ(q.front(), "world");
  q.pop();
}