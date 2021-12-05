#pragma once

#include <initializer_list>
#include <iterator>
#include <utility>

namespace mystl {
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
        if (it != iterator(nullptr)) {
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
        } else {
            // position is null = emplace back
            node *tmp = tail;
            tail = new node(std::forward<Args>(args)...);
            if (head == nullptr)
                head = tail;
            if (tmp != nullptr)
                tmp->next = tail;
            tail->prev = tmp;
            return iterator(tail);
        }
    }

    template <typename... Args> T &emplace_back(Args &&...args) {
        return *emplace(end(), std::forward<Args>(args)...);
    }

    template <typename... Args> T &emplace_front(Args &&...args) {
        return *emplace(begin(), std::forward<Args>(args)...);
    }

    iterator begin() const { return iterator(head); }
    iterator end() const { return iterator(nullptr); }

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
        head = tail = nullptr;
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
        head = tail = nullptr;
        // move
        if (this != &rhs) {
            head = rhs.head;
            tail = rhs.tail;
            rhs.head = rhs.tail = nullptr;
        }
        return *this;
    }

    list() : head(nullptr), tail(nullptr) {}
    list(std::initializer_list<T> init) : head(nullptr), tail(nullptr) {
        for (const auto &v : init) {
            emplace_back(v);
        }
    }

    // copy constructor
    list(const list &l) : head(nullptr), tail(nullptr) {
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
