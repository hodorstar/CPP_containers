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

#ifndef CONTAINERS_SRC_CONTAINERS_S21_AVL_TREE_H_
#define CONTAINERS_SRC_CONTAINERS_S21_AVL_TREE_H_

/* ----- NAMESPACES AND CLASSES ----- */
namespace s21 {
template <typename K, typename V>
class avl_tree {
 public:
  class node {
   public:
    /* ----- CONSTRUCTORS AND DESTRUCTORS ----- */
    node(K key, V value) : key(key), value(value){};
    node(const node &other)
        : key(other.key), value(other.value), height(other.height){};
    node(node &&other) { *this = std::move(other); };
    node &operator=(const node &other) {
      node cpy(other);
      *this = std::swap(cpy);
      return *this;
    }
    node &operator=(node &&other) {
      std::swap(key, other.key);
      std::swap(value, other.value);
      std::swap(height, other.height);
      std::swap(parent, other.parent);
      std::swap(left, other.left);
      std::swap(right, other.right);
      return *this;
    }
    ~node() {
      delete left;
      delete right;
    }
    /* ----- ACCESSORS AND MUTATORS ----- */
    node *insertNode(K k, V v) {
      if (k < key) {
        if (!left) {
          node *result = new node(k, v);
          result->parent = this;
          left = result;
          return balance();
        }
        left = left->insertNode(k, v);
      } else if (k > key) {
        if (!right) {
          node *result = new node(k, v);
          result->parent = this;
          right = result;
          return balance();
        }
        right = right->insertNode(k, v);
      }
      return balance();
    }

    /* ----- TREE PRINTER ----- */
    void copyHelper(node *src) {
      if (src->left) {
        left = new node(*(src->left));
        left->parent = this;
        left->copyHelper(src->left);
      }
      if (src->right) {
        right = new node(*(src->right));
        right->parent = this;
        right->copyHelper(src->right);
      }
    };
    void printHelper(std::string indent, bool last, int depth) const {
      if (depth < 10) {
        std::cout << indent;
        if (last) {
          std::cout << "R----";
          indent += "     ";
        } else {
          std::cout << "L----";
          indent += "|    ";
        }
        std::cout << "(" << key << ")";
        std::cout << std::endl;
        if (left) left->printHelper(indent, false, depth + 1);
        if (right) right->printHelper(indent, true, depth + 1);
      }
    };
    /* ----- TREE BALANCING ----- */
    int getHeight() const { return height; }
    int bFactor() const {
      return (right ? right->getHeight() : 0) - (left ? left->getHeight() : 0);
    }
    void fixHeight() {
      size_t hl = left ? left->getHeight() : 0;
      size_t hr = right ? right->getHeight() : 0;
      height = (hl > hr ? hl : hr) + 1;
    }
    node *rotateRight() {
      node *result = left;
      if (result) {
        result->parent = parent;
        left = result->right;
      }
      if (left) left->parent = this;
      if (result) result->right = this;
      parent = result;
      fixHeight();
      if (result) result->fixHeight();
      return result;
    }
    node *rotateLeft() {
      node *result = right;
      if (result) {
        result->parent = parent;
        right = result->left;
      }
      if (right) right->parent = this;
      if (result) result->left = this;
      parent = result;
      fixHeight();
      if (result) result->fixHeight();
      return result;
    }
    node *balance() {
      fixHeight();
      if (bFactor() == 2) {
        if (right->bFactor() < 0) right = right->rotateRight();
        return rotateLeft();
      }
      if (bFactor() == -2) {
        if (left->bFactor() > 0) left = left->rotateLeft();
        return rotateRight();
      }
      return this;
    }

