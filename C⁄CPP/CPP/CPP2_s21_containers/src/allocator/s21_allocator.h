#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef>
#include <new>
#include <stdexcept>

namespace s21 {

template <typename T>
class allocator {
 public:
  using value_type = T;
  using pointer = T*;
  using size_type = std::size_t;
  using const_reference = const T&;

  allocator() noexcept = default;

  pointer allocate(size_type n);

  void construct(pointer p, const_reference val);
  void construct(pointer p);

  void deallocate(pointer ptr, size_type n);

  void destroy(pointer p);

  size_type max_size() const noexcept;
};
}  // namespace s21
#include "s21_allocator.tpp"

#endif
