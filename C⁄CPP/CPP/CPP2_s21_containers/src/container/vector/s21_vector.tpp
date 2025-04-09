#include "s21_vector.h"

namespace s21 {

template <typename T, typename Alloc>
vector<T, Alloc>::vector() : data_(nullptr), size_(0), capacity_(0) {}

template <typename T, typename Alloc>
vector<T, Alloc>::vector(size_type n) : size_(n), capacity_(n) {
  data_ = alloc_.allocate(capacity_);
  for (size_type i = 0; i < size_; ++i) {
    alloc_.construct(data_ + i);
  }
}
template <typename T, typename Alloc>
vector<T, Alloc>::vector(std::initializer_list<value_type> const &items)
    : size_(items.size()), capacity_(items.size()) {
  data_ = alloc_.allocate(capacity_);
  size_type i = 0;
  for (const auto &val : items) {
    alloc_.construct(data_ + i, val);
    ++i;
  }
}

template <typename T, typename Alloc>
vector<T, Alloc>::vector(const vector &v)
    : size_(v.size_), capacity_(v.capacity_) {
  data_ = alloc_.allocate(capacity_);
  for (size_type i = 0; i < size_; ++i) {
    alloc_.construct(data_ + i, v.data_[i]);
  }
}

template <typename T, typename Alloc>
vector<T, Alloc>::vector(vector &&v) noexcept
    : data_(v.data_), size_(v.size_), capacity_(v.capacity_) {
  v.data_ = nullptr;
  v.size_ = v.capacity_ = 0;
}

template <typename T, typename Alloc>
vector<T, Alloc>::~vector() {
  clear();
  if (data_ != nullptr) {
    alloc_.deallocate(data_, capacity_);
  }
}

template <typename T, typename Alloc>
vector<T, Alloc> &vector<T, Alloc>::operator=(const vector &v) {
  if (this != &v) {
    clear();
    if (capacity_ < v.size_) {
      if (data_ != nullptr) {
        alloc_.deallocate(data_, capacity_);
      }
      capacity_ = v.capacity_;
      data_ = alloc_.allocate(capacity_);
    }
    size_ = v.size_;
    for (size_type i = 0; i < size_; ++i) {
      alloc_.construct(data_ + i, v.data_[i]);
    }
  }
  return *this;
}

template <typename T, typename Alloc>
vector<T, Alloc> &vector<T, Alloc>::operator=(vector &&v) noexcept {
  if (this != &v) {
    clear();
    if (data_ != nullptr) {
      alloc_.deallocate(data_, capacity_);
    }
    data_ = v.data_;
    size_ = v.size_;
    capacity_ = v.capacity_;
    v.data_ = nullptr;
    v.size_ = v.capacity_ = 0;
  }
  return *this;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](
    size_type pos) {
  return data_[pos];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[](
    size_type pos) const {
  return data_[pos];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("out of range");
  }
  return data_[pos];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(
    size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("out of range");
  }
  return data_[pos];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::front() {
  return data_[0];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::front() const {
  return data_[0];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::back() {
  return data_[size_ - 1];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() const {
  return data_[size_ - 1];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::pointer vector<T, Alloc>::data() noexcept {
  return data_;
}

template <typename T, typename Alloc>
const typename vector<T, Alloc>::pointer vector<T, Alloc>::data()
    const noexcept {
  return data_;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::begin() noexcept {
  return iterator(data_);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin()
    const noexcept {
  return const_iterator(data_);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::end() noexcept {
  return iterator(data_ + size_);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end()
    const noexcept {
  return const_iterator(data_ + size_);
}

template <typename T, typename Alloc>
bool vector<T, Alloc>::empty() const noexcept {
  return size_ == 0;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::size() const noexcept {
  return size_;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity()
    const noexcept {
  return capacity_;
}

template <typename T, typename Alloc>
void vector<T, Alloc>::reserve(size_type new_cap) {
  if (new_cap > capacity_) {
    reallocate(new_cap);
  }
}

template <typename T, typename Alloc>
void vector<T, Alloc>::shrink_to_fit() {
  if (capacity_ > size_) {
    reallocate(size_);
  }
}

template <typename T, typename Alloc>
void vector<T, Alloc>::clear() noexcept {
  for (size_type i = 0; i < size_; ++i) {
    alloc_.destroy(data_ + i);
  }
  size_ = 0;
}

template <typename T, typename Alloc>
void vector<T, Alloc>::push_back(const_reference value) {
  if (size_ == capacity_) {
    reserve(capacity_ > 0 ? capacity_ * 2 : 1);
  }
  alloc_.construct(data_ + size_, value);
  ++size_;
}

template <typename T, typename Alloc>
void vector<T, Alloc>::pop_back() {
  if (size_ <= 0) {
    throw std::out_of_range("empty vector");
  }
  --size_;
  alloc_.destroy(data_ + size_);
}

template <typename T, typename Alloc>
void vector<T, Alloc>::resize(size_type count) {
  if (count > size_) {
    reserve(count);
    for (size_type i = size_; i < count; ++i) {
      alloc_.construct(data_ + i);
    }
  } else if (count < size_) {
    for (size_type i = count; i < size_; ++i) {
      alloc_.destroy(data_ + i);
    }
  }
  size_ = count;
}

template <typename T, typename Alloc>
void vector<T, Alloc>::erase(iterator pos) {
  if (pos < begin() || pos >= end()) {
    throw std::out_of_range("out of range");
  }
  size_type index = pos - begin();

  for (size_type i = index; i < size_ - 1; ++i) {
    data_[i] = std::move(data_[i + 1]);
  }

  --size_;
  alloc_.destroy(data_ + size_);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(
    iterator pos, const_reference value) {
  size_type index = pos - begin();
  if (index > size_) {
    throw std::out_of_range("out of range");
  }

  if (size_ == capacity_) {
    size_type new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
    reallocate(new_capacity);
  }

  for (size_type i = size_; i > index; --i) {
    alloc_.construct(data_ + i, std::move(data_[i - 1]));
    alloc_.destroy(data_ + i - 1);
  }

  alloc_.construct(data_ + index, value);
  ++size_;
  return iterator(data_ + index);
}

template <typename T, typename Alloc>
void vector<T, Alloc>::swap(vector &other) noexcept {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename T, typename Alloc>
void vector<T, Alloc>::reallocate(size_type new_cap) {
  pointer new_data = alloc_.allocate(new_cap);
  size_type old_size = size_;

  for (size_type i = 0; i < size_; ++i) {
    alloc_.construct(new_data + i, std::move(data_[i]));
  }

  clear();
  if (data_) {
    alloc_.deallocate(data_, capacity_);
  }

  data_ = new_data;
  size_ = old_size;
  capacity_ = new_cap;
}

template <typename T, typename Alloc>
template <typename... Args>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert_many(
    const_iterator pos, Args &&...args) {
  size_type index = pos - begin();
  size_type count = sizeof...(args);
  if (index > size_) {
    throw std::out_of_range("out of range");
  }

  if (size_ + count > capacity_) {
    size_type new_capacity = capacity_ == 0 ? count : capacity_;
    while (new_capacity < size_ + count) {
      new_capacity *= 2;
    }
    reallocate(new_capacity);
  }

  for (size_type i = size_; i > index; --i) {
    alloc_.construct(data_ + i + count - 1, std::move(data_[i - 1]));
    alloc_.destroy(data_ + i - 1);
  }

  size_type curr = index;
  ((alloc_.construct(data_ + curr++, std::forward<Args>(args))), ...);

  size_ += count;
  return iterator(data_ + index);
}

template <typename T, typename Alloc>
template <typename... Args>
void vector<T, Alloc>::insert_many_back(Args &&...args) {
  (push_back(std::forward<Args>(args)), ...);
}

}  // namespace s21