    node *findMin() const {
      return left ? left->findMin() : const_cast<node *>(this);
    }
    node *findMax() const {
      return right ? right->findMax() : const_cast<node *>(this);
    }
    node *removeMin() {
      if (!left) {
        if (right) right->parent = parent;
        return right;
      }
      left = left->removeMin();
      return balance();
    }
    node *removeNode(K k) {
      if (k < key) {
        if (!left) return this;
        left = left->removeNode(k);
      } else if (k > key) {
        if (!right) return this;
        right = right->removeNode(k);
      } else {
        if (!right) {
          node *result = left;
          if (result) result->parent = parent;
          left = nullptr;
          right = nullptr;
          parent = nullptr;
          delete this;
          return result ? result->balance() : nullptr;
        }
        node *min = right->findMin();
        min->right = right->removeMin();
        min->left = left;
        min->parent = parent;
        if (min->left) min->left->parent = min;
        if (min->right) min->right->parent = min;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        delete this;
        return min->balance();
      }
      return balance();
    }
    size_t countNodes() const {
      if (left && right) {
        return 1 + left->countNodes() + right->countNodes();
      } else if (left) {
        return 1 + left->countNodes();
      } else if (right) {
        return 1 + right->countNodes();
      } else {
        return 1;
      }
    }
    node *find(K k) const {
      if (k < key) {
        if (!left) return nullptr;
        return left->find(k);
      } else if (k > key) {
        if (!right) return nullptr;
        return right->find(k);
      } else {
        node *this_ = const_cast<node *>(this);
        return this_;
      }
    }
    node *findNext() const {
      node *this_ = const_cast<node *>(this);
      if (this_->right) return this_->right->findMin();
      if (this_->parent) {
        while (this_->parent && this_->parent->key < key) this_ = this_->parent;
        if (!this_->parent) return nullptr;
        return this_->parent;
      }
      return nullptr;
    }
    node *findPrev() const {
      node *this_ = const_cast<node *>(this);
      if (this_->left) return this_->left->findMax();
      if (this_->parent) {
        while (this_->parent && this_->parent->key > key) this_ = this_->parent;
        if (!this_->parent) return nullptr;
        return this_->parent;
      }
      return nullptr;
    }

    bool operator==(const node &other) const {
      return key == other.key && value == other.value;
    }
    bool operator!=(const node &other) const {
      return key != other.key || value != other.value;
    }

    const K key;
    V value;
    size_t height = 0;
    node *left = nullptr;
    node *right = nullptr;
    node *parent = nullptr;
  };

  template <typename T>
  class treeIterator {
   public:
    /* ----- TYPES ----- */
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = int32_t;
    using pointer = T *;
    using reference = T &;

    treeIterator() : ptr_(nullptr), prev_(nullptr), next_(nullptr){};
    treeIterator(T *ptr) : ptr_(ptr) {
      if (ptr_) {
        prev_ = ptr_->findPrev();
        next_ = ptr_->findNext();
      }
    };

    treeIterator &operator++() {
      prev_ = ptr_;
      ptr_ = next_;
      if (next_) next_ = next_->findNext();
      return *this;
    }
    treeIterator &operator--() {
      next_ = ptr_;
      ptr_ = prev_;
      if (prev_) prev_ = prev_->findPrev();
      return *this;
    }

    bool operator==(const treeIterator &other) const {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const treeIterator &other) const {
      return ptr_ != other.ptr_;
    }

    T &operator*() const { return *ptr_; }
    T *operator->() const { return ptr_; }

    operator treeIterator<const T>() const {
      return treeIterator<const T>(ptr_, prev_, next_);
    }

   protected:
    T *ptr_;
    T *prev_;
    T *next_;
  };

  template <typename T>
  class treeKeyIterator : public treeIterator<T> {
   public:
    /* ----- TYPES ----- */
    using base = treeIterator<T>;
    using iterator_category = typename treeIterator<T>::iterator_category;
    using value_type = T;
    using difference_type = int32_t;
    using pointer = T *;
    using reference = T &;

    treeKeyIterator() : base(){};
    treeKeyIterator(T *ptr) : base(ptr){};

    treeKeyIterator &operator++() {
      base::operator++();
      return *this;
    }
    treeKeyIterator &operator--() {
      base::operator--();
      return *this;
    }

    bool operator==(const treeKeyIterator &other) const {
      return base::ptr_ == other.ptr_;
    }
    bool operator!=(const treeKeyIterator &other) const {
      return base::ptr_ != other.ptr_;
    }

    typename std::conditional<std::is_const<T>::value, V, V &>::type
    operator*() {
      return base::ptr_->value;
    }

    operator treeKeyIterator<const T>() const {
      return treeKeyIterator<const T>(base::ptr_, base::prev_, base::next_);
    }
  };

