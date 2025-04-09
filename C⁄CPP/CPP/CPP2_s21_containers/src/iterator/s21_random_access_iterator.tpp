#ifndef S21_RANDOM_ACCESS_ITERATOR_TPP
#define S21_RANDOM_ACCESS_ITERATOR_TPP

#include "s21_random_access_iterator.h"

namespace s21 {

template <typename T, bool IsConst>
RandomAccessIterator<T, IsConst>::RandomAccessIterator() : ptr_(nullptr) {}

template <typename T, bool IsConst>
RandomAccessIterator<T, IsConst>::RandomAccessIterator(pointer p) : ptr_(p) {}

template <typename T, bool IsConst>
template <bool OtherConst, typename>
RandomAccessIterator<T, IsConst>::RandomAccessIterator(
    const RandomAccessIterator<T, OtherConst>& other)
    : ptr_(other.operator->()) {}
template <typename T, bool IsConst>
typename RandomAccessIterator<T, IsConst>::reference
RandomAccessIterator<T, IsConst>::operator*() const {
  return *ptr_;
}

template <typename T, bool IsConst>
typename RandomAccessIterator<T, IsConst>::pointer
RandomAccessIterator<T, IsConst>::operator->() const {
  return ptr_;
}

template <typename T, bool IsConst>
RandomAccessIterator<T, IsConst>&
RandomAccessIterator<T, IsConst>::operator++() {
  ++ptr_;
  return *this;
}

template <typename T, bool IsConst>
RandomAccessIterator<T, IsConst> RandomAccessIterator<T, IsConst>::operator++(
    int) {
  RandomAccessIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T, bool IsConst>
RandomAccessIterator<T, IsConst>&
RandomAccessIterator<T, IsConst>::operator--() {
  --ptr_;
  return *this;
}

template <typename T, bool IsConst>
RandomAccessIterator<T, IsConst> RandomAccessIterator<T, IsConst>::operator--(
    int) {
  RandomAccessIterator temp = *this;
  --(*this);
  return temp;
}

template <typename T, bool IsConst>
template <bool OtherConst>
bool RandomAccessIterator<T, IsConst>::operator==(
    const RandomAccessIterator<T, OtherConst>& other) const {
  return ptr_ == other.ptr_;
}

template <typename T, bool IsConst>
template <bool OtherConst>
bool RandomAccessIterator<T, IsConst>::operator!=(
    const RandomAccessIterator<T, OtherConst>& other) const {
  return ptr_ != other.ptr_;
}

template <typename T, bool IsConst>
template <bool OtherConst>
bool RandomAccessIterator<T, IsConst>::operator<(
    const RandomAccessIterator<T, OtherConst>& other) const {
  return ptr_ < other.ptr_;
}

template <typename T, bool IsConst>
template <bool OtherConst>
bool RandomAccessIterator<T, IsConst>::operator>(
    const RandomAccessIterator<T, OtherConst>& other) const {
  return ptr_ > other.ptr_;
}

template <typename T, bool IsConst>
template <bool OtherConst>
bool RandomAccessIterator<T, IsConst>::operator<=(
    const RandomAccessIterator<T, OtherConst>& other) const {
  return ptr_ <= other.ptr_;
}

template <typename T, bool IsConst>
template <bool OtherConst>
bool RandomAccessIterator<T, IsConst>::operator>=(
    const RandomAccessIterator<T, OtherConst>& other) const {
  return ptr_ >= other.ptr_;
}

template <typename T, bool IsConst>
RandomAccessIterator<T, IsConst> RandomAccessIterator<T, IsConst>::operator+(
    difference_type n) const {
  return RandomAccessIterator(ptr_ + n);
}

template <typename T, bool IsConst>
RandomAccessIterator<T, IsConst> RandomAccessIterator<T, IsConst>::operator-(
    difference_type n) const {
  return RandomAccessIterator(ptr_ - n);
}

template <typename T, bool IsConst>
template <bool OtherConst>
typename RandomAccessIterator<T, IsConst>::difference_type
RandomAccessIterator<T, IsConst>::operator-(
    const RandomAccessIterator<T, OtherConst>& other) const {
  return ptr_ - other.operator->();
}

template <typename T, bool IsConst>
RandomAccessIterator<T, IsConst>& RandomAccessIterator<T, IsConst>::operator+=(
    difference_type n) {
  ptr_ += n;
  return *this;
}

template <typename T, bool IsConst>
RandomAccessIterator<T, IsConst>& RandomAccessIterator<T, IsConst>::operator-=(
    difference_type n) {
  ptr_ -= n;
  return *this;
}

template <typename T, bool IsConst>
typename RandomAccessIterator<T, IsConst>::reference
RandomAccessIterator<T, IsConst>::operator[](difference_type n) const {
  return *(ptr_ + n);
}

}  // namespace s21

#endif
