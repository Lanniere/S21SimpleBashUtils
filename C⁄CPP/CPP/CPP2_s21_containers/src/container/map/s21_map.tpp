#include "s21_map.h"
namespace s21 {

template <class Key, class T>
map<Key, T>::map() : _data(new Red_black_tree<value_type>()), _size(0) {}

template <class Key, class T>
map<Key, T>::map(std::initializer_list<value_type> const& items)
    : _data(new Red_black_tree<value_type>()), _size(0) {
  for (auto& item : items) {
    insert(item);
  }
}

template <class Key, class T>
map<Key, T>::map(const map& m) {
  _data = new Red_black_tree<value_type>();
  *(_data) = *(m._data);
  _size = m._size;
}

template <class Key, class T>
map<Key, T>::map(map&& m) {
  if (this != &m) {
    _data = m._data;
    _size = m._size;
    m._data = nullptr;
    m._size = 0;
  }
}

template <class Key, class T>
map<Key, T>::~map() {
  if (_data) {
    delete _data;
    _data = nullptr;
  }
}

template <class Key, class T>
map<Key, T>& map<Key, T>::operator=(map&& m) {
  if (this != &m) {
    delete _data;
    _data = nullptr;
    _data = m._data;
    _size = m._size;
    m._data = nullptr;
    m._size = 0;
  }
  return *this;
}

template <class Key, class T>
map<Key, T>& map<Key, T>::operator=(const map& m) {
  (*_data) = (*m._data);
  _size = m._size;
  return *this;
}

template <class Key, class T>
typename map<Key, T>::iterator map<Key, T>::begin() {
  return iterator(_data, 0);
}

template <class Key, class T>
typename map<Key, T>::iterator map<Key, T>::end() {
  return iterator(_data, _size - 1);
}

template <class Key, class T>
T& map<Key, T>::at(const Key& key) {
  return _data
      ->get([&key](const_reference val) {
        return key > val.first ? BIGGER : (val.first == key ? EQUAL : LESS);
      })
      .second;
}

template <class Key, class T>
T& map<Key, T>::operator[](const Key& key) {
  return _data
      ->get([&key](const_reference val) {
        return key > val.first ? BIGGER : (val.first == key ? EQUAL : LESS);
      })
      .second;
}

template <class Key, class T>
bool map<Key, T>::empty() {
  return _size == 0;
}

template <class Key, class T>
typename map<Key, T>::size_type map<Key, T>::size() {
  return _size;
}

template <class Key, class T>
typename map<Key, T>::size_type map<Key, T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <class Key, class T>
void map<Key, T>::clear() {
  _data->clear();
  _size = 0;
}

template <class Key, class T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type& value) {
  if (_data->index(value) != -1) {
    throw std::out_of_range("element already exist");
  }
  bool ret = _data->insert(value);
  _size++;
  return std::pair<iterator, bool>(iterator(_data, _data->index(value)), ret);
}

template <class Key, class T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key& key, const T& obj) {
  return insert(std::make_pair(key, obj));
}

template <class Key, class T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key& key, const T& obj) {
  bool ret = false;
  try {
    at(key) = obj;  // тщательно проверить
    ret = true;
  } catch (const std::out_of_range& e) {
    ret = _data->insert(std::make_pair(key, obj));
    _size++;
  }
  return std::pair<iterator, bool>(
      iterator(_data, _data->index(std::make_pair(key, obj))), ret);
}

template <class Key, class T>
void map<Key, T>::erase(iterator pos) {
  _data->del(*pos);
  _size--;
}

template <class Key, class T>
void map<Key, T>::swap(map& other) {
  std::swap(other._data, _data);
  std::swap(_size, other._size);
}

template <class Key, class T>
void map<Key, T>::merge(map& other) {
  int n = other.size();
  for (int i = 0; i < n; i++) {
    value_type var = *(iterator(other._data, i));
    if (_data->index(var) != -1) {
      throw std::out_of_range("element already exist");
    }
    _data->insert(var);
    _size++;
  }
}

template <class Key, class T>
bool map<Key, T>::contains(const Key& key) const {
  return _data->search([&key](const value_type& pair) {
    return pair.first < key ? BIGGER : (pair.first == key ? EQUAL : LESS);
  });
}

template <class Key, class T>
template <typename... Args>
vector<std::pair<typename map<Key, T>::iterator, bool>>
map<Key, T>::insert_many_back(Args&&... args) {
  vector<std::pair<iterator, bool>> tmp;
  tmp.push_back((insert(std::forward<Args>(args)), ...));
  return tmp;
}

};  // namespace s21