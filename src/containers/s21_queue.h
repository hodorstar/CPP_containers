/* Copyright 2023 sallieam
 *
 * This file contains Original Code created by Saveliy Karpushkin aka sallieam.
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

#ifndef SRC_CONTAINERS_S21_QUEUE_H_
#define SRC_CONTAINERS_S21_QUEUE_H_

/* ----- NAMESPACES AND CLASSES ----- */
namespace s21 {
template <typename T, typename containers = s21::vector<T>>
class queue {
 public:
  /* ----- TASK TYPES ----- */
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  using iterator = typename containers::iterator;
  using const_iterator = typename containers::const_iterator;

  /* ----- CONSTRUCTORS AND DESTRUCTORS ----- */
  queue() : base(){};
  queue(std::initializer_list<value_type> const& items) : base(items){};
  queue(const queue& other) : base(other.base){};
  queue& operator=(const queue& other) {
    base = other.base;
    return *this;
  }
  queue(queue&& other) : base(std::move(other.base)){};
  queue& operator=(queue&& other) {
    base = std::move(other.base);
    return *this;
  }
  ~queue() = default;

  /* ----- ACCESSORS AND MUTATORS ----- */
  bool empty() { return base.empty(); }
  size_type size() { return base.size(); }
  void pop() { base.erase(base.begin()); }
  void push(const_reference value) { base.insert(base.end(), value); }
  void swap(queue& other) { base.swap(other.base); }
  const_reference front() { return base.front(); }
  const_reference back() { return base.back(); }

  /* ----- BONUS METHODS ----- */
  template <typename... Args>
  void insert_many_back(Args&&... args) {
    base.insert_many(base.end(), args...);
  }

 private:
  /* ----- VARIABLES ----- */
  containers base;
};
}  // namespace s21

#endif  // SRC_CONTAINERS_S21_QUEUE_H_
