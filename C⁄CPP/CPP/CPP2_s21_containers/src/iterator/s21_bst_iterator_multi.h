#ifndef BST_ITERATOR_MULTI_H
#define BST_ITERATOR_MULTI_H

#include "../bst/s21_bst.h"

namespace s21 {

template <typename T>
class BST_iterator_multi {
 public:
  using value_t = Red_black_tree<T>;
  using pointer = value_t*;
  using reference = T&;

  BST_iterator_multi(pointer ptr, int index);

  BST_iterator_multi& operator++();
  BST_iterator_multi operator++(int);

  reference operator*() const;
  pointer operator->();

  bool operator==(const BST_iterator_multi& other) const;
  bool operator!=(const BST_iterator_multi& other) const;

  int get_index();

 private:
  pointer _ptr;
  int _index;
};

}  // namespace s21

#include "s21_bst_iterator_multi.tpp"
#endif  // BST_ITERATOR_MULTI_H
