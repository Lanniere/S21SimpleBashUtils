#ifndef BST_TPP
#define BST_TPP
#include "s21_bst.h"
namespace s21 {

template <typename T>
int Red_black_tree<T>::get_w(Node* node) {
  if (node) {
    return node->weight;
  }
  return 0;
}

template <typename T>
void Red_black_tree<T>::set_w(Node* cur) {
  if (cur) cur->weight = get_w(cur->right) + get_w(cur->left) + cur->count;
}

template <typename T>
void Red_black_tree<T>::set_w(Node* cur, int num) {
  if (cur) cur->weight = num;
}

template <typename T>
void Red_black_tree<T>::set_w_parents(Node* node) {
  Node* cur = node->parent;
  while (cur) {
    cur->weight++;
    cur = cur->parent;
  }
}

template <typename T>
void Red_black_tree<T>::fix_del_weight(Node* node) {
  Node* cur = node;
  while (cur) {
    cur->weight--;
    cur = cur->parent;
  }
}

template <typename T>
int Red_black_tree<T>::get_index(Node* node, int num) {
  int index = num;
  if (!node) return -1;
  if (node->left) index += node->left->weight;
  return index;
}

template <typename T>
typename Red_black_tree<T>::Node* Red_black_tree<T>::get_node(T& value) {
  Node* cur = root;
  while (cur) {
    if (value > cur->_data) {
      cur = cur->right;
    } else if (value < cur->_data) {
      cur = cur->left;
    } else {
      return cur;
    }
  }
  return nullptr;
}

template <typename T>
typename Red_black_tree<T>::Node* Red_black_tree<T>::get_max_node(Node* start) {
  Node* tmp = start;
  while (tmp->right) tmp = tmp->right;
  return tmp;
}

template <typename T>
typename Red_black_tree<T>::Node* Red_black_tree<T>::get_min_node(Node* start) {
  Node* tmp = start;
  while (tmp->left) tmp = tmp->left;
  return tmp;
}

template <typename T>
void Red_black_tree<T>::del(Node* value) {
  if (!value) return;
  Node* cur = value;

  if (cur == root && !cur->left && !cur->right) {
    delete root;
    root = nullptr;
    return;
  }

  if (cur->is_red && !cur->left && !cur->right) {
    fix_del_weight(cur->parent);
    if (cur->parent && cur->parent->left == cur) {
      cur->parent->left = nullptr;
    } else if (cur->parent && cur->parent->right == cur) {
      cur->parent->right = nullptr;
    }
    delete cur;
  } else if (cur->left && cur->right) {
    Node* mx = get_max_node(cur->left);
    Node* min = get_min_node(cur->right);
    if (mx->is_red) {
      cur->_data = mx->_data;
      cur->count = mx->count;
      del(mx);
    } else if (min->is_red) {
      cur->_data = min->_data;
      cur->count = min->count;
      del(min);
    } else {
      cur->_data = mx->_data;
      cur->count = mx->count;
      del(mx);
    }
  } else if (!cur->is_red && (cur->left && !cur->right)) {
    cur->_data = cur->left->_data;
    del(cur->left);
  } else if (!cur->is_red && (!cur->left && cur->right)) {
    cur->_data = cur->right->_data;
    del(cur->right);
  } else if (!cur->is_red && !cur->left && !cur->right) {
    bool is_right = false;

    if (cur->parent && cur->parent->left == cur) {
      cur->parent->left = nullptr;
      is_right = false;
    } else if (cur->parent && cur->parent->right == cur) {
      cur->parent->right = nullptr;
      is_right = true;
    }

    Node* tmp = cur->parent;
    fix_del_weight(cur->parent);
    delete cur;

    fix_delete(tmp, is_right);
  } else {
    if (cur->parent && cur->parent->left == cur) {
      cur->parent->left = nullptr;
      if (cur->right) {
        cur->parent->left = cur->right;
        cur->right->parent = cur->parent;
      } else if (cur->left) {
        cur->parent->left = cur->left;
        cur->left->parent = cur->parent;
      }
    } else if (cur->parent && cur->parent->right == cur) {
      cur->parent->right = nullptr;
      if (cur->right) {
        cur->parent->right = cur->right;
        cur->right->parent = cur->parent;
      } else if (cur->left) {
        cur->parent->right = cur->left;
        cur->left->parent = cur->parent;
      }
    }
    fix_del_weight(cur->parent);
    delete cur;
  }
}

template <typename T>
void Red_black_tree<T>::fix_delete(Node* cur, bool is_right_deleted) {
  Node* brother = nullptr;
  if (!cur) return;

  brother = is_right_deleted ? cur->left : cur->right;

  if (!brother) return;

  if (!brother->is_red) {
    if (brother->right && brother->right->is_red) {
      brother->is_red = cur->is_red;
      cur->is_red = false;
      if (brother->left) brother->left->is_red = false;
      if (cur->right)
        rotate_left(cur);
      else
        rotate_right(cur);
    } else if (brother->right && !brother->right->is_red && brother->left &&
               brother->left->is_red) {
      brother->is_red = brother->left->is_red;
      brother->left->is_red = true;
      rotate_right(brother);

      fix_delete(cur, false);
    } else if (!cur->is_red && brother->right && brother->left &&
               !brother->right->is_red && !brother->left->is_red) {
      fix_delete(cur->parent, true);
    } else if (cur->is_red && !brother->is_red && !cur->parent->is_red) {
      cur->is_red = !cur->is_red;
      brother->is_red = !brother->is_red;
    }
  } else {
    cur->is_red = true;
    brother->is_red = false;
    if (cur->left)
      rotate_right(cur);
    else {
      rotate_left(cur);
    }
  }
}

template <typename T>
void Red_black_tree<T>::rotate_left(Node* node) {
  Node* right_child = node->right;
  set_w(right_child, node->weight);
  node->right = right_child->left;
  if (right_child->left != nullptr) {
    right_child->left->parent = node;
  }

  right_child->parent = node->parent;

  if (node->parent == nullptr) {
    root = right_child;
  } else if (node == node->parent->left) {
    node->parent->left = right_child;
  } else {
    node->parent->right = right_child;
  }

  right_child->left = node;
  node->parent = right_child;
  set_w(node->right);
  set_w(node->left);
  set_w(node);
}

template <typename T>
void Red_black_tree<T>::rotate_right(Node* node) {
  Node* left_child = node->left;
  set_w(left_child, node->weight);

  node->left = left_child->right;

  if (left_child->right != nullptr) {
    left_child->right->parent = node;
  }

  left_child->parent = node->parent;

  if (node->parent == nullptr) {
    root = left_child;
  } else if (node == node->parent->right) {
    node->parent->right = left_child;
  } else {
    node->parent->left = left_child;
  }

  left_child->right = node;
  node->parent = left_child;
  set_w(node->right);
  set_w(node->left);
  set_w(node);
}

template <typename T>
void Red_black_tree<T>::fix_insert(Node* node) {
  while (node && node != root && node->parent && node->parent->is_red) {
    Node* uncle = nullptr;

    if (node->parent->parent && node->parent == node->parent->parent->left) {
      uncle = node->parent->parent->right;
    } else if (node->parent->parent &&
               node->parent == node->parent->parent->right) {
      uncle = node->parent->parent->left;
    }
    if (!uncle) uncle = root;

    if (uncle->is_red) {
      node->parent->is_red = false;

      uncle->is_red = false;

      if (node->parent->parent) node->parent->parent->is_red = true;

      node = node->parent->parent;
    } else if (node == node->parent->right && !uncle->is_red) {
      node->parent->parent->is_red = true;
      node->parent->is_red = false;
      if (node->parent->parent->right) {
        rotate_left(node->parent->parent);
      } else {
        rotate_right(node->parent->parent);
      }
    } else if (!uncle->is_red && node->parent->left == node) {
      node->parent->is_red = false;
      node->parent->parent->is_red = true;

      if (node->parent->parent->right) {
        rotate_left(node->parent->parent);
      } else {
        rotate_right(node->parent->parent);
      }
    }

    node = node->parent;
  }
  root->is_red = false;
}

template <typename T>
void Red_black_tree<T>::copy(const Red_black_tree& other) {
  if (root) {
    copy(other, root, other.root);
  }
}

template <typename T>
void Red_black_tree<T>::copy(const Red_black_tree& other, Node* cur,
                             Node* cur_other) {
  if (cur_other) {
    cur = new Node(cur_other->_data);
    copy(other, cur->left, cur_other->left);
    copy(other, cur->right, cur_other->right);
  }
}

template <typename T>
Red_black_tree<T>::Red_black_tree() : root(nullptr) {}

template <typename T>
Red_black_tree<T>::Red_black_tree(Red_black_tree&& other) : root(other.root) {
  other.root = nullptr;
}

template <typename T>
Red_black_tree<T>::Red_black_tree(const Red_black_tree<T>& other) {
  copy(other);
}

template <typename T>
Red_black_tree<T>& Red_black_tree<T>::operator=(
    const Red_black_tree<T>& other) {
  copy(other);
  return *this;
}

template <typename T>
Red_black_tree<T>::Red_black_tree(std::initializer_list<T> const& items)
    : root(nullptr) {
  for (auto& item : items) {
    insert(item);
  }
}

template <typename T>
Red_black_tree<T>::~Red_black_tree() {
  clear();
}

template <typename T>
bool Red_black_tree<T>::insert(T value) {
  if (root == nullptr) {
    root = new Node(value);
    root->weight = 1;
    root->is_red = false;
    return true;
  }

  Node* cur = root;

  while (cur && cur->_data != value) {
    if (cur->_data > value && cur->left) {
      cur = cur->left;
    }
    if (cur->_data < value && cur->right) {
      cur = cur->right;
    }

    if (cur->_data > value && !cur->left) {
      cur->left = new Node(value);
      cur->left->parent = cur;
      cur->left->weight = 1;
      set_w_parents(cur->left);
      if (cur->is_red) fix_insert(cur->left);
      return true;
    }
    if (cur->_data < value && !cur->right) {
      cur->right = new Node(value);
      cur->right->parent = cur;
      cur->right->weight = 1;
      set_w_parents(cur->right);
      if (cur->is_red) {
        fix_insert(cur->right);
      }

      return true;
    }
  }
  if (cur->_data == value) {
    cur->count++;
    cur->weight++;
    set_w_parents(cur);
  }

  return cur->_data != value;
}

template <typename T>
template <typename Predicate>
bool Red_black_tree<T>::search(Predicate pred) const {
  Node* cur = root;
  while (cur != nullptr) {
    if (pred(cur->_data) == EQUAL) {
      return true;
    } else if (pred(cur->_data) == LESS) {
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  return false;
}

template <typename T>
template <typename Predicate>
T& Red_black_tree<T>::get(Predicate pred) const {
  Node* cur = root;
  while (cur != nullptr) {
    if (pred(cur->_data) == EQUAL) {
      return cur->_data;
    } else if (pred(cur->_data) == LESS) {
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  if (cur == nullptr) throw std::out_of_range("no key");
  return cur->_data;
}

template <typename T>
bool Red_black_tree<T>::del(T value) {
  Node* cur = root;
  while (cur) {
    if (cur->_data == value) {
      break;
    } else if (cur->_data > value) {
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  if (!cur) return false;
  if (cur->count < 2)
    del(cur);
  else {
    cur->count--;
    fix_del_weight(cur);
  }
  return true;
}

template <typename T>
void Red_black_tree<T>::out_tree() {
  if (root) out(root);
}

template <typename T>
void Red_black_tree<T>::out(Node* cur) {
  if (cur) {
    std::cout << "cur is : " << cur->_data << " cur_count is: " << cur->count
              << " cur weight is: " << cur->weight
              << " color is red : " << cur->is_red
              << " cur_left is : " << (cur->left ? cur->left->_data : -1)
              << " color is red : " << (cur->left ? cur->left->is_red : -1)
              << " cur_right is : " << (cur->right ? cur->right->_data : -1)
              << " color is red : " << (cur->right ? cur->right->is_red : -1)
              << std::endl;
    out(cur->left);
    out(cur->right);
  }
}

template <typename T>
void Red_black_tree<T>::clear() {
  while (root != nullptr) {
    del(root);
  }
}

template <typename T>
bool Red_black_tree<T>::contains(T value) const {
  Node* cur = root;
  while (cur) {
    if (cur->_data > value) {
      cur = cur->left;
    }
    if (cur->_data < value) {
      cur = cur->right;
    }
  }
  return cur != nullptr;
}

template <typename T>
int Red_black_tree<T>::index(T value) {
  Node* cur = root;

  int ind = 0;
  while (cur) {
    if (value > cur->_data) {
      ind = get_index(cur, ind) + cur->count;
      cur = cur->right;
    } else if (value < cur->_data) {
      cur = cur->left;
    } else {
      return get_index(cur, ind);
    }
  }
  return -1;
}

template <typename T>
T& Red_black_tree<T>::get_value_by_index(int _ind) {
  Node* cur = root;

  int ind = 0;
  int ind_cmp = get_index(cur, ind);
  while (cur) {
    if (_ind > ind_cmp) {
      ind = get_index(cur, ind) + 1;
      cur = cur->right;
      ind_cmp = get_index(cur, ind);
    } else if (_ind < ind_cmp) {
      cur = cur->left;
      ind_cmp = get_index(cur, ind);
    } else {
      return cur->_data;
    }
  }
  throw;
}

template <typename T>
T& Red_black_tree<T>::get_value_by_index_multi(int _ind) {
  if (_ind < 0) throw;
  Node* cur = root;

  int ind = 0;
  int ind_cmp = get_index(cur, ind);
  while (cur) {
    if (_ind > ind_cmp) {
      if (!cur->right ||
          (index(cur->right->_data) > _ind && !cur->right->left) ||
          (index(cur->_data) + cur->count - 1 >= _ind)

      )
        break;
      ind = get_index(cur, ind) + 1;
      cur = cur->right;
      ind_cmp = index(cur->_data);
    } else if (_ind < ind_cmp) {
      if (!cur->left) break;
      cur = cur->left;
      ind_cmp = index(cur->_data);
    } else {
      return cur->_data;
    }
  }
  if (cur && index(cur->_data) + cur->count - 1 >= _ind) {
    return cur->_data;
  }
  throw;
}

template <typename T>
int Red_black_tree<T>::get_count(T key) {
  return get_node(key)->count;
}

template <typename T>
int Red_black_tree<T>::upper_bound(T value) {
  Node* cur_ = root;
  bool contains = false;
  while (cur_) {
    if (value > cur_->_data) {
      cur_ = cur_->right;
    } else if (value < cur_->_data) {
      cur_ = cur_->left;
    } else {
      contains = true;
      break;
    }
  }
  Node* mx = get_max_node(root);
  if (contains && mx == cur_) {
    return index(mx->_data);
  }
  Node* cur = root;
  while (cur) {
    if (value > cur->_data) {
      if (cur->right && cur->right->_data > value) {
        return index(get_min_node(cur->right)->_data);
      }
      if (!cur->right) {
        break;
      }
      cur = cur->right;
    } else if (value < cur->_data) {
      if ((cur->left && cur->left->_data < value) || !(cur->left)) {
        if (cur->left)
          return index((get_max_node(cur->left)->_data >= value
                            ? get_max_node(cur->left)->_data
                            : cur->_data));
        else
          return index(cur->_data);
      }
      cur = cur->left;
    } else if (cur->right) {
      return index(get_min_node(cur->right)->_data);
    } else if (cur->parent && cur->parent->_data > cur->_data) {
      return index(cur->parent->_data);
    } else {
      break;
    }
  }
  return index(get_max_node(root)->_data);
}

template <typename T>
int Red_black_tree<T>::lower_bound(T value) {
  Node* cur = root;
  while (cur) {
    if (value > cur->_data) {
      if (cur->right && cur->right->_data > value) {
        return index(get_min_node(cur->right)->_data);
      }
      if (!cur->right) {
        break;
      }
      cur = cur->right;
    } else if (value < cur->_data) {
      if ((cur->left && cur->left->_data < value) || !(cur->left)) {
        if (cur->left)
          return index((get_max_node(cur->left)->_data >= value
                            ? get_max_node(cur->left)->_data
                            : cur->_data));
        else
          return index(cur->_data);
      }
      cur = cur->left;
    } else {
      return index(cur->_data);
    }
  }
  return index(get_max_node(root)->_data);
}

};  // namespace s21

#endif