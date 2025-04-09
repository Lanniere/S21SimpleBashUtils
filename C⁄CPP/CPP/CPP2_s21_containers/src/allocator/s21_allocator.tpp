#include "s21_allocator.h"

namespace s21 {

template <typename T>
typename allocator<T>::pointer allocator<T>::allocate(size_type n) {
  if (n > max_size()) {
    throw std::bad_array_new_length();
  }
  pointer ptr = static_cast<pointer>(::operator new(sizeof(T) * n));
  return ptr;
}
template <typename T>
void allocator<T>::construct(pointer p, const_reference val) {
  ::new (static_cast<void*>(p)) T(val);
}
template <typename T>
void allocator<T>::construct(pointer p) {
  ::new (static_cast<void*>(p)) T();
}
template <typename T>
void allocator<T>::deallocate(pointer ptr, size_type n) {
  ::operator delete(ptr, sizeof(T) * n);
}
template <typename T>
void allocator<T>::destroy(pointer p) {
  p->~T();
}
template <typename T>
typename allocator<T>::size_type allocator<T>::max_size() const noexcept {
  return static_cast<size_type>(-1) / sizeof(T);
}
}  // namespace s21
