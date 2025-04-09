#ifndef S21_ARRAY_TPP
#define S21_ARRAY_TPP

#include <stdexcept>
#include <utility>

#include "s21_array.h"

namespace s21 {

template <typename T, std::size_t N, typename Alloc>
array<T, N, Alloc>::array() : size_(N) {
  data_ = alloc_.allocate(N);
  for (size_type i = 0; i < N; ++i) {
    alloc_.construct(data_ + i);
  }
}

template <typename T, std::size_t N, typename Alloc>
array<T, N, Alloc>::array(std::initializer_list<value_type> const &items)
    : size_(N) {
  data_ = alloc_.allocate(N);
  size_type i = 0;
  for (auto it = items.begin(); it != items.end() && i < N; ++it, ++i) {
    alloc_.construct(data_ + i, *it);
  }
  for (; i < N; ++i) {
    alloc_.construct(data_ + i);
  }
}

template <typename T, std::size_t N, typename Alloc>
array<T, N, Alloc>::array(const array &a) : size_(N) {
  data_ = alloc_.allocate(N);
  for (size_type i = 0; i < N; ++i) {
    alloc_.construct(data_ + i, a.data_[i]);
  }
}

template <typename T, std::size_t N, typename Alloc>
array<T, N, Alloc>::array(array &&a) noexcept
    : data_(a.data_), size_(a.size_), alloc_(std::move(a.alloc_)) {
  a.data_ = nullptr;
  a.size_ = 0;
}

template <typename T, std::size_t N, typename Alloc>
array<T, N, Alloc>::~array() noexcept {
  if (data_) {
    for (size_type i = 0; i < size_; ++i) {
      alloc_.destroy(data_ + i);
    }
    alloc_.deallocate(data_, size_);
  }
}

template <typename T, std::size_t N, typename Alloc>
array<T, N, Alloc> &array<T, N, Alloc>::operator=(array &&a) noexcept {
  if (this != &a) {
    for (size_type i = 0; i < size_; ++i) {
      alloc_.destroy(data_ + i);
    }
    alloc_.deallocate(data_, size_);
    data_ = a.data_;
    size_ = a.size_;
    alloc_ = std::move(a.alloc_);
    a.data_ = nullptr;
    a.size_ = 0;
  }
  return *this;
}

template <typename T, std::size_t N, typename Alloc>
typename array<T, N, Alloc>::reference array<T, N, Alloc>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("array index out of range");
  }
  return data_[pos];
}

template <typename T, std::size_t N, typename Alloc>
typename array<T, N, Alloc>::reference array<T, N, Alloc>::operator[](
    size_type pos) {
  return data_[pos];
}

template <typename T, std::size_t N, typename Alloc>
typename array<T, N, Alloc>::const_reference array<T, N, Alloc>::front() const {
  return data_[0];
}

template <typename T, std::size_t N, typename Alloc>
typename array<T, N, Alloc>::const_reference array<T, N, Alloc>::back() const {
  return data_[size_ - 1];
}

template <typename T, std::size_t N, typename Alloc>
typename array<T, N, Alloc>::iterator array<T, N, Alloc>::data() noexcept {
  return iterator(data_);
}

template <typename T, std::size_t N, typename Alloc>
typename array<T, N, Alloc>::iterator array<T, N, Alloc>::begin() noexcept {
  return iterator(data_);
}

template <typename T, std::size_t N, typename Alloc>
typename array<T, N, Alloc>::iterator array<T, N, Alloc>::end() noexcept {
  return iterator(data_ + size_);
}

template <typename T, std::size_t N, typename Alloc>
bool array<T, N, Alloc>::empty() const noexcept {
  return size_ == 0;
}

template <typename T, std::size_t N, typename Alloc>
typename array<T, N, Alloc>::size_type array<T, N, Alloc>::size()
    const noexcept {
  return size_;
}

template <typename T, std::size_t N, typename Alloc>
typename array<T, N, Alloc>::size_type array<T, N, Alloc>::max_size()
    const noexcept {
  return N;
}

template <typename T, std::size_t N, typename Alloc>
void array<T, N, Alloc>::swap(array &other) noexcept {
  for (size_type i = 0; i < size_; ++i) {
    std::swap(data_[i], other.data_[i]);
  }
}

template <typename T, std::size_t N, typename Alloc>
void array<T, N, Alloc>::fill(const_reference value) {
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = value;
  }
}

}  // namespace s21

#endif