  /* ----- TYPES ----- */
  using iterator = treeIterator<node>;
  using const_iterator = treeIterator<const node>;
  using key_iterator = treeKeyIterator<node>;
  using const_key_iterator = treeKeyIterator<const node>;

  avl_tree() : root_(nullptr), count_(0){};
  avl_tree(K key, V value) : root_(new node(key, value)), count_(1){};
  avl_tree(const avl_tree &other)
      : root_(new node(other.root_->key, other.root_->value)),
        count_(other.count_) {
    root_->copyHelper(other.root_);
  }
  avl_tree(avl_tree &&other) : avl_tree() { *this = std::move(other); }
  avl_tree &operator=(const avl_tree &other) {
    avl_tree cpy(other);
    *this = std::move(cpy);
    return *this;
  }
  avl_tree &operator=(avl_tree &&other) {
    std::swap(root_, other.root_);
    std::swap(count_, other.count_);
    return *this;
  }
  ~avl_tree() { delete root_; };

  void insert(K k, V v) {
    if (root_) {
      root_ = root_->insertNode(k, v);
      count_ = root_->countNodes();
    } else {
      root_ = new node(k, v);
      count_ = 1;
    }
  }
  void remove(K k) {
    root_ = root_->removeNode(k);
    if (root_) {
      count_ = root_->countNodes();
    } else {
      count_ = 0;
    }
  }
  size_t count() const { return root_ ? root_->countNodes() : 0; }
  node *findNode(K k) const { return root_ ? root_->find(k) : nullptr; }

  void print() const {
    if (root_) root_->printHelper("", true, 5);
  }

  iterator begin() {
    if (root_) return iterator(root_->findMin());
    return end();
  }
  iterator end() {
    if (root_) return ++iterator(root_->findMax());
    return iterator();
  }

  const_iterator begin() const {
    if (root_) return const_iterator(root_->findMin());
    return end();
  }
  const_iterator end() const {
    if (root_) return ++const_iterator(root_->findMax());
    return const_iterator();
  }

  key_iterator kbegin() {
    if (root_) return key_iterator(root_->findMin());
    return kend();
  }
  key_iterator kend() {
    if (root_) return ++key_iterator(root_->findMax());
    return key_iterator();
  }

  const_key_iterator kbegin() const {
    if (root_) return const_key_iterator(root_->findMin());
    return kend();
  }
  const_key_iterator kend() const {
    if (root_) return ++const_key_iterator(root_->findMax());
    return const_key_iterator();
  }

  node *root_;
  size_t count_;
};

template <typename K, typename V>
class multi_avl_tree {
 public:
  class node {
   public:
    node(K key, V value) : key(key), value(value){};
    node(const node &other) : key(other.key), value(other.value){};
    node(node &&other) { *this = std::move(other); };
    node &operator=(const node &other) {
      node cpy(other);
      *this = std::swap(cpy);
      return *this;
    }
    node &operator=(node &&other) {
      std::swap(key, other.key);
      std::swap(value, other.value);
      std::swap(parent, other.parent);
      std::swap(left, other.left);
      std::swap(right, other.right);
      return *this;
    }
    ~node() {
      delete left;
      delete right;
    }

    void copyHelper(node *src) {
      if (src->left) {
        left = new node(*(src->left));
        left->parent = this;
        left->copyHelper(src->left);
      }
      if (src->right) {
        right = new node(*(src->right));
        right->parent = this;
        right->copyHelper(src->right);
      }
    };
    void printHelper(std::string indent, bool last, int depth) const {
      if (depth < 10) {
        std::cout << indent;
        if (last) {
          std::cout << "R----";
          indent += "     ";
        } else {
          std::cout << "L----";
          indent += "|    ";
        }
        std::cout << "(" << key << ")" << std::endl;
        if (left) left->printHelper(indent, false, depth + 1);
        if (right) right->printHelper(indent, true, depth + 1);
      }
    };

