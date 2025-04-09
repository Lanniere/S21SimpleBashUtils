#ifndef SET_TPP
#define SET_TPP
#include "s21_set.h"
namespace s21 {

template <class T>
set<T>::set() : _size(0) {
  data = new Red_black_tree<T>();
}

template <class T>
set<T>::set(std::initializer_list<value_type> const& items) {
  _size = 0;
  data = new Red_black_tree<T>();
  for (size_type i = 0; i < items.size(); i++) {
    const value_type temp = *(items.begin() + i);
    insert(temp);
  }
}

template <class T>
set<T>::set(const set& m) : _size(m.size()) {
  data = new Red_black_tree<T>();
  *(data) = *(m.data);
}

template <class T>
set<T>::set(set&& m) : _size(m.size()) {
  if (this != &m) {
    data = m.data;
    _size = m._size;
    m.data = nullptr;
    m._size = 0;
  }
}

template <class T>
set<T>::~set() {
  if (data) {
    delete data;
    data = nullptr;
  }
}

template <class T>
set<T>& set<T>::operator=(set&& m) {
  if (this != &m) {
    delete data;
    data = nullptr;
    data = m.data;
    _size = m._size;
    m.data = nullptr;
    m._size = 0;
  }
  return *this;
}

template <class T>
set<T>& set<T>::operator=(set& m) {
  data = m.data;
  _size = m._size;
  return *this;
}

template <class T>
typename set<T>::iterator set<T>::begin() const {
  return iterator(data, 0);
}

template <class T>
typename set<T>::iterator set<T>::end() const {
  return iterator(data, _size - 1);
}

template <class T>
bool set<T>::empty() const {
  return _size == 0;
}

template <class T>
typename set<T>::size_type set<T>::size() const {
  return _size;
}

template <class T>
typename set<T>::size_type set<T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <class T>
void set<T>::clear() {
  data->clear();
  _size = 0;
}

template <class T>
std::pair<typename set<T>::iterator, bool> set<T>::insert(
    const value_type& value) {
  if (data->index(value) != -1) {
    throw std::out_of_range("element already exist");
  }
  bool ret = data->insert(value);
  _size++;
  return std::pair<iterator, bool>(iterator(data, data->index(value)), ret);
}

template <class T>
void set<T>::erase(iterator pos) {
  data->del(*pos);
  _size--;
}

template <class T>
void set<T>::swap(set& other) {
  std::swap(other.data, data);
  std::swap(_size, other._size);
}

template <class T>
void set<T>::merge(set& other) {
  int n = other.size();
  for (int i = 0; i < n; i++) {
    value_type var = *(iterator(other.data, i));
    if (data->index(var) != -1) {
      throw std::out_of_range("element already exist");
    }
    data->insert(var);
    _size++;
  }
}

template <class T>
typename set<T>::iterator set<T>::find(const_reference key) const {
  int ind = data->index(key);
  if (ind == -1) {
    return end();
  }
  return iterator(data, ind);
}

template <class T>
bool set<T>::contains(const T& key) const {
  bool contain = data->search([&key](const_reference val) {
    return key > val ? BIGGER : (val == key ? EQUAL : LESS);
  });
  return contain;
}

template <class T>
void set<T>::out() {
  data->out_tree();
}

template <class T>
template <typename... Args>
vector<std::pair<typename set<T>::iterator, bool>> set<T>::insert_many_back(
    Args&&... args) {
  vector<std::pair<iterator, bool>> tmp;
  tmp.push_back((insert(std::forward<Args>(args)), ...));
  return tmp;
}

}  // namespace s21

#endif  // SET_TPP
