/* Copyright 2023 tcinthia
 *
 * This file contains Original Code created by Roman Nabiev aka tcinthia.
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

#ifndef CONTAINERS_SRC_CONTAINERS_S21_SET_H_
#define CONTAINERS_SRC_CONTAINERS_S21_SET_H_

/* ----- NAMESPACES AND CLASSES ----- */
namespace s21 {
template <typename T>
class set {
 public:
  /* ----- TASK TYPES ----- */
  using tree = avl_tree<T, T>;
  using key_type = T;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = typename tree::key_iterator;
  using const_iterator = typename tree::const_key_iterator;
  using size_type = size_t;

  /* ----- CONSTRUCTORS AND DESTRUCTORS ----- */
  set() = default;
  set(std::initializer_list<value_type> const &items) {
    for (auto i = items.begin(); i != items.end(); ++i)
      if (!tree_.findNode(*i)) tree_.insert(*i, *i);
  };
  set(const set &other) : tree_(other.tree_){};
  set(set &&other) : tree_(std::move(other.tree_)){};
  set &operator=(const set &other) {
    set cpy(other);
    *this = std::move(cpy);
    return *this;
  }
  set &operator=(set &&other) {
    tree_ = std::move(other.tree_);
    return *this;
  }
  ~set() = default;

  /* ----- ACCESSORS AND MUTATORS ----- */
  bool empty() const { return !tree_.count_; }
  size_type size() const { return tree_.count_; }
  size_type max_size() const { return size_type(-1); }
  void erase(iterator pos) {
    if (pos != end()) tree_.remove(*pos);
  }
  void merge(set &other) {
    for (auto it = other.begin(), et = other.end(); it != et; ++it) insert(*it);
    other.clear();
  }
  void swap(set &other) { tree_ = std::move(other.tree_); }
  void clear() {
    if (tree_.root_) delete tree_.root_;
    tree_.root_ = nullptr;
    tree_.count_ = 0;
  }
  std::pair<iterator, bool> insert(const value_type &value) {
    bool exist = tree_.findNode(value);
    if (!exist) tree_.insert(value, value);
    iterator pos(tree_.findNode(value));
    return std::make_pair(pos, !exist);
  }
  iterator find(const value_type &key) {
    auto node = tree_.findNode(key);
    if (node) {
      return iterator(node);
    } else {
      return ++iterator(tree_.root_->findMax());
    }
  }
  bool contains(const value_type &key) const {
    return (tree_.findNode(key)) ? true : false;
  }

  /* ----- ITERATORS ----- */
  iterator begin() { return tree_.kbegin(); }
  const_iterator begin() const { return tree_.kbegin(); }
  iterator end() { return tree_.kend(); }
  const_iterator end() const { return tree_.kend(); }

  /* ----- BONUS METHODS ----- */
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::initializer_list elements{args...};
    vector<std::pair<iterator, bool>> insert_result(elements.size());
    for (auto elem : elements) insert_result.push_back(insert(elem));
    return insert_result;
  }

 private:
  /* ----- VARIABLES ----- */
  tree tree_;
};
}  // namespace s21

#endif  // CONTAINERS_SRC_CONTAINERS_S21_SET_H_
