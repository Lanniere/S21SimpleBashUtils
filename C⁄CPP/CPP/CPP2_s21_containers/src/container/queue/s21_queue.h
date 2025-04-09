#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <iostream>

#include "../list/s21_list.h"

namespace s21 {

template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &s);
  queue(queue &&s) noexcept;

  queue &operator=(queue &&s) noexcept;

  const_reference front() const;
  const_reference back() const;

  bool empty() const noexcept;
  size_type size() const noexcept;

  void push(const_reference value);
  void pop();
  void swap(queue &other) noexcept;
  void print() const;

  template <class... Args>
  void insert_many_back(Args &&...args);

 private:
  s21::list<value_type> data;
};

}  // namespace s21

#include "s21_queue.tpp"

#endif