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

#ifndef CONTAINERS_SRC_CONTAINERS_S21_MULTISET_H_
#define CONTAINERS_SRC_CONTAINERS_S21_MULTISET_H_

/* ----- NAMESPACES AND CLASSES ----- */
namespace s21 {
template <typename T>
class multiset {
 public:
  /* ----- TASK TYPES ----- */
  using key_type = T;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using tree = multi_avl_tree<T, T>;
  using iterator = typename tree::key_iterator;
  using const_iterator = typename tree::const_key_iterator;

  /* ----- CONSTRUCTORS AND DESTRUCTORS ----- */
  multiset() = default;
  multiset(std::initializer_list<value_type> const &items) {
    for (auto i = items.begin(); i != items.end(); ++i) tree_.insert(*i, *i);
  };
  multiset(const multiset &other) : tree_(other.tree_){};
  multiset &operator=(const multiset &other) {
    multiset cpy(other);
    *this = std::move(cpy);
    return *this;
  }
  multiset(multiset &&other) : tree_(std::move(other.tree_)){};
  multiset &operator=(multiset &&other) {
    tree_ = std::move(other.tree_);
    return *this;
  }
  ~multiset() = default;

  /* ----- ACCESSORS AND MUTATORS ----- */
  bool empty() const { return !tree_.count_; }
  size_type size() const { return tree_.count_; }
  size_type max_size() const { return size_type(-1); }
  void erase(iterator pos) {
    if (pos != end()) tree_.remove(*pos);
  }
  void merge(multiset &other) {
    for (auto it = other.begin(), et = other.end(); it != et; ++it) insert(*it);
    other.clear();
  }
  void swap(multiset &other) { tree_ = std::move(other.tree_); }
  void clear() {
    if (tree_.root_) delete tree_.root_;
    tree_.root_ = nullptr;
    tree_.count_ = 0;
  }
  iterator insert(const value_type &value) {
    tree_.insert(value, value);
    iterator pos(tree_.findFirstNode(value));
    return pos;
  }
  iterator find(const_reference key) {
    auto node = tree_.findFirstNode(key);
    if (node) {
      return iterator(node);
    } else {
      return ++iterator(tree_.root_->findMax());
    }
  }
  bool contains(const_reference key) const {
    return (tree_.findNode(key)) ? true : false;
  }
  std::pair<iterator, iterator> equal_range(const_reference key) {
    iterator first(tree_.findFirstNode(key));
    iterator last(tree_.findLastNode(key));
    return std::make_pair(first, last);
  }
  std::pair<const_iterator, const_iterator> equal_range(
      const_reference key) const {
    const_iterator first(tree_.findFirstNode(key));
    const_iterator last(tree_.findLastNode(key));
    return std::make_pair(first, last);
  }
  size_type count(const_reference key) const {
    std::pair<const_iterator, const_iterator> range = equal_range(key);
    return std::distance(range.first, range.second);
  }
  iterator lower_bound(const_reference key) { return equal_range(key).first; }
  iterator upper_bound(const_reference key) { return equal_range(key).second; }

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
    for (auto elem : elements)
      insert_result.push_back(std::make_pair(insert(elem), true));
    return insert_result;
  }

 private:
  /* ----- VARIABLES ----- */
  tree tree_;
};
}  // namespace s21

#endif  // CONTAINERS_SRC_CONTAINERS_S21_MULTISET_H_
