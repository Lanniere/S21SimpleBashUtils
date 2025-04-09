#ifndef MULTISET_TPP
#define MULTISET_TPP
#include "s21_multiset.h"

namespace s21 {

template <class T>
multiset<T>::multiset() : size_set(0) {
  data = new Red_black_tree<T>();
}

template <class T>
multiset<T>::multiset(std::initializer_list<value_type> const& items) {
  size_set = 0;
  data = new Red_black_tree<T>();
  for (size_type i = 0; i < items.size(); i++) {
    const value_type temp = *(items.begin() + i);
    insert(temp);
  }
}

template <class T>
multiset<T>::multiset(const multiset& m) : size_set(m.size_set) {
  data = new Red_black_tree<T>();
  *(data) = *(m.data);
}

template <class T>
multiset<T>::multiset(multiset&& m) {
  if (this != &m) {
    data = m.data;
    size_set = m.size_set;
    m.data = nullptr;
    m.size_set = 0;
  }
}

template <class T>
multiset<T>::~multiset() {
  if (data) {
    delete data;
    data = nullptr;
  }
}

template <class T>
multiset<T>& multiset<T>::operator=(multiset&& m) {
  if (this != &m) {
    delete data;
    data = nullptr;
    data = m.data;
    size_set = m.size_set;
    m.data = nullptr;
    m.size_set = 0;
  }
  return *this;
}

template <class T>
multiset<T>& multiset<T>::operator=(multiset& m) {
  data = m.data;
  size_set = m.size_set;
  return *this;
}

template <class T>
typename multiset<T>::iterator multiset<T>::begin() const {
  return iterator(data, 0);
}

template <class T>
typename multiset<T>::iterator multiset<T>::end() const {
  return iterator(data, size_set - 1);
}

template <class T>
bool multiset<T>::empty() const {
  return size_set == 0;
}

template <class T>
typename multiset<T>::size_type multiset<T>::size() const {
  return size_set;
}

template <class T>
typename multiset<T>::size_type multiset<T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <class T>
void multiset<T>::clear() {
  data->clear();
  size_set = 0;
}

template <class T>
std::pair<typename multiset<T>::iterator, bool> multiset<T>::insert(
    const value_type& value) {
  bool ret = data->insert(value);
  size_set++;
  return std::pair<iterator, bool>(iterator(data, data->index(value)), ret);
}

template <class T>
void multiset<T>::erase(iterator pos) {
  data->del(*pos);
  size_set--;
}

template <class T>
void multiset<T>::swap(multiset& other) {
  std::swap(other.data, data);
  std::swap(size_set, other.size_set);
}

template <class T>
void multiset<T>::merge(multiset& other) {
  int n = other.size();
  for (int i = 0; i < n; i++) {
    value_type var = *(iterator(other.data, i));
    data->insert(var);
    size_set++;
  }
}

template <class T>
typename multiset<T>::iterator multiset<T>::find(const_reference key) const {
  int ind = data->index(key);
  if (ind == -1) {
    return end();
  }
  return iterator(data, ind);
}

template <class T>
bool multiset<T>::contains(const T& key) const {
  bool contain = data->search([&key](const_reference val) {
    return key > val ? BIGGER : (val == key ? EQUAL : LESS);
  });
  return contain;
}

template <class T>
void multiset<T>::out() {
  if (data) data->out_tree();
}

template <class T>
typename multiset<T>::size_type multiset<T>::count(const key_type& key) {
  if (data->index(key) == -1) return 0;
  return data->get_count(key);
}

template <class T>
std::pair<typename multiset<T>::iterator, typename multiset<T>::iterator>
multiset<T>::equal_range(const key_type& key) {
  return std::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
}

template <class T>
typename multiset<T>::iterator multiset<T>::lower_bound(const key_type& key) {
  return iterator(data, data->lower_bound(key));
}

template <class T>
typename multiset<T>::iterator multiset<T>::upper_bound(const key_type& key) {
  return iterator(data, data->upper_bound(key));
}

template <class T>
template <typename... Args>
vector<std::pair<typename multiset<T>::iterator, bool>>
multiset<T>::insert_many_back(Args&&... args) {
  vector<std::pair<iterator, bool>> tmp;
  tmp.push_back((insert(std::forward<Args>(args)), ...));
  return tmp;
};

};  // namespace s21

#endif  // MULTISET_TPP