    node *insertNode(K k, V v) {
      if (k < key) {
        if (!left) {
          node *result = new node(k, v);
          result->parent = this;
          left = result;
          return this;
        }
        left = left->insertNode(k, v);
      } else if (k > key) {
        if (!right) {
          node *result = new node(k, v);
          result->parent = this;
          right = result;
          return this;
        }
        right = right->insertNode(k, v);
      } else if (k == key) {
        node *result = new node(k, v);
        result->parent = this;
        result->left = left;
        if (left) left->parent = result;
        left = result;
        return this;
      }
      return this;
    }
    node *findMin() const {
      return left ? left->findMin() : const_cast<node *>(this);
    }
    node *findMax() const {
      return right ? right->findMax() : const_cast<node *>(this);
    }
    node *findFirst() const {
      return left && left->key == key ? left->findFirst()
                                      : const_cast<node *>(this);
    }
    node *findLast() const {
      return parent && parent->key == key ? parent->findLast()
                                          : const_cast<node *>(this);
    }
    node *removeMin() {
      if (!left) {
        if (right) right->parent = parent;
        return right;
      }
      left = left->removeMin();
      return this;
    }
    node *removeNode(K k) {
      if (k < key) {
        if (!left) return this;
        left = left->removeNode(k);
      } else if (k > key) {
        if (!right) return this;
        right = right->removeNode(k);
      } else {
        if (!right || (left && k == left->key)) {
          node *result = left;
          if (result) result->parent = parent;
          if (right) {
            right->parent = result;
            result->right = right;
          }
          left = nullptr;
          right = nullptr;
          parent = nullptr;
          delete this;
          return result;
        }
        node *min = right->findMin();
        min->right = right->removeMin();
        min->left = left;
        min->parent = parent;
        if (min->left) min->left->parent = min;
        if (min->right) min->right->parent = min;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        delete this;
        return min;
      }
      return this;
    }
    size_t countNodes() const {
      if (left && right) {
        return 1 + left->countNodes() + right->countNodes();
      } else if (left) {
        return 1 + left->countNodes();
      } else if (right) {
        return 1 + right->countNodes();
      } else {
        return 1;
      }
    }
    node *find(K k) const {
      if (k < key) {
        if (!left) return nullptr;
        return left->find(k);
      } else if (k > key) {
        if (!right) return nullptr;
        return right->find(k);
      } else {
        node *this_ = const_cast<node *>(this);
        return this_;
      }
    }
    node *findNext() const {
      node *this_ = const_cast<node *>(this);
      if (this_->right) return this_->right->findMin();
      if (this_->parent) {
        if (this_->parent->key == this_->key) return this_->parent;
        while (this_->parent && this_->parent->key < key) this_ = this_->parent;
        if (!this_->parent) return nullptr;
        return this_->parent;
      }
      return nullptr;
    }
    node *findPrev() const {
      node *this_ = const_cast<node *>(this);
      if (this_->left) {
        if (this_->left->key == key) return this_->left;
        return this_->left->findMax();
      }
      if (this_->parent) {
        while (this_->parent && this_->parent->key >= key)
          this_ = this_->parent;
        if (!this_->parent) return nullptr;
        return this_->parent;
      }
      return nullptr;
    }

    bool operator==(const node &other) const {
      return key == other.key && value == other.value;
    }
    bool operator!=(const node &other) const {
      return key != other.key || value != other.value;
    }

    const K key;
    V value;
    node *left = nullptr;
    node *right = nullptr;
    node *parent = nullptr;
  };

  template <typename T>
  class treeIterator {
   public:
    /* ----- TYPES ----- */
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = int32_t;
    using pointer = T *;
    using reference = T &;

    treeIterator() : ptr_(nullptr), prev_(nullptr), next_(nullptr){};
    treeIterator(T *ptr) : ptr_(ptr) {
      if (ptr_) {
        prev_ = ptr_->findPrev();
        next_ = ptr_->findNext();
      }
    };

    treeIterator &operator++() {
      prev_ = ptr_;
      ptr_ = next_;
      if (next_) next_ = next_->findNext();
      return *this;
    }
    treeIterator &operator--() {
      next_ = ptr_;
      ptr_ = prev_;
      if (prev_) prev_ = prev_->findPrev();
      return *this;
    }

    bool operator==(const treeIterator &other) const {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const treeIterator &other) const {
      return ptr_ != other.ptr_;
    }

    T &operator*() const { return *ptr_; }
    T *operator->() const { return ptr_; }

    operator treeIterator<const T>() const {
      return treeIterator<const T>(ptr_, prev_, next_);
    }

   protected:
    T *ptr_;
    T *prev_;
    T *next_;
  };

