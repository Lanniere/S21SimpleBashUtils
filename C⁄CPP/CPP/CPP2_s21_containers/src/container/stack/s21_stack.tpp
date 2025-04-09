#ifndef S21_STACK_TPP
#define S21_STACK_TPP

#include "s21_stack.h"

namespace s21 {

template <typename T>
stack<T>::stack() : data() {}

template <typename T>
stack<T>::stack(std::initializer_list<value_type> const& items) : data(items) {}

template <typename T>
stack<T>::stack(const stack<T>& s) : data(s.data) {}

template <typename T>
stack<T>::stack(stack<T>&& s) noexcept : data(std::move(s.data)) {}

template <typename T>
stack<T>& stack<T>::operator=(stack<T>&& s) noexcept {
  if (this != &s) {
    data = std::move(s.data);
  }
  return *this;
}

template <typename T>
typename stack<T>::const_reference stack<T>::top() const {
  if (data.empty()) {
    throw std::out_of_range("stack is empty");
  }
  return data.back();
}

template <typename T>
bool stack<T>::empty() const {
  return data.empty();
}

template <typename T>
typename stack<T>::size_type stack<T>::size() const {
  return data.size();
}

template <typename T>
void stack<T>::push(const_reference value) {
  data.push_back(value);
}

template <typename T>
void stack<T>::pop() {
  if (data.empty()) {
    throw std::out_of_range("stack is empty");
  }
  data.pop_back();
}

template <typename T>
void stack<T>::swap(stack<T>& other) {
  data.swap(other.data);
}

}  // namespace s21

#endif
