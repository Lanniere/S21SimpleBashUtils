#include "s21_list.h"

namespace s21 {

template <typename T>
list<T>::list() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
list<T>::list(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
  for (size_type i = 0; i < n; ++i) {
    push_back(T());
  }
}

template <typename T>
list<T>::list(std::initializer_list<T> const& items)
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (const T& item : items) {
    push_back(item);
  }
}

template <typename T>
list<T>::list(const list& l) : head_(nullptr), tail_(nullptr), size_(0) {
  Node* current = l.head_;
  while (current) {
    push_back(current->data);
    current = current->next;
  }
}

template <typename T>
list<T>::list(list&& l) : head_(l.head_), tail_(l.tail_), size_(l.size_) {
  l.head_ = nullptr;
  l.tail_ = nullptr;
  l.size_ = 0;
}

template <typename T>
list<T>::~list() {
  clear();
}

template <typename T>
list<T>& list<T>::operator=(list&& l) {
  if (this != &l) {
    clear();
    head_ = l.head_;
    tail_ = l.tail_;
    size_ = l.size_;
    l.head_ = nullptr;
    l.tail_ = nullptr;
    l.size_ = 0;
  }
  return *this;
}

template <typename T>
typename list<T>::const_reference list<T>::front() const {
  return head_->data;
}

template <typename T>
typename list<T>::const_reference list<T>::back() const {
  return tail_->data;
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  return empty() ? iterator(nullptr) : iterator(head_);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator(nullptr);
}

template <typename T>
typename list<T>::const_iterator list<T>::cbegin() const {
  return empty() ? const_iterator(nullptr) : const_iterator(head_);
}

template <typename T>
typename list<T>::const_iterator list<T>::cend() const {
  return const_iterator(nullptr);
}

template <typename T>
bool list<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T>
typename list<T>::size_type list<T>::size() const {
  return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const {
  return std::numeric_limits<size_type>::max();
}

template <typename T>
void list<T>::clear() {
  while (!empty()) {
    pop_back();
  }
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::insert(iterator pos,
                                                     const_reference value) {
  Node* newNode = new Node(value);
  Node* posNode = pos.operator->();

  if (posNode == nullptr) {
    newNode->prev = tail_;
    newNode->next = nullptr;
    if (tail_ != nullptr) {
      tail_->next = newNode;
    } else {
      head_ = newNode;
    }
    tail_ = newNode;
  } else {
    newNode->next = posNode;
    newNode->prev = posNode->prev;
    if (posNode->prev != nullptr)
      posNode->prev->next = newNode;
    else
      head_ = newNode;
    posNode->prev = newNode;
  }
  ++size_;
  return iterator(newNode);
}

template <typename T>
void s21::list<T>::erase(iterator pos) {
  Node* node = pos.operator->();
  if (node == nullptr) return;

  if (node->prev != nullptr)
    node->prev->next = node->next;
  else
    head_ = node->next;

  if (node->next != nullptr)
    node->next->prev = node->prev;
  else
    tail_ = node->prev;

  delete node;
  --size_;
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Node* new_node = new Node(value);
  if (!head_) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    tail_->next = new_node;
    new_node->prev = tail_;
    tail_ = new_node;
  }
  ++size_;
}

template <typename T>
void list<T>::pop_back() {
  if (empty()) {
    std::cerr << "list is empty" << std::endl;
  } else {
    if (size_ == 1) {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
    } else {
      Node* prev = tail_->prev;
      delete tail_;
      tail_ = prev;
      tail_->next = nullptr;
    }
    --size_;
  }
}

template <typename T>
void list<T>::push_front(const_reference value) {
  Node* new_node = new Node(value);
  if (!head_) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    new_node->next = head_;
    head_->prev = new_node;
    head_ = new_node;
  }
  ++size_;
}

template <typename T>
void list<T>::pop_front() {
  if (empty()) {
    std::cerr << "list is empty" << std::endl;
  } else {
    if (size_ == 1) {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
    } else {
      Node* next = head_->next;
      delete head_;
      head_ = next;
      head_->prev = nullptr;
    }
    --size_;
  }
}

