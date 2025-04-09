#ifndef MULTISET_H
#define MULTISET_H

#include "../../bst/s21_bst.h"
#include "../../iterator/s21_bst_iterator_multi.h"
#include "../vector/s21_vector.h"

namespace s21 {
template <class T>
class multiset {
  using key_type = T;
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = BST_iterator_multi<T>;
  using const_iterator = const iterator;
  using size_type = size_t;

 public:
  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& m);
  multiset(multiset&& m);
  ~multiset();

  multiset& operator=(multiset&& m);
  multiset& operator=(multiset& m);

  iterator begin() const;
  iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void clear();

  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(multiset& other);
  void merge(multiset& other);
  iterator find(const_reference key) const;
  bool contains(const T& key) const;
  void out();
  size_type count(const key_type& key);
  std::pair<iterator, iterator> equal_range(const key_type& key);
  iterator lower_bound(const key_type& key);
  iterator upper_bound(const key_type& key);

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many_back(Args&&... args);

 private:
  Red_black_tree<T>* data;
  size_type size_set;
};

}  // namespace s21

#include "s21_multiset.tpp"

#endif  // MULTISET_H
