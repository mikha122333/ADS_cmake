#pragma once

// Copyright 2026 Ryabov M

#include<stdexcept>
template<typename t>
struct Node{
    t _data;
    Node* _next;
    explicit Node(const t& data, Node* next = nullptr) { _data(data); _next(next); }
    Node(const Node& other) = default;
    Node(Node&& other) = default;
};
template<typename t>
class List{
    Node<t>* _first;
    Node<t>* _last;
    size_t _size;
    bool is_node_exist(Node<t>* some)const noexcept;
 public:
     List();

     ~List();

     Node<t>* push_front(const t& data)noexcept;
     Node<t>* push_back(const t& data)noexcept;
     Node<t>* insert(const t& data, size_t size);
     void insert(const t& data, Node<t>* where);

     t pop_back();
     t pop_front();
     t erase(size_t num);
     t erase(Node<t>* nod);

     Node<t>* find(const t& elem)const noexcept;
     inline size_t size()const noexcept { return _size; }
     inline bool is_empty()const noexcept {return _size == 0; }
};
template<typename t>
bool List<t>::is_node_exist(Node<t>* some)const noexcept {
    if (is_empty()) return 0;
    Node<t>* tmp = _first;
    bool res = 0;
    if (tmp == some) res = 1;
    for (int i = 1; i < _size&&!res; i++) {
        tmp = tmp->_next;
        res = (tmp == some);
    }
    return res;
}
template<typename t>
List<t>::List() {
    _first = nullptr;
    _last = nullptr;
    _size = 0;
}
template<typename t>
List<t>::~List() {
    for (int i = 0; i < _size; i++) {
        pop_front();
    }
}
template<typename t>
Node<t>* List<t>::push_front(const t& data)noexcept {
    Node<t>* tmp = new Node<t>(data, _first);
    if (is_empty()) _last = tmp;
    _first = tmp;
    _size++;
    return _first;
}
template<typename t>
Node<t>* List<t>::push_back(const t& data)noexcept {
    Node<t>* tmp = new Node<t>(data, _first);
    if (is_empty()) _first = tmp;
    _last = tmp;
    _size++;
    return _last;
}
template<typename t>
Node<t>* List<t>::insert(const t& data, size_t size) {
    if (size > _size)throw std::out_of_range("ins o.o.r.");
    Node<t>* res;
    if (is_empty() || size == 0) {
        res = push_front(data);
    } else if (size == _size) {
        res = push_back(data);
    } else {
        Node<t>* next = _first;
        Node<t>* prev;
        for (int i = 1; i < size; i++) {
            prev = next;
            next = next->_next;
        }
        Node<t>* new_nod = new Node<t>(data, next);
        prev->_next = new_nod;
        _size++;
        res = new_nod;
    }
    return res;
}
template<typename t>
void List<t>::insert(const t& data, Node<t>* where) {
    if (!is_node_exist(where)) throw std::logic_error("list dontcontain nod");
    Node<t>* res = new Node<t>(data, where->_next);
    where->_next = res;
    _size++;
}
template<typename t>
t List<t>::pop_front() {
    if (is_empty())throw std::logic_error("err pop_front");
    t res = _first->_data;
    Node<t>* new_first = nullptr;
    if (_size >= 2) new_first = _first->_next;
    delete _first;
    _first = new_first;
    if (_size == 1) _last = nullptr;
    _size--;
    return res;
}
template<typename t>
t List<t>::pop_back() {
    if (is_empty())throw std::logic_error("err pop_front");
    t res = _last->_data;
    if (_size == 1) {
        pop_front();
    } else {
        Node<t>* new_last = _first;
        for (int i = 1; i < _size - 1; i++) {
            new_last = new_last->_next;
        }
        delete _last;
        _last = new_last;
        _size--;
    }
    return res;
}
template<typename t>
t List<t>::erase(size_t num) {
    if (num >= _size || is_empty()) throw std::out_of_range("err in erase");
    Node<t>* prev = _first;
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
        delete tmp_to_del
    }
    return res;
}
template<typename t>
t List<t>::erase(Node<t>* nod) {
    if (!is_node_exist(nod)) throw std::logic_error("list dontcontain nod");
    t res = nod->_data;
    if (nod == _first || _size == 1) {
        pop_front();
    } else if (nod = _last) {
        pop_back();
    } else {
        Node<t>* prev = _first;
        for (int i = 1; prev->_next != nod; i++) {
            prev = prev->_next;
        }
        prev->_next = nod->_next;
        delete nod
    }
    return res;
}
template<typename t>
Node<t>* List<t>::find(const t& elem)const noexcept {
    if (is_empty())throw nullptr;
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
