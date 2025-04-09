#ifndef BST_ITERATOR_MULTI_TPP
#define BST_ITERATOR_MULTI_TPP

#include "s21_bst_iterator_multi.h"

namespace s21 {

template <typename T>
BST_iterator_multi<T>::BST_iterator_multi(pointer ptr, int index)
    : _ptr(ptr), _index(index) {}

template <typename T>
BST_iterator_multi<T>& BST_iterator_multi<T>::operator++() {
  ++_index;
  return *this;
}

template <typename T>
BST_iterator_multi<T> BST_iterator_multi<T>::operator++(int) {
  BST_iterator_multi tmp = *this;
  ++_index;
  return tmp;
}

template <typename T>
typename BST_iterator_multi<T>::reference BST_iterator_multi<T>::operator*()
    const {
  return _ptr->get_value_by_index_multi(_index);
}

template <typename T>
typename BST_iterator_multi<T>::pointer BST_iterator_multi<T>::operator->() {
  return _ptr;
}

template <typename T>
bool BST_iterator_multi<T>::operator==(
    const BST_iterator_multi<T>& other) const {
  return _ptr == other._ptr;
}

template <typename T>
bool BST_iterator_multi<T>::operator!=(
    const BST_iterator_multi<T>& other) const {
  return !(*this == other);
}

template <typename T>
int BST_iterator_multi<T>::get_index() {
  return _index;
}

}  // namespace s21

#endif