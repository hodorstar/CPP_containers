/* Copyright 2023 hodorsta
 *
 * This file contains Original Code created by Ksenia Alonceva aka hodorsta.
 *
 * The Original Code and all software developed in the process of participation
 * on learning by experimental programming educational method. The whole
 * methodology was developed and distributed by autonomous non-profit
 * organization «School 21» (ANO «School 21»).
 *
 * Redistribution and use of this file, its parts, or entire project are
 * permitted by confirmation of its original creator.
 */

/* ========================================================================== */

#ifndef CONTAINERS_SRC_S21_ARRAY_H_
#define CONTAINERS_SRC_S21_ARRAY_H_

/* ----- NAMESPACES AND CLASSES ----- */
namespace s21 {
template <class T, size_t N>
class array {
 public:
  /* ----- TASK TYPES ----- */
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  /* ----- CONSTRUCTORS AND DESTRUCTORS ----- */
  array();
  array(std::initializer_list<value_type> const& items);

  /* ----- ACCESSORS AND MUTATORS ----- */
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void swap(array& other);
  void fill(const_reference value);
  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  T* data() noexcept;
  const T* data() const noexcept;

  /* ----- ITERATORS ----- */
  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  /* ----- VARIABLES ----- */
  T arr_[N];
};
}  // namespace s21

/* ----- FUNCTIONS ----- */
template <class T, size_t N>
s21::array<T, N>::array() {}

template <class T, size_t N>
s21::array<T, N>::array(std::initializer_list<value_type> const& items) {
  for (size_t i = 0; i < N; i++) arr_[i] = *(items.begin() + i);
}

template <class T, size_t N>
bool s21::array<T, N>::empty() const noexcept {
  return N == 0;
}

template <class T, size_t N>
size_t s21::array<T, N>::size() const noexcept {
  return N;
}

template <class T, size_t N>
size_t s21::array<T, N>::max_size() const noexcept {
  return N;
}

template <class T, size_t N>
void s21::array<T, N>::swap(array& other) {
  if (size() == other.size()) std::swap(arr_, other.arr_);
}

template <class T, size_t N>
void s21::array<T, N>::fill(const_reference value) {
  for (size_t i = 0; i < size(); i++) arr_[i] = value;
}

template <class T, size_t N>
T& s21::array<T, N>::at(size_type pos) {
  if (pos > N) throw std::out_of_range("out of range");
  return arr_[pos];
}

template <class T, size_t N>
const T& s21::array<T, N>::at(size_type pos) const {
  if (pos > N) throw std::out_of_range("out of range");
  return arr_[pos];
}

template <class T, size_t N>
T& s21::array<T, N>::operator[](size_type pos) {
  return arr_[pos];
}

template <class T, size_t N>
const T& s21::array<T, N>::operator[](size_type pos) const {
  return arr_[pos];
}

template <class T, size_t N>
T& s21::array<T, N>::front() {
  return arr_[0];
}

template <class T, size_t N>
const T& s21::array<T, N>::front() const {
  return arr_[0];
}

template <class T, size_t N>
T& s21::array<T, N>::back() {
  return arr_[N - 1];
}

template <class T, size_t N>
const T& s21::array<T, N>::back() const {
  return arr_[N - 1];
}

template <class T, size_t N>
T* s21::array<T, N>::data() noexcept {
  return arr_;
}

template <class T, size_t N>
const T* s21::array<T, N>::data() const noexcept {
  return arr_;
}

template <class T, size_t N>
typename s21::array<T, N>::iterator s21::array<T, N>::begin() noexcept {
  return arr_;
}

template <class T, size_t N>
typename s21::array<T, N>::const_iterator s21::array<T, N>::begin()
    const noexcept {
  return arr_;
}

template <class T, size_t N>
typename s21::array<T, N>::iterator s21::array<T, N>::end() noexcept {
  return arr_ + N;
}

template <class T, size_t N>
typename s21::array<T, N>::const_iterator s21::array<T, N>::end()
    const noexcept {
  return arr_ + N;
}

#endif  // S21CONTAINERS_SRC_S21_ARRAY_H_
