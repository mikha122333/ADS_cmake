#pragma once
#include <iostream>
#include<cstdlib>
#include<utility>
#include "../lib_TVector/memdata.h"

// Copyright 2026 Ryabov M

template<typename vec_type>
class Vector {
    MemData<vec_type> _mem;
    size_t _front;
    size_t _back;
    size_t i_to_ri(size_t) const;

 public:
     explicit Vector(std::initializer_list<vec_type>);
     explicit Vector(size_t size = 0, const vec_type* data = nullptr);
     explicit Vector(const Vector<vec_type>&);
     explicit Vector(Vector<vec_type>&&);
    virtual ~Vector() = default;

    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;

    inline size_t size() const noexcept;
    inline size_t capacity() const noexcept;
    inline vec_type front() const;
    inline vec_type back() const;

    inline vec_type& front();
    inline vec_type& back();

    void push_front(vec_type) noexcept;
    void push_front_some(vec_type*, size_t) noexcept;
    void push_back(vec_type) noexcept;
    void push_back_some(vec_type*, size_t) noexcept;
    void insert(vec_type, size_t);
    void insert_some(vec_type*, size_t, size_t);
    void pop_front();
    void pop_back();
    void erase(size_t);
    void erase_some(size_t, size_t);


    template<typename ptr_type>
    class Iterator {
        ptr_type* _ptr = nullptr;
    public:
        Iterator() noexcept = default;
        explicit Iterator(ptr_type* p) noexcept : _ptr(p) {}

        ptr_type& operator*()  const { return *_ptr; }
        ptr_type* operator->() const { return _ptr; }

        Iterator& operator++() { ++_ptr; return *this; }
        Iterator  operator++(int) { Iterator t = *this; ++_ptr; return t; }
        Iterator& operator--() { --_ptr; return *this; }
        Iterator  operator--(int) { Iterator t = *this; --_ptr; return t; }

        bool operator==(const Iterator& o) const noexcept {
            return _ptr == o._ptr;
        }
        bool operator!=(const Iterator& o) const noexcept {
            return _ptr != o._ptr;
        }
    };

    typedef Iterator<vec_type>       iterator;
    typedef Iterator<const vec_type> const_iterator;

    iterator begin() noexcept { return iterator(_mem._data + _front); }
    iterator end()   noexcept {
        if (_mem._size == 0) return iterator(_mem._data);
        return iterator(_mem._data + _back + 1);
    }

    const_iterator begin() const noexcept {
        return const_iterator(_mem._data + _front);
    }
    const_iterator end()   const noexcept {
        if (_mem._size == 0) return const_iterator(_mem._data);
        return const_iterator(_mem._data + _back + 1);
    }

    iterator rbegin() noexcept {
        if (_mem._size == 0) return iterator(_mem._data);
        return iterator(_mem._data + _back);
    }
    iterator rend() noexcept { return iterator(_mem._data + _front - 1); }

    const_iterator rbegin() const noexcept {
        if (_mem._size == 0) return const_iterator(_mem._data);
        return const_iterator(_mem._data + _back);
    }
    const_iterator rend() const noexcept {
        return const_iterator(_mem._data + _front - 1);
    }
    Vector<vec_type>& operator=(const Vector<vec_type>&) noexcept;
    Vector<vec_type>& operator=(Vector<vec_type>&&) noexcept;

    vec_type operator[](size_t) const noexcept;
    vec_type& operator[](size_t) noexcept;