template <typename T>
void list<T>::swap(list& other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template <typename T>
void s21::list<T>::merge(list<T>& other) {
  if (this == &other) return;

  Node* ptr1 = head_;
  Node* ptr2 = other.head_;
  Node* newHead = nullptr;
  Node* newTail = nullptr;

  while (ptr1 != nullptr && ptr2 != nullptr) {
    Node* chosen = nullptr;
    if (ptr2->data < ptr1->data) {
      chosen = ptr2;
      ptr2 = ptr2->next;
    } else {
      chosen = ptr1;
      ptr1 = ptr1->next;
    }
    chosen->prev = newTail;
    chosen->next = nullptr;
    if (newTail != nullptr)
      newTail->next = chosen;
    else
      newHead = chosen;
    newTail = chosen;
  }

  while (ptr1 != nullptr) {
    Node* next = ptr1->next;
    ptr1->prev = newTail;
    ptr1->next = nullptr;
    if (newTail != nullptr)
      newTail->next = ptr1;
    else
      newHead = ptr1;
    newTail = ptr1;
    ptr1 = next;
  }

  while (ptr2 != nullptr) {
    Node* next = ptr2->next;
    ptr2->prev = newTail;
    ptr2->next = nullptr;
    if (newTail != nullptr)
      newTail->next = ptr2;
    else
      newHead = ptr2;
    newTail = ptr2;
    ptr2 = next;
  }

  head_ = newHead;
  tail_ = newTail;
  size_ = size_ + other.size_;

  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename T>
void s21::list<T>::splice(const_iterator pos, list<T>& other) {
  if (this == &other || other.empty()) return;

  Node* posNode = const_cast<Node*>(pos.operator->());

  if (posNode == nullptr) {
    if (empty()) {
      head_ = other.head_;
      tail_ = other.tail_;
    } else {
      tail_->next = other.head_;
      other.head_->prev = tail_;
      tail_ = other.tail_;
    }
  } else {
    Node* prevNode = posNode->prev;
    if (prevNode) {
      prevNode->next = other.head_;
      other.head_->prev = prevNode;
    } else {
      head_ = other.head_;
    }
    posNode->prev = other.tail_;
    other.tail_->next = posNode;
  }

  size_ += other.size_;
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename T>
void list<T>::reverse() {
  Node* current = head_;
  Node* temp = nullptr;
  while (current) {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev;
  }
  temp = head_;
  head_ = tail_;
  tail_ = temp;
}

template <typename T>
void list<T>::unique() {
  if (empty() || !head_->next) return;
  Node* current = head_;
  while (current && current->next) {
    if (current->data == current->next->data) {
      Node* node_to_remove = current->next;
      current->next = node_to_remove->next;
      if (node_to_remove->next) {
        node_to_remove->next->prev = current;
      } else {
        tail_ = current;
      }
      delete node_to_remove;
      --size_;
    } else {
      current = current->next;
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (size_ < 2) return;
  bool swapped;
  do {
    swapped = false;
    Node* current = head_;
    while (current->next != nullptr) {
      if (current->data > current->next->data) {
        std::swap(current->data, current->next->data);
        swapped = true;
      }
      current = current->next;
    }
  } while (swapped);
}

template <typename T>
template <class... Args>
typename s21::list<T>::iterator s21::list<T>::insert_many(const_iterator pos,
                                                          Args&&... args) {
  const size_type count = sizeof...(Args);
  if (count == 0) return iterator(const_cast<Node*>(pos.operator->()));

  bool is_begin = (pos == cbegin());
  bool is_end = (pos == cend());

  list<T> temp;
  (temp.push_back(std::forward<Args>(args)), ...);
  splice(pos, temp);

  if (is_begin) {
    return begin();
  } else if (is_end) {
    iterator ret(tail_);
    for (size_type i = 1; i < count; ++i) --ret;
    return ret;
  } else {
    iterator ret(const_cast<Node*>(pos.operator->()));
    for (size_type i = 0; i < count; ++i) --ret;
    return ret;
  }
}

template <typename T>
template <class... Args>
void s21::list<T>::insert_many_back(Args&&... args) {
  insert_many(cend(), std::forward<Args>(args)...);
}

template <typename T>
template <class... Args>
void s21::list<T>::insert_many_front(Args&&... args) {
  insert_many(cbegin(), std::forward<Args>(args)...);
}

template <typename T>
bool list<T>::operator==(const list& l) const {
  Node* current1 = head_;
  Node* current2 = l.head_;
  while (current1 && current2) {
    if (current1->data != current2->data) {
      return false;
    }
    current1 = current1->next;
    current2 = current2->next;
  }
  return (current1 == current2);
}

template <typename T>
void list<T>::print() const {
  Node* current = head_;
  while (current) {
    std::cout << current->data << " ";
    current = current->next;
  }
  std::cout << std::endl;
}

template <typename T>
list<T>::Node::Node(const_reference value)
    : data(value), next(nullptr), prev(nullptr) {}

}  // namespace s21
