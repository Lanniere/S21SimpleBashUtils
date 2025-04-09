#ifndef BST_H
#define BST_H
#include <exception>
#include <iostream>

namespace s21 {
enum CMP_e { LESS, EQUAL, BIGGER };

template <typename T>
class Red_black_tree {
 private:
  class Node {
   public:
    T _data;
    Node* left;
    Node* right;
    Node* parent;
    bool is_red;
    int weight;  // for indexing
    int count;   // for multiset

    Node(T data)
        : _data(data),
          left(nullptr),
          right(nullptr),
          parent(nullptr),
          is_red(true),
          weight(1),
          count(1) {};
  };

  Node* root;

  int get_w(Node* node);
  void set_w(Node* cur);
  void set_w(Node* cur, int num);
  void set_w_parents(Node* node);
  void fix_del_weight(Node* node);
  int get_index(Node* node, int num);
  Node* get_node(T& value);
  Node* get_max_node(Node* start);
  Node* get_min_node(Node* start);
  void del(Node* value);
  void fix_delete(Node* cur, bool is_right_deleted);
  void rotate_left(Node* node);
  void rotate_right(Node* node);
  void fix_insert(Node* node);
  void copy(const Red_black_tree& other);
  void copy(const Red_black_tree& other, Node* cur, Node* cur_other);

 public:
  Red_black_tree();
  Red_black_tree(Red_black_tree&& other);
  Red_black_tree(const Red_black_tree<T>& other);
  Red_black_tree<T>& operator=(const Red_black_tree<T>& other);
  Red_black_tree(std::initializer_list<T> const& items);
  ~Red_black_tree();
  bool insert(T value);
  template <typename Predicate>
  bool search(Predicate pred) const;
  template <typename Predicate>
  T& get(Predicate pred) const;
  bool del(T value);
  void out_tree();
  void out(Node* cur);
  void clear();
  bool contains(T value) const;
  int index(T value);
  T& get_value_by_index(int _ind);
  T& get_value_by_index_multi(int _ind);
  int get_count(T key);
  int upper_bound(T value);
  int lower_bound(T value);
};
};  // namespace s21

#include "s21_bst.tpp"

#endif