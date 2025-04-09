#ifndef BIDIRECTIONAL_ITERATOR_TPP
#define BIDIRECTIONAL_ITERATOR_TPP

#include "s21_bidirectional_iterator.h"

namespace s21 {

template <typename T, typename NodeType, bool IsConst>
BidirectionalIterator<T, NodeType, IsConst>::BidirectionalIterator()
    : node_(nullptr) {}

template <typename T, typename NodeType, bool IsConst>
BidirectionalIterator<T, NodeType, IsConst>::BidirectionalIterator(node_ptr p)
    : node_(p) {}

template <typename T, typename NodeType, bool IsConst>
template <bool OtherConst, typename>
BidirectionalIterator<T, NodeType, IsConst>::BidirectionalIterator(
    const BidirectionalIterator<T, NodeType, OtherConst>& other)
    : node_(other.operator->()) {}

template <typename T, typename NodeType, bool IsConst>
typename BidirectionalIterator<T, NodeType, IsConst>::reference
BidirectionalIterator<T, NodeType, IsConst>::operator*() const {
  return node_->data;
}

template <typename T, typename NodeType, bool IsConst>
typename BidirectionalIterator<T, NodeType, IsConst>::pointer
BidirectionalIterator<T, NodeType, IsConst>::operator->() const {
  return node_;
}

template <typename T, typename NodeType, bool IsConst>
BidirectionalIterator<T, NodeType, IsConst>&
BidirectionalIterator<T, NodeType, IsConst>::operator++() {
  if (node_) node_ = node_->next;
  return *this;
}

template <typename T, typename NodeType, bool IsConst>
BidirectionalIterator<T, NodeType, IsConst>
BidirectionalIterator<T, NodeType, IsConst>::operator++(int) {
  BidirectionalIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T, typename NodeType, bool IsConst>
BidirectionalIterator<T, NodeType, IsConst>&
BidirectionalIterator<T, NodeType, IsConst>::operator--() {
  if (node_) node_ = node_->prev;
  return *this;
}

template <typename T, typename NodeType, bool IsConst>
BidirectionalIterator<T, NodeType, IsConst>
BidirectionalIterator<T, NodeType, IsConst>::operator--(int) {
  BidirectionalIterator temp = *this;
  --(*this);
  return temp;
}

template <typename T, typename NodeType, bool IsConst>
bool BidirectionalIterator<T, NodeType, IsConst>::operator==(
    const BidirectionalIterator& other) const {
  return node_ == other.node_;
}

template <typename T, typename NodeType, bool IsConst>
bool BidirectionalIterator<T, NodeType, IsConst>::operator!=(
    const BidirectionalIterator& other) const {
  return node_ != other.node_;
}

}  // namespace s21
#endif