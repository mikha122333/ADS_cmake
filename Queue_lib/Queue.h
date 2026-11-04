#pragma once

// Copyright 2026 Ryabov M

#include <stdexcept>

template<class t>
class Queue {
    size_t _count;
    size_t _size;
    t* _data;
    size_t _front;
    size_t _back;
    size_t i_to_real_i(size_t i)const;

 public:
     explicit Queue(size_t size);
     Queue(const Queue& other);
     ~Queue();
     inline size_t size()const noexcept { return _size; }
     inline t& front() {
         if (is_empty()) throw std::logic_error("fr wne no fr");
         return _data[_front];
     }

     inline bool is_full() const noexcept { return _count == _size; }
     inline bool is_empty()const noexcept { return _count == 0; }
     void push(const t& el);
     t pop();
};
template<class t>
size_t Queue<t>::i_to_real_i(size_t i)const {
    if (i >= _size) throw std::out_of_range("out of range while i to r i");
    return(_back + i) % _size;
}
template<class t>
Queue<t>::Queue(size_t size) {
    _size = size;
    _count = 0;
    _data = new t[_size];
    _front = 0;
    _back = 0;
}
template<class t>
Queue<t>::Queue(const Queue<t>& other) {
    _count = other._count;
    _size = other._size;
    _front = other._front;
    _back = other._back;
    _data = new t[_size];
    for (size_t i = 0; i < _count; i++) {
        _data[i_to_real_i(i)] = other._data[i_to_real_i(i)];
    }
}
template<class t>
Queue<t>::~Queue() { delete[]_data;}
template<class t>
void Queue<t>::push(const t& el) {
    if (is_full()) throw std::logic_error("trying push to full Queue");
    if(!is_empty())
        _back = (_back+(_size-1)) % _size;
    _count++;
    _data[i_to_real_i(0)] = el;
}
template<class t>
t Queue<t>::pop() {
    if (is_empty())throw std::logic_error("tried pop empty queue");
    t res = _data[_front];
    if(_count != 1)
        _front = (_front + (_size - 1)) % _size;
    _count--;
    return res;
}
