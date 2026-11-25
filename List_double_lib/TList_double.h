#pragma once

// Copyright 2026 Ryabov M

#include<stdexcept>
template<typename t>
struct Node {
    t _data;
    Node* _next;
    Node* _prev;
    explicit Node(const t& data, Node* next = nullptr, Node* prev = nullptr) {
        _data = data;
        _next = next;
        _prev = prev;
    }
    Node(const Node& other) = default;
    Node(Node&& other) = default;
};
template<typename t>
class List_double {
    Node<t>* _first;
    Node<t>* _last;
    size_t _size;
    bool is_node_exist(Node<t>* some)const noexcept;

 public:
    List_double();

    ~List_double();

    Node<t>* push_front(const t& data)noexcept;
    Node<t>* push_back(const t& data)noexcept;
    Node<t>* insert(const t& data, size_t size);
    void insert(const t& data, Node<t>* where);

    template<typename it>
    class Iterator {
        it* _here = nullptr;

     public:
        Iterator()noexcept = default;
        explicit Iterator(it* other)noexcept :_here(other) {}

        void operator =(const Iterator& other) { _here = other._here; }

        t& operator*() noexcept { return _here->_data; }

        Iterator& operator++() {
            if (_here == nullptr)throw std::out_of_range("iter oof");
            _here = (*_here)._next;
            return (*this);
        }
        Iterator operator++(int) {
            if (_here == nullptr)throw std::out_of_range("iter oof");
            Iterator res(_here);
            _here = (*_here)._next;
            return res;
        }
        Iterator& operator+=(size_t num) {
            Iterator tmp(this->_here);
            int i = 0;
            for (; i < num; i++) {
                (tmp)++;
            }
            (*this) = tmp;
            return(*this);
        }
        Iterator operator+(size_t num) {
            Iterator tmp(_here);
            tmp += num;
            return tmp;
        }

        Iterator& operator--() {
            if (_here==nullptr||_here->_prev == nullptr)throw std::out_of_range("iter oof");
            _here = (*_here)._prev;
            return (*this);
        }
        Iterator operator--(int) {
            if (_here == nullptr || _here->_prev == nullptr)throw std::out_of_range("iter oof");
            Iterator res(_here);
            _here = (*_here)._prev;
            return res;
        }
        Iterator& operator-=(size_t num) {
            Iterator tmp(this->_here);
            int i = 0;
            for (; i < num; i++) {
                (tmp)--;
            }
            (*this) = tmp;
            return(*this);
        }
        Iterator operator-(size_t num) {
            Iterator tmp(_here);
            tmp -= num;
            return tmp;
        }

        bool operator ==(const Iterator& other)const noexcept {
            return _here == other._here;
        }
        bool operator !=(const Iterator& other)const noexcept {
            return _here != other._here;
        }
    };

    typedef Iterator<Node<t>> iterator;
    typedef Iterator<Node<const t>> const_iterator;

    iterator begin()  noexcept {
        return iterator(_first);
    }
    const_iterator begin() const noexcept {
        return const_iterator(_first);
    }
    iterator end() noexcept {
        return iterator(nullptr);
    }
    const_iterator end()const noexcept {
        return const_iterator(nullptr);
    }

    t pop_back();
    t pop_front();
    t erase(size_t num);
    t erase(Node<t>* nod);

