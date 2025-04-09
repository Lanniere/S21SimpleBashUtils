#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>

#include "../../allocator/s21_allocator.h"
#include "../../iterator/s21_random_access_iterator.h"
namespace s21 {

template <typename T, typename Alloc = s21::allocator<T>>
class vector {
 public:
  using value_type = T;
  using allocator_type = Alloc;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = T&;
  using const_reference = const T&;
  using pointer = typename Alloc::pointer;
  using iterator = s21::RandomAccessIterator<T, false>;
  using const_iterator = s21::RandomAccessIterator<T, true>;

  vector();
  explicit vector(size_type n);
  vector(std::initializer_list<value_type> const& items);
  vector(const vector& v);
  vector(vector&& v) noexcept;
  ~vector();

  vector& operator=(const vector& v);
  vector& operator=(vector&& v) noexcept;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  pointer data() noexcept;
  const pointer data() const noexcept;
  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type capacity() const noexcept;
  void reserve(size_type new_cap);
  void shrink_to_fit();
  void clear() noexcept;
  void push_back(const_reference value);
  void pop_back();
  void resize(size_type count);
  void erase(iterator pos);
  iterator insert(iterator pos, const_reference value);
  void swap(vector& other) noexcept;

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);

 private:
  void reallocate(size_type new_cap);
  allocator_type alloc_;
  pointer data_;
  size_type size_;
  size_type capacity_;
};

}  // namespace s21

#include "s21_vector.tpp"

#endif
