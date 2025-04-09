#ifndef SET_H
#define SET_H

#include "../../bst/s21_bst.h"
#include "../../iterator/s21_bst_iterator.h"
#include "../vector/s21_vector.h"

namespace s21 {
template <class T>
class set {
  using key_type = T;
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = BST_iterator<T>;
  using const_iterator = const iterator;
  using size_type = size_t;

 public:
  set();
  set(std::initializer_list<value_type> const& items);
  set(const set& m);
  set(set&& m);
  ~set();

  set& operator=(set&& m);
  set& operator=(set& m);

  iterator begin() const;
  iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void clear();

  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(set& other);
  void merge(set& other);
  iterator find(const_reference key) const;
  bool contains(const T& key) const;
  void out();

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many_back(Args&&... args);

 private:
  Red_black_tree<T>* data;
  size_type _size;
};

}  // namespace s21

#include "s21_set.tpp"

#endif  // SET_H
