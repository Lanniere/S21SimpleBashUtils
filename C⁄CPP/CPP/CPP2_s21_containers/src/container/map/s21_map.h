#ifndef MAP_H
#define MAP_H

#include "../../bst/s21_bst.h"
#include "../../iterator/s21_bst_iterator.h"
#include "../vector/s21_vector.h"

namespace s21 {

template <class Key, class T>
class map {
 public:
  // Типы
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;

  // Итераторы
  using iterator = BST_iterator<value_type>;
  using const_iterator = const iterator;

  // Конструкторы и деструкторы
  map();
  map(std::initializer_list<value_type> const& items);
  map(const map& m);
  map(map&& m);
  ~map();

  // Операторы присваивания
  map& operator=(map&& m);
  map& operator=(const map& m);

  // Итераторы
  iterator begin();
  iterator end();

  // Доступ к элементам
  T& at(const Key& key);
  T& operator[](const Key& key);

  // Вместимость
  bool empty();
  size_type size();
  size_type max_size();

  // Модификаторы
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);

  // Поиск
  bool contains(const Key& key) const;

  // Вставка нескольких элементов
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many_back(Args&&... args);

 private:
  Red_black_tree<value_type>* _data;
  size_type _size;
};

}  // namespace s21

#include "s21_map.tpp"

#endif