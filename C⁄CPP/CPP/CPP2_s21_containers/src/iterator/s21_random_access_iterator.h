#ifndef RANDOM_ACCESS_ITERATOR
#define RANDOM_ACCESS_ITERATOR

#include <iterator>
#include <type_traits>

namespace s21 {

template <typename T, bool IsConst>
class RandomAccessIterator {
 public:
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = typename std::conditional<IsConst, const T*, T*>::type;
  using reference = typename std::conditional<IsConst, const T&, T&>::type;

  RandomAccessIterator();
  RandomAccessIterator(pointer p);

  template <bool OtherConst,
            typename = std::enable_if_t<IsConst && !OtherConst>>
  RandomAccessIterator(const RandomAccessIterator<T, OtherConst>& other);

  reference operator*() const;
  pointer operator->() const;

  RandomAccessIterator& operator++();
  RandomAccessIterator operator++(int);
  RandomAccessIterator& operator--();
  RandomAccessIterator operator--(int);

  template <bool OtherConst>
  bool operator==(const RandomAccessIterator<T, OtherConst>& other) const;
  template <bool OtherConst>
  bool operator!=(const RandomAccessIterator<T, OtherConst>& other) const;
  template <bool OtherConst>
  bool operator<(const RandomAccessIterator<T, OtherConst>& other) const;
  template <bool OtherConst>
  bool operator>(const RandomAccessIterator<T, OtherConst>& other) const;
  template <bool OtherConst>
  bool operator<=(const RandomAccessIterator<T, OtherConst>& other) const;
  template <bool OtherConst>
  bool operator>=(const RandomAccessIterator<T, OtherConst>& other) const;

  RandomAccessIterator operator+(difference_type n) const;
  RandomAccessIterator operator-(difference_type n) const;
  template <bool OtherConst>
  difference_type operator-(
      const RandomAccessIterator<T, OtherConst>& other) const;
  RandomAccessIterator& operator+=(difference_type n);
  RandomAccessIterator& operator-=(difference_type n);
  reference operator[](difference_type n) const;

 private:
  pointer ptr_;
};

}  // namespace s21

#include "s21_random_access_iterator.tpp"

#endif