#ifndef BST_ITERATOR_TPP
#define BST_ITERATOR_TPP

#include "s21_bst_iterator.h"

namespace s21 {

template <typename T>
BST_iterator<T>::BST_iterator(pointer ptr, int index)
    : _ptr(ptr), _index(index) {}

template <typename T>
BST_iterator<T>& BST_iterator<T>::operator++() {
  ++_index;
  return *this;
}

template <typename T>
BST_iterator<T> BST_iterator<T>::operator++(int) {
  BST_iterator tmp = *this;
  ++_index;
  return tmp;
}

template <typename T>
typename BST_iterator<T>::reference BST_iterator<T>::operator*() const {
  return _ptr->get_value_by_index(_index);
}

template <typename T>
typename BST_iterator<T>::pointer BST_iterator<T>::operator->() {
  return _ptr;
}

template <typename T>
bool BST_iterator<T>::operator==(const BST_iterator<T>& other) const {
  return _ptr == other._ptr;
}

template <typename T>
bool BST_iterator<T>::operator!=(const BST_iterator<T>& other) const {
  return !(*this == other);
}

template <typename T>
int BST_iterator<T>::get_index() {
  return _index;
}

}  // namespace s21

#endif