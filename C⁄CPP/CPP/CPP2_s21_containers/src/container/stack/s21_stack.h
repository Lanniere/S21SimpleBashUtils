#ifndef S21_STACK_H
#define S21_STACK_H

#include <initializer_list>
#include <stdexcept>
#include <utility>

#include "../vector/s21_vector.h"

namespace s21 {

template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s) noexcept;

  stack &operator=(stack &&s) noexcept;

  const_reference top() const;

  bool empty() const;
  size_type size() const;

  void push(const_reference value);
  void pop();
  void swap(stack &other);

 private:
  s21::vector<value_type> data;
};

}  // namespace s21

#include "s21_stack.tpp"

#endif