    friend std::ostream& 
        operator<< (std::ostream& out, const Vector<vec_type>& v1) {
        out << "{ ";
        if (v1._mem.size() != 0) {
            out << v1._mem.data()[v1._front];
        }
        for (size_t i = 1; i < v1._mem.size(); i++) {
            out << ", " << v1._mem.data()[v1.i_to_ri(i)];
        }
        out << " }";
        return out;
    }
    friend std::istream& operator>> (std::istream& in, Vector<vec_type>& v1) {
        Vector<vec_type> tmp;
        vec_type ch;
        in >> ch;
        while (in >> ch) {
            tmp.push_back(ch);
        }
        v1 = std::move(tmp);
        return in;
    }
    void shrink_to_fit() noexcept;
};
template<typename vec_type>
inline bool Vector<vec_type>::is_empty() const noexcept {
    return _mem.is_empty();
}
template<typename vec_type>
inline bool Vector<vec_type>::is_full() const noexcept {
    return _mem.is_full();
}
template<typename vec_type>
inline size_t Vector<vec_type>::size() const noexcept { return _mem._size; }
template<typename vec_type>
inline size_t Vector<vec_type>::capacity() const noexcept {
    return _mem._capacity;
}
template<typename vec_type>
inline vec_type Vector<vec_type>::front() const {
    if (_mem._size != 0)
        return (_mem._data)[_front];
    else throw std::logic_error("tried front when vector is empty");
}
template<typename vec_type>
inline vec_type Vector<vec_type>::back() const {
    if (_mem._size != 0)
        return (_mem._data)[_back];
    else throw std::logic_error("tried front when vector is empty");
}
template<typename vec_type>
inline vec_type& Vector<vec_type>::front() {
    if (_mem._size != 0)
        return (_mem._data)[_front];
    else throw std::logic_error("tried front when vector is empty");
}
template<typename vec_type>
inline vec_type& Vector<vec_type>::back() {
    if (_mem._size != 0)
        return (_mem._data)[_back];
    else throw std::logic_error("tried front when vector is empty");
}

