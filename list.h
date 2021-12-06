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
    node *m_head, *m_tail;
    size_t m_size;

  public:
    class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
      private:
        iterator() : ptr(nullptr) {}
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

  private:
    iterator emplace_node(const iterator &it, iterator n) {
        node *tmp = it.ptr->prev;
        it.ptr->prev = n.ptr;
        tmp->next = it.ptr->prev; // update previous node's next node pointer
        //(because theprotection of pseudo node, tmp will never be null)
        auto ret = iterator(it.ptr->prev);
        ret.ptr->next = it.ptr;
        ret.ptr->prev = tmp;
        return ret;
    }

  public:
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
        tmp->next = it.ptr->prev; // update previous node's next node pointer
        //(because theprotection of pseudo node, tmp will never be null)
        auto ret = iterator(it.ptr->prev);
        ret.ptr->next = it.ptr;
        ret.ptr->prev = tmp;
        ++m_size; // increment container size
        return ret;
    }

    template <typename... Args> T &emplace_back(Args &&...args) {
        return *emplace(end(), std::forward<Args>(args)...);
    }

    template <typename... Args> T &emplace_front(Args &&...args) {
        return *emplace(begin(), std::forward<Args>(args)...);
    }

    iterator erase(const iterator it) {
        it.ptr->prev->next = it.ptr->next;
        it.ptr->next->prev = it.ptr->prev;
        node *tmp = it.ptr->next;
        delete it.ptr;
        --m_size; // decrement container size
        return iterator(tmp);
    }
    iterator erase(const iterator first, const iterator last) {
        first.ptr->prev->next = last.ptr;
        iterator it, tmp;
        for (it = first; it != last; it = tmp) {
            tmp = std::next(it);
            delete it.ptr;
            --m_size; // decrement container size by 1
        }
        tmp.ptr->prev = first.ptr;
        return tmp;
    }
    void pop_front() { erase(begin()); }
    void pop_back() { erase(std::prev(end())); }

    iterator begin() noexcept { return iterator(m_head->next); }
    const iterator begin() const noexcept { return iterator(m_head->next); }
    iterator end() noexcept { return iterator(m_tail); }
    const iterator end() const noexcept { return iterator(m_tail); }
    std::reverse_iterator<iterator> rbegin() noexcept {
        return std::reverse_iterator(end());
    }
    const std::reverse_iterator<iterator> rbegin() const noexcept {
        return std::reverse_iterator(end());
    }
    std::reverse_iterator<iterator> rend() noexcept {
        return std::reverse_iterator(begin());
    }
    const std::reverse_iterator<iterator> rend() const noexcept {
        return std::reverse_iterator(begin());
    }
    const iterator cbegin() const noexcept { return iterator(m_head->next); }
    const iterator cend() const noexcept { return iterator(m_tail); }
    const std::reverse_iterator<iterator> crbegin() const noexcept {
        return std::reverse_iterator(rbegin());
    }
    const std::reverse_iterator<const iterator> crend() const noexcept {
        return std::reverse_iterator(rend());
    }

    constexpr bool operator==(const list &rhs) const {
        return std::equal(this->begin(), this->end(), rhs.begin(), rhs.end());
    }

    constexpr bool operator!=(const list &rhs) const { return !(*this == rhs); }

    T &operator[](size_t index) { return *std::next(begin(), index); }

    size_t size() const noexcept { return m_size; }
    bool empty() const noexcept { return m_size == 0; }

    template <typename Comp> void merge(list &&other, Comp comp) {
        merge(other, comp);
    }
    void merge(list &&other) { merge(std::forward<list>(other), std::less()); }

    template <typename Comp> void merge(list &other, Comp comp) {
        if (&other == this)
            return;
        auto it = begin(), oit = other.begin();
        for (; it != end() && oit != other.end();) {
            if (!comp(*it, *oit)) {
                auto next = std::next(oit);
                it = emplace_node(it, oit);
                ++m_size; // increment container size
                oit = next;
            } else {
                ++it;
            }
        }
        for (; oit != other.end();) {
            auto next = std::next(oit);
            emplace_node(end(), oit);
            ++m_size; // increment container size
            oit = next;
        }
        other.m_size = 0;
        other.m_head->next = other.m_tail;
        other.m_tail->prev = other.m_head;
    }
    void merge(list &other) { merge(other, std::less()); }

  private:
    list split(iterator &&it) {
        node *tmp = it.ptr->prev->next = new node();
        it.ptr->prev->next->prev = it.ptr->prev;
        list ret;                  // declare list to return
        ret.m_tail = m_tail;       // set tail
        ret.m_head->next = it.ptr; // setup dummy head
        it.ptr->prev = ret.m_head;
        m_tail = tmp;
        size_t counter = 0;
        for (auto it = ret.begin(); it != ret.end(); ++it) {
            ++counter;
        }
        ret.m_size = counter;
        m_size -= counter;
        return ret;
    }

  public:
    template <typename Comp> void sort(Comp comp) {
        if (size() <= 1)
            return;
        if (size() == 2) {
            auto start_it = begin(), end_it = std::prev(end());
            if (!comp(*start_it, *end_it)) { // swap on reverse order
                node *pprev = start_it.ptr->prev, *nnext = end_it.ptr->next;
                pprev->next = end_it.ptr;
                nnext->prev = start_it.ptr;
                start_it.ptr->next = nnext;
                end_it.ptr->prev = pprev;
                start_it.ptr->prev = end_it.ptr;
                end_it.ptr->next = start_it.ptr;
            }
            return;
        }
        list r = split(std::next(begin(), size() / 2));
        sort(comp);
        r.sort(comp);
        merge(r, comp);
    }
    void sort() { sort(std::less()); }

    // copy assignment
    list &operator=(const list &rhs) {
        // free original list
        for (node *it = m_head, *tmp; it != m_tail; it = tmp) {
            tmp = it->next;
            delete it;
        }
        delete m_tail;
        m_head = new node();
        m_tail = new node();
        m_head->next = m_tail;
        m_tail->prev = m_head;
        m_size = rhs.m_size;
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
        for (node *it = m_head, *tmp; it != m_tail; it = tmp) {
            tmp = it->next;
            delete it;
        }
        delete m_tail;
        m_head = new node();
        m_tail = new node();
        m_head->next = m_tail;
        m_tail->prev = m_head;
        m_size = rhs.m_size;
        // move
        if (this != &rhs) {
            m_head = rhs.m_head;
            m_tail = rhs.m_tail;
            rhs.m_head = rhs.m_tail = nullptr;
        }
        return *this;
    }

    list() : m_head(new node()), m_tail(new node()), m_size(0) {
        m_head->next = m_tail;
        m_tail->prev = m_head;
    }
    list(std::initializer_list<T> init)
        : m_head(new node()), m_tail(new node()), m_size(0) {
        m_head->next = m_tail;
        m_tail->prev = m_head;
        for (const auto &v : init) {
            emplace_back(v);
        }
    }

    // copy constructor
    list(const list &l) : m_head(new node()), m_tail(new node()), m_size(0) {
        m_head->next = m_tail;
        m_tail->prev = m_head;
        for (const auto &v : l) {
            emplace_back(v);
        }
    }

    // move constructor
    list(list &&l) : m_head(l.m_head), m_tail(l.m_tail), m_size(l.m_size) {
        l.m_head = l.m_tail = nullptr;
    }

    ~list() {
        for (node *it = m_head, *tmp; it != m_tail; it = tmp) {
            tmp = it->next;
            delete it;
        }
        delete m_tail;
    }
};
} // namespace mystl