  template <typename T>
  class treeKeyIterator : public treeIterator<T> {
   public:
    /* ----- TYPES ----- */
    using base = treeIterator<T>;
    using iterator_category = typename treeIterator<T>::iterator_category;
    using value_type = T;
    using difference_type = int32_t;
    using pointer = T *;
    using reference = T &;

    treeKeyIterator() : base(){};
    treeKeyIterator(T *ptr) : base(ptr){};

    treeKeyIterator &operator++() {
      base::operator++();
      return *this;
    }
    treeKeyIterator &operator--() {
      base::operator--();
      return *this;
    }

    bool operator==(const treeKeyIterator &other) const {
      return base::ptr_ == other.ptr_;
    }
    bool operator!=(const treeKeyIterator &other) const {
      return base::ptr_ != other.ptr_;
    }

    typename std::conditional<std::is_const<T>::value, V, V &>::type
    operator*() {
      return base::ptr_->value;
    }

    operator treeKeyIterator<const T>() const {
      return treeKeyIterator<const T>(base::ptr_, base::prev_, base::next_);
    }
  };

  /* ----- TYPES ----- */
  using iterator = treeIterator<node>;
  using const_iterator = treeIterator<const node>;
  using key_iterator = treeKeyIterator<node>;
  using const_key_iterator = treeKeyIterator<const node>;

  multi_avl_tree() : root_(nullptr), count_(0){};
  multi_avl_tree(K key, V value) : root_(new node(key, value)), count_(1){};
  multi_avl_tree(const multi_avl_tree &other)
      : root_(new node(other.root_->key, other.root_->value)),
        count_(other.count_) {
    root_->copyHelper(other.root_);
  }
  multi_avl_tree(multi_avl_tree &&other) : multi_avl_tree() {
    *this = std::move(other);
  }
  multi_avl_tree &operator=(const multi_avl_tree &other) {
    multi_avl_tree cpy(other);
    *this = std::move(cpy);
    return *this;
  }
  multi_avl_tree &operator=(multi_avl_tree &&other) {
    std::swap(root_, other.root_);
    std::swap(count_, other.count_);
    return *this;
  }
  ~multi_avl_tree() { delete root_; };

  void insert(K k, V v) {
    if (root_) {
      root_ = root_->insertNode(k, v);
      count_ = root_->countNodes();
    } else {
      root_ = new node(k, v);
      count_ = 1;
    }
  }
  void remove(K k) {
    root_ = root_->removeNode(k);
    if (root_) {
      count_ = root_->countNodes();
    } else {
      count_ = 0;
    }
  }
  size_t count() const { return root_ ? root_->countNodes() : 0; }
  node *findNode(K k) const { return root_ ? root_->find(k) : nullptr; }
  node *findFirstNode(K k) const {
    if (root_) {
      node *tmp = root_->find(k);
      if (tmp) return tmp->findFirst();
    }
    return nullptr;
  }
  node *findLastNode(K k) const {
    if (root_) {
      node *tmp = root_->find(k);
      if (tmp) return tmp->findNext();
    }
    return nullptr;
  }

  void print() const {
    if (root_) root_->printHelper("", true, 0);
  }

  iterator begin() {
    if (root_) return iterator(root_->findMin());
    return end();
  }
  iterator end() {
    if (root_) return ++iterator(root_->findMax());
    return iterator();
  }

  const_iterator begin() const {
    if (root_) return const_iterator(root_->findMin());
    return end();
  }
  const_iterator end() const {
    if (root_) return ++const_iterator(root_->findMax());
    return const_iterator();
  }

  key_iterator kbegin() {
    if (root_) return key_iterator(root_->findMin());
    return kend();
  }
  key_iterator kend() {
    if (root_) return ++key_iterator(root_->findMax());
    return key_iterator();
  }

  const_key_iterator kbegin() const {
    if (root_) return const_key_iterator(root_->findMin());
    return kend();
  }
  const_key_iterator kend() const {
    if (root_) return ++const_key_iterator(root_->findMax());
    return const_key_iterator();
  }

  node *root_;
  size_t count_;
};
}  // namespace s21

#endif  // S21CONTAINERS_SRC_CONTAINERS_S21_AVL_TREE_H_