    Node<t>* find(const t& elem)const noexcept;
    inline size_t size()const noexcept { return _size; }
    inline bool is_empty()const noexcept { return _size == 0; }
};
template<typename t>
bool List_double<t>::is_node_exist(Node<t>* some)const noexcept {
    if (is_empty()) return 0;
    Node<t>* tmp = _first;
    bool res = 0;
    if (tmp == some) res = 1;
    for (int i = 1; i < _size && !res; i++) {
        tmp = tmp->_next;
        res = (tmp == some);
    }
    return res;
}
template<typename t>
List_double<t>::List_double() {
    _first = nullptr;
    _last = nullptr;
    _size = 0;
}
template<typename t>
List_double<t>::~List_double() {
    for (int i = 0; i < _size; i++) {
        pop_front();
    }
}
template<typename t>
Node<t>* List_double<t>::push_front(const t& data)noexcept {
    Node<t>* tmp = new Node<t>(data, _first);
    if (is_empty()) {
        _last = tmp;
    } else {
        _first->_prev = tmp;
    }
    _first = tmp;
    _size++;
    return _first;
}
template<typename t>
Node<t>* List_double<t>::push_back(const t& data)noexcept {
    Node<t>* tmp = new Node<t>(data);
    if (is_empty()) {
        _first = tmp;
    } else {
        _last->_next = tmp;
        tmp->_prev = _last;
    }
    _last = tmp;
    _size++;
    return _last;
}
template<typename t>
Node<t>* List_double<t>::insert(const t& data, size_t size) {
    if (size > _size)throw std::out_of_range("ins o.o.r.");
    Node<t>* res;
    if (is_empty() || size == 0) {
        res = push_front(data);
    } else if (size == _size) {
        res = push_back(data);
    } else {
        Node<t>* next = _first;
        Node<t>* prev;
        for (int i = 0; i < size; i++) {
            prev = next;
            next = next->_next;
        }
        Node<t>* new_nod = new Node<t>(data, next, prev);
        next->_prev = new_nod;
        prev->_next = new_nod;
        _size++;
        res = new_nod;
    }
    return res;
}
template<typename t>
void List_double<t>::insert(const t& data, Node<t>* where) {
    if (!is_node_exist(where)) throw std::logic_error("list dontcontain nod");
    Node<t>* res = new Node<t>(data, where->_next, where);
    if (where == _last) _last = res;
    else where->_next->_prev = res;
    where->_next = res;
    _size++;
}
template<typename t>
t List_double<t>::pop_front() {
    if (is_empty())throw std::logic_error("err pop_front");
    t res = _first->_data;
    Node<t>* new_first = nullptr;
    if (_size >= 2) {
        new_first = _first->_next;
        new_first->_prev = nullptr;
    } else {
        _last = nullptr;
    }
    delete _first;
    _first = new_first;
    _size--;
    return res;
}
template<typename t>
t List_double<t>::pop_back() {
    if (is_empty())throw std::logic_error("err pop_back");
    t res = _last->_data;
    if (_size == 1) {
        pop_front();
    } else {
        Node<t>* new_last = _last->_prev;
        delete _last;
        _last = new_last;
        _last->_next = nullptr;
        _size--;
    }
    return res;
}
template<typename t>
t List_double<t>::erase(size_t num) {
    if (num >= _size || is_empty()) throw std::out_of_range("err in erase");
    t res;
    if (num == 0 || _size == 1) {
        res = pop_front();
    } else if (num == _size - 1) {
        res = pop_back();
    } else {
        Node<t>* prev = _first;
        for (int i = 1; i < num; i++) {
            prev = prev->_next;
        }
        Node<t>* tmp_to_del = prev->_next;
        res = tmp_to_del->_data;
        prev->_next = tmp_to_del->_next;
        tmp_to_del->_next->_prev = prev;
        delete tmp_to_del;
        _size--;
    }
    return res;
}
template<typename t>
t List_double<t>::erase(Node<t>* nod) {
    if (!is_node_exist(nod)) throw std::logic_error("list dontcontain nod");
    t res = nod->_data;
    if (nod == _first || _size == 1) {
        pop_front();
    } else if (nod == _last) {
        pop_back();
    } else {
        nod->_prev->_next = nod->_next;
        nod->_next->_prev = nod->_prev;
        delete nod;
        _size--;
    }
    return res;
}
template<typename t>
Node<t>* List_double<t>::find(const t& elem)const noexcept {
    if (is_empty())return nullptr;
    Node<t>* res = _first;
    bool is_found = 0;
    if (res->_data == elem)
        is_found = 1;
    for (int i = 1; i < _size && !is_found; i++) {
        res = res->_next;
        is_found = res->_data == elem;
    }
    if (is_found)
        return res;
    else
        return nullptr;
}
