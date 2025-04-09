#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <initializer_list>

#include "../../allocator/s21_allocator.h"
#include "../../iterator/s21_random_access_iterator.h"

namespace s21 {
template <typename T, std::size_t N, typename Alloc = s21::allocator<T>>
class array {
 public:
  using value_type = T;
  using allocator_type = Alloc;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = T &;
  using const_reference = const T &;
  using pointer = typename Alloc::pointer;
  using iterator = s21::RandomAccessIterator<T, false>;
  using const_iterator = s21::RandomAccessIterator<T, true>;

  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a) noexcept;
  ~array() noexcept;
  array<T, N, Alloc> &operator=(array &&a) noexcept;

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  iterator data() noexcept;

  iterator begin() noexcept;
  iterator end() noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void swap(array &other) noexcept;
  void fill(const_reference value);

 private:
  pointer data_;
  size_type size_;
  Alloc alloc_;
};
}  // namespace s21
#include "s21_array.tpp"
#endif