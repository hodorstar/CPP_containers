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

#ifndef CONTAINERS_SRC_CONTAINERS_S21_MAP_H_
#define CONTAINERS_SRC_CONTAINERS_S21_MAP_H_

/* ----- NAMESPACES AND CLASSES ----- */
namespace s21 {
template <typename K, typename V>
class map {
 public:
  /* ----- TASK TYPES ----- */
  using tree = avl_tree<K, V>;
  using key_type = K;
  using mapped_type = V;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename tree::iterator;
  using const_iterator = typename tree::const_iterator;
  using size_type = size_t;

  /* ----- CONSTRUCTORS AND DESTRUCTORS ----- */
  map() = default;
  map(std::initializer_list<value_type> const &items) {
    for (auto i = items.begin(); i != items.end(); ++i)
      if (!tree_.findNode(i->first)) tree_.insert(i->first, i->second);
  };
  map(const map &other) : tree_(other.tree_){};
  map &operator=(const map &other) {
    map cpy(other);
    *this = std::move(cpy);
    return *this;
  }
  map(map &&other) : tree_(std::move(other.tree_)){};
  map &operator=(map &&other) {
    tree_ = std::move(other.tree_);
    return *this;
  }
  ~map() = default;

  /* ----- ACCESSORS AND MUTATORS ----- */
  bool empty() const { return !tree_.count_; }
  size_type size() const { return tree_.count_; }
  size_type max_size() const { return size_type(-1); }
  void erase(iterator pos) {
    if (pos != end()) tree_.remove(pos->key);
  }
  void merge(map &other) {
    for (auto it = other.begin(), et = other.end(); it != et; ++it)
      insert(it->key, it->value);
    other.clear();
  }
  void swap(map &other) { tree_ = std::move(other.tree_); }
  void clear() {
    if (tree_.root_) delete tree_.root_;
    tree_.root_ = nullptr;
    tree_.count_ = 0;
  }
  std::pair<iterator, bool> insert(const value_type &value) {
    bool exist = tree_.findNode(value.first);
    if (!exist) tree_.insert(value.first, value.second);
    iterator pos(tree_.findNode(value.first));
    return std::make_pair(pos, !exist);
  }
  std::pair<iterator, bool> insert(const key_type &key,
                                   const mapped_type &obj) {
    bool exist = tree_.findNode(key);
    if (!exist) tree_.insert(key, obj);
    iterator pos(tree_.findNode(key));
    return std::make_pair(pos, !exist);
  }
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj) {
    bool exist = tree_.findNode(key);
    if (!exist) {
      tree_.insert(key, obj);
    } else {
      tree_.findNode(key)->value = obj;
    }
    iterator pos(tree_.findNode(key));
    return std::make_pair(pos, !exist);
  }
  mapped_type &at(const key_type &key) {
    if (!tree_.findNode(key)) throw std::out_of_range("No such element in map");
    return tree_.findNode(key)->value;
  }
  iterator find(const key_type &key) const {
    return iterator(tree_.findNode(key));
  }
  bool contains(const key_type &key) const {
    return (tree_.findNode(key)) ? true : false;
  }

  /* ----- ITERATORS ----- */
  iterator begin() { return tree_.begin(); }
  const_iterator begin() const { return tree_.begin(); }
  iterator end() { return tree_.end(); }
  const_iterator end() const { return tree_.end(); }

  /* ----- OPERATOR OVERLOADS ----- */
  mapped_type &operator[](const key_type &key) {
    if (!tree_.findNode(key)) tree_.insert(key, mapped_type());
    return tree_.findNode(key)->value;
  }

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

#endif  // CONTAINERS_SRC_CONTAINERS_S21_MAP_H_
