#ifndef S21_LIST_H
#define S21_LIST_H

#include <iostream>
#include <limits>

#include "../../iterator/s21_bidirectional_iterator.h"

namespace s21 {

template <typename T>
class list {
 private:
  class Node;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using iterator = BidirectionalIterator<T, Node>;
  using const_iterator = const BidirectionalIterator<T, Node, true>;

  void print() const;
  bool operator==(const list &l) const;

  list();
  explicit list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  ~list();
  list &operator=(list &&l);

  const_reference front() const;
  const_reference back() const;

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty() const noexcept;
  size_type size() const;
  size_type max_size() const;

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <class... Args>
  void insert_many_back(Args &&...args);
  template <class... Args>
  void insert_many_front(Args &&...args);

 private:
  class Node {
   public:
    T data;
    Node *next;
    Node *prev;

    explicit Node(const_reference value);
  };

  Node *head_{nullptr};
  Node *tail_{nullptr};
  size_type size_{0};
};

}  // namespace s21

#include "s21_list.tpp"

#endif  // S21_LIST_H
