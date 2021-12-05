#pragma once

#include <initializer_list>
#include <iterator>
#include <utility>

namespace mystl {
/**
 * @brief A self implemented linked list
 * Uses pseudo node design on two ends.
 *
 * @tparam T element type
 */
template <typename T> class list {
  private:
    class node {
        T element;
        node *prev, *next;
        friend class list;

      public:
        node() : prev(nullptr), next(nullptr){};
        template <typename... Args>
        node(Args &&...args) : element(args...), prev(nullptr), next(nullptr) {}
    };
    node *head, *tail;

  public:
    class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
      private:
        iterator() = default;
        iterator(node *p) : ptr(p) {}
        node *ptr;
        friend class list;

      public:
        iterator &operator++() {
            ptr = ptr->next;
            return *this;
        }
        iterator operator++(int) {
            iterator itr(this->ptr);
            operator++();
            return itr;
        }
        iterator &operator--() {
            ptr = ptr->prev;
            return *this;
        }
        iterator operator--(int) {
            iterator itr(this->ptr);
            operator--();
            return itr;
        }
        constexpr bool operator==(const iterator &rhs) const {
            return ptr == rhs.ptr;
        }
        constexpr bool operator!=(const iterator &rhs) const {
            return ptr != rhs.ptr;
        }
        T &operator*() { return ptr->element; }
    };

    /**
     * @brief Append element before designated position
     *
     * @tparam Args constructor of element
     * @param it indicate designated position
     * @param args parameters of element constructor
     * @return iterator iterator an iterator pointed to the inserted node
     */
    template <typename... Args>
    iterator emplace(const iterator &it, Args &&...args) {
        node *tmp = it.ptr->prev;
        it.ptr->prev = new node(std::forward<Args>(args)...);
        if (tmp) { // if append node in middle
            tmp->next =
                it.ptr->prev;    // update previous node's next node pointer
        } else {                 // if append element before head
            head = it.ptr->prev; // update head
        }
        auto ret = iterator(it.ptr->prev);
        ret.ptr->next = it.ptr;
        ret.ptr->prev = tmp;
        return ret;
    }

    template <typename... Args> T &emplace_back(Args &&...args) {
        return *emplace(end(), std::forward<Args>(args)...);
    }

    template <typename... Args> T &emplace_front(Args &&...args) {
        return *emplace(begin(), std::forward<Args>(args)...);
    }

    iterator begin() const { return iterator(head->next); }
    iterator end() const { return iterator(tail); }

    constexpr bool operator==(const list &rhs) const {
        return std::equal(this->begin(), this->end(), rhs.begin(), rhs.end());
    }

    constexpr bool operator!=(const list &rhs) const { return !(*this == rhs); }

    T &operator[](size_t index) {
        node *ret = head;
        for (size_t i = 0; i < index; ++i) {
            ret = head->next;
        }
        return ret->element;
    }

    // copy assignment
    list &operator=(const list &rhs) {
        // free original list
        for (node *it = head, *tmp; it != tail; it = tmp) {
            tmp = it->next;
            delete it;
        }
        delete tail;
        head = new node();
        tail = new node();
        head->next = tail;
        tail->prev = head;
        // copy
        if (this != &rhs) {
            for (const auto &v : rhs) {
                emplace_back(v);
            }
        }
        return *this;
    }

    // move assignment
    list &operator=(list &&rhs) {
        // free original list
        for (node *it = head, *tmp; it != tail; it = tmp) {
            tmp = it->next;
            delete it;
        }
        delete tail;
        head = new node();
        tail = new node();
        head->next = tail;
        tail->prev = head;
        // move
        if (this != &rhs) {
            head = rhs.head;
            tail = rhs.tail;
            rhs.head = rhs.tail = nullptr;
        }
        return *this;
    }

    list() : head(new node()), tail(new node()) {
        head->next = tail;
        tail->prev = head;
    }
    list(std::initializer_list<T> init) : head(new node()), tail(new node()) {
        head->next = tail;
        tail->prev = head;
        for (const auto &v : init) {
            emplace_back(v);
        }
    }

    // copy constructor
    list(const list &l) : head(new node()), tail(new node()) {
        head->next = tail;
        tail->prev = head;
        for (const auto &v : l) {
            emplace_back(v);
        }
    }

    // move constructor
    list(list &&l) : head(l.head), tail(l.tail) { l.head = l.tail = nullptr; }

    ~list() {
        for (node *it = head, *tmp; it != tail; it = tmp) {
            tmp = it->next;
            delete it;
        }
        delete tail;
    }
};
} // namespace mystl
