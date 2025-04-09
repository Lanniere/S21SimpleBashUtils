#ifndef BST_ITERATOR_H
#define BST_ITERATOR_H

#include "../bst/s21_bst.h"
namespace s21 {

template <typename T>
class BST_iterator {
 public:
  using value_t = Red_black_tree<T>;
  using pointer = value_t*;
  using reference = T&;

  BST_iterator(pointer ptr, int index);

  BST_iterator& operator++();
  BST_iterator operator++(int);

  reference operator*() const;
  pointer operator->();

  bool operator==(const BST_iterator& other) const;
  bool operator!=(const BST_iterator& other) const;

  int get_index();

 private:
  pointer _ptr;
  int _index;
};

}  // namespace s21
#include "s21_bst_iterator.tpp"
#endif