#include "s21_queue.h"

namespace s21 {

template <typename T>
queue<T>::queue() = default;

template <typename T>
queue<T>::queue(std::initializer_list<value_type> const &items) : data(items) {}

template <typename T>
queue<T>::queue(const queue &s) : data(s.data) {}

template <typename T>
queue<T>::queue(queue &&s) noexcept : data(std::move(s.data)) {}

template <typename T>
queue<T> &queue<T>::operator=(queue &&s) noexcept {
  if (this != &s) {
    data = std::move(s.data);
  }
  return *this;
}

template <typename T>
typename queue<T>::const_reference queue<T>::front() const {
  if (data.empty()) {
    throw std::out_of_range("queue is empty");
  }
  return data.front();
}

template <typename T>
typename queue<T>::const_reference queue<T>::back() const {
  if (data.empty()) {
    throw std::out_of_range("queue is empty");
  }
  return data.back();
}

template <typename T>
bool queue<T>::empty() const noexcept {
  return data.empty();
}

template <typename T>
typename queue<T>::size_type queue<T>::size() const noexcept {
  return data.size();
}

template <typename T>
void queue<T>::push(const_reference value) {
  data.push_back(value);
}

template <typename T>
void queue<T>::pop() {
  if (data.empty()) {
    throw std::out_of_range("queue is empty");
  }
  data.pop_front();
}

template <typename T>
void queue<T>::swap(queue &other) noexcept {
  data.swap(other.data);
}

template <typename T>
template <class... Args>
void s21::queue<T>::insert_many_back(Args &&...args) {
  ((push(std::forward<Args>(args))), ...);
}

template <typename T>
void queue<T>::print() const {
  if (data.empty()) {
    std::cout << "Queue is empty\n";
    return;
  }
  for (auto it = data.cbegin(); it != data.cend(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

}  // namespace s21