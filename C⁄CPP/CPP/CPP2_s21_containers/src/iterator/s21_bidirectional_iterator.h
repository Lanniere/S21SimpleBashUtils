#ifndef BIDIRECTIONAL_ITERATOR_H
#define BIDIRECTIONAL_ITERATOR_H
#include <type_traits>

namespace s21 {

template <typename T, typename NodeType, bool IsConst = false>
class BidirectionalIterator {
 public:
  // Если итератор константный, то node_ptr становится const NodeType*, иначе
  // NodeType*
  using node_ptr = std::conditional_t<IsConst, const NodeType*, NodeType*>;
  using value_type = T;
  using pointer = node_ptr;
  using reference = std::conditional_t<IsConst, const T&, T&>;

  BidirectionalIterator();
  explicit BidirectionalIterator(node_ptr p);

  template <bool OtherConst,
            typename = std::enable_if_t<IsConst && !OtherConst>>
  BidirectionalIterator(
      const BidirectionalIterator<T, NodeType, OtherConst>& other);
  reference operator*() const;
  pointer operator->() const;

  BidirectionalIterator& operator++();
  BidirectionalIterator operator++(int);

  BidirectionalIterator& operator--();
  BidirectionalIterator operator--(int);

  bool operator==(const BidirectionalIterator& other) const;
  bool operator!=(const BidirectionalIterator& other) const;

 private:
  node_ptr node_;
};

}  // namespace s21

#include "s21_bidirectional_iterator.tpp"
#endif  // BIDIRECTIONAL_ITERATOR_H