template<typename vec_type>
size_t Vector<vec_type>::i_to_ri(size_t i) const {
    return ((i + _front) % _mem._capacity);
}
template<typename vec_type>
Vector<vec_type>::Vector(std::initializer_list<vec_type> li) {
    MemData<vec_type> tmp(li);
    _mem = std::move(tmp);
    _front = 0;
    if (_mem._size > 0)
        _back = _mem._size - 1;
    else
        _back = 0;
}
template<typename vec_type>
Vector<vec_type>::Vector(size_t size, const vec_type* data) {
    MemData<vec_type> tmp(size, data);
    _mem = (std::move(tmp));
    _front = 0;
    if (_mem._size > 0)
        _back = _mem._size - 1;
    else
        _back = 0;
}
template<typename vec_type>
Vector<vec_type>::Vector(const Vector<vec_type>& v1) {
    _mem = v1._mem;
    _front = v1._front;
    _back = v1._back;
}
template<typename vec_type>
Vector<vec_type>::Vector(Vector<vec_type>&& v1) {
    _mem = std::move(v1._mem);
    _front = v1._front;
    v1._front = 0;
    _back = v1._back;
    v1._back = 0;
}
template<typename vec_type>
Vector<vec_type>& 
Vector<vec_type>::operator=(const Vector<vec_type>& v1)noexcept {
    if (this != &v1) {
        _mem = v1._mem;
        _front = v1._front;
        _back = v1._back;
    }
    return(*this);
}
template<typename vec_type>
Vector<vec_type>& Vector<vec_type>::operator=(Vector<vec_type>&& v1) noexcept {
    if (this != &v1) {
        _mem = std::move(v1._mem);
        _front = v1._front;
        v1._front = 0;
        _back = v1._back;
        v1._back = 0;
    }
    return(*this);
}
template<typename vec_type>
void Vector<vec_type>::push_front(vec_type ch) noexcept {
    this->_mem._size++;
    if (this->_mem._size > 1)
        this->_front = (_front - 1 + _mem._capacity) % _mem._capacity;
    if ((*this).is_full()) {
        _mem.reset_memory(_mem._size);
        _front = 0;
        _back = _mem._size - 1;
    }
    _mem._data[_front] = ch;
}
template<typename vec_type>
void Vector<vec_type>::push_front_some(vec_type* ch, size_t size) noexcept {
    for (int i = size - 1; i >= 0; i--) {
        (*this).push_front(ch[i]);
    }
}
template<typename vec_type>
void Vector<vec_type>::pop_front() {
    if (this->_mem._size == 0)
        throw std::logic_error("trying to delete front in empty vector");
    else {
        this->_mem._size--;
        if (this->_mem._size != 0)
            _front = (_front + 1) % this->_mem._capacity;
        if (this->_mem._capacity - this->_mem._size > 2 * MEM_STEP) {
            this->_mem.reset_memory(this->_mem._size, this->_front);
            _front = 0;
            if (this->_mem._size != 0)
                _back = this->_mem._size - 1;
        }
    }
}
template<typename vec_type>
void Vector<vec_type>::push_back(vec_type ch) noexcept {
    this->_mem._size++;
    if (this->_mem._size > 1)
        this->_back = (_back + 1) % _mem._capacity;
    if ((*this).is_full()) {
        _mem.reset_memory(_mem._size);
        _front = 0;
        _back = _mem._size - 1;
    }
    _mem._data[_back] = ch;
}
template<typename vec_type>
void Vector<vec_type>::push_back_some(vec_type* ch, size_t size) noexcept {
    for (int i = 0; i < size; i++) {
        (*this).push_back(ch[i]);
    }
}
template<typename vec_type>
void Vector<vec_type>::pop_back() {
    if (this->_mem._size == 0)
        throw std::logic_error("trying to delete front in empty vector");
    else {
        this->_mem._size--;
        if (this->_mem._size != 0)
            _back = (_back - 1 + this->capacity()) % this->_mem._capacity;
        if (this->_mem._capacity - this->_mem._size > 2 * MEM_STEP) {
            this->_mem.reset_memory(this->_mem._size, this->_front);
            _front = 0;
            if (this->_mem._size != 0)
                _back = this->_mem._size - 1;
        }
    }
}
template<typename vec_type>
vec_type Vector<vec_type>::operator[](size_t i) const noexcept {
    if (i < this->_mem._size)
        return this->_mem._data[(*this).i_to_ri(i)];
    else throw std::logic_error("i go out of range");
}
template<typename vec_type>
vec_type& Vector<vec_type>::operator[](size_t i) noexcept {
    if (i < this->_mem._size)
        return this->_mem._data[(*this).i_to_ri(i)];
    else throw std::logic_error("i go out of range");
}
template<typename vec_type>
void Vector<vec_type>::insert(vec_type ch, size_t i) {
    if (i > (*this).size()) {
        throw std::logic_error("i is out of range");
    }else {
        if (i == 0) {
            (*this).push_front(ch);
        }else if (i == (*this).size()) {
            (*this).push_back(ch);
        }else {
            this->_mem._size++;
            this->_back = (this->_back + 1) % this->capacity();
            for (int i2 = _mem._size - 1; i2 > i; i2--) {
                (*this)[i2] = (*this)[i2 - 1];
            }
            (*this)[i] = ch;
            if ((*this).is_full()) {
                _mem.reset_memory(_mem._size);
                _front = 0;
                _back = _mem._size - 1;
            }
        }
    }
}
template<typename vec_type>
void Vector<vec_type>::insert_some(vec_type* ch, size_t size, size_t place) {
    if (place > this->_mem._size) {
        throw std::logic_error("place is out of range");
    }else {
        for (int i = 0; i < size; i++) {
            (*this).insert(ch[i], place + i);
        }
    }
}
template<typename vec_type>
void Vector<vec_type>::erase(size_t i) {
    if (i >= (*this).size()) {
        throw std::logic_error("i is out of range");
    }else {
        if (i == 0) {
            (*this).pop_front();
        }else if (i == (*this).size() - 1) {
            (*this).pop_back();
        }else {
            this->_back =
                (this->_back - 1 + this->capacity()) % this->capacity();
            for (int i2 = i; i2 < this->_mem._size - 1; i2++) {
                (*this)[i2] = (*this)[i2 + 1];
            }
            this->_mem._size--;
            if (this->_mem._capacity - this->_mem._size > 2 * MEM_STEP) {
                this->_mem.reset_memory(this->_mem._size, this->_front);
                _front = 0;
                _back = this->_mem._size - 1;
            }
        }
    }
}
template<typename vec_type>
void Vector<vec_type>::erase_some(size_t place, size_t count) {
    if (count > (*this).size() || place > ((*this).size() - count)) {
        throw std::logic_error("trying to delete alot more than can");
    }
    for (int i = 0; i < count; i++) {
        (*this).erase(place);
    }
}
template<typename vec_type>
void Vector<vec_type>::shrink_to_fit()noexcept {
    this->_mem.shrink_to_fit(_front);
    _front = 0;
    _back = _mem._size - 1;
}
