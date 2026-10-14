#pragma once
#include <initializer_list>

#define MEM_STEP 15

template<typename vec_type>
class Vector;

template<typename vec_type>
class MemData {
    vec_type* _data;
    size_t _size;
    size_t _capacity;

    void shrink_to_fit(size_t start_index = 0)noexcept;
public:
    MemData(size_t size = 0, const vec_type* data = nullptr);
    MemData(std::initializer_list<vec_type>);          
    MemData(const MemData&);
    MemData(MemData&&);
    ~MemData();

    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;

    inline size_t size() const noexcept;             
    inline size_t capacity() const noexcept;         
    inline const vec_type* const data() const noexcept; 

    void set_memory(size_t) noexcept;                   
    void reset_memory(size_t size, size_t start_index = 0) noexcept;          
    void clear_memory() noexcept;                                             

    MemData<vec_type>& operator=(const MemData<vec_type>&) noexcept;         
    MemData<vec_type>& operator=(MemData<vec_type>&&) noexcept;              

    friend class Vector<vec_type>;
};
template<typename vec_type>
inline bool MemData<vec_type>::is_empty() const noexcept {
    if (_size == 0)
        return 1;
    else return 0;
}
template<typename vec_type>
inline bool MemData<vec_type>::is_full() const noexcept {
    if (_size >= _capacity)
        return 1;
    else return 0;
}
template<typename vec_type>
inline size_t MemData<vec_type>::size() const noexcept { return _size; }
template<typename vec_type>
inline size_t MemData<vec_type>::capacity() const noexcept { return _capacity; }
template<typename vec_type>
inline const vec_type* const MemData<vec_type>::data() const noexcept { return _data; }

template<typename vec_type>
MemData<vec_type>::MemData(std::initializer_list<vec_type> data) {
    _size = data.size();
    _capacity = _size + MEM_STEP - 1;
    _data = new vec_type[_capacity];
    int i = 0;
    for (vec_type dig : data) {
        _data[i] = vec_type(dig);
        i++;
    }
}
template<typename vec_type>
MemData<vec_type>::MemData(size_t size, const vec_type* data) {
    _size = size;
    _capacity = size + MEM_STEP - 1;
    _data = new vec_type[_capacity];
    if (data != nullptr) {
        for (int i = 0; i < _size; i++) {
            _data[i] = data[i];
        }
    }
    else {
        for (int i = 0; i < _size; i++) {
            _data[i] = vec_type();
        }
    }
}
template<typename vec_type>
MemData<vec_type>::MemData(const MemData& m1) {
    this->_size = m1._size;
    this->_capacity = m1._capacity;
    this->_data = new vec_type[this->_capacity];
    for (int i = 0; i < this->_size; i++) {
        this->_data[i] = m1._data[i];
    }
}
template<typename vec_type>
MemData<vec_type>::MemData(MemData&& m1) {
    this->_size = m1._size;
    this->_capacity = m1._capacity;
    this->_data = m1._data;
    m1._data = nullptr;
    m1._size = 0;
    m1._capacity = 0;
}
template<typename vec_type>
MemData<vec_type>::~MemData() {
    if (_data != nullptr)
        delete[]_data;
}
template<typename vec_type>
void MemData<vec_type>::set_memory(size_t size) noexcept {
    if (_data != nullptr)
        delete[]_data;
    _size = size;
    _capacity = _size + MEM_STEP - 1;
    _data = new vec_type[_capacity];
}
template<typename vec_type>
void MemData<vec_type>::reset_memory(size_t size, size_t start_index) noexcept {
    size_t start_capacity = _capacity;
    size_t copy_size = _size;
    _size = size;
    _capacity = _size + MEM_STEP - 1;
    vec_type* tmp = new vec_type[_capacity];
    if (copy_size > _size) { copy_size = copy_size % _size; }
    for (int i = 0; i < copy_size; i++) {
        tmp[i] = _data[(i + start_index) % start_capacity];
    }
    if (_data != nullptr)
        delete[]_data;
    _data = tmp;
}
template<typename vec_type>
void MemData<vec_type>::clear_memory() noexcept {
    if (_data != nullptr)
        delete[]_data;
    _data = nullptr;
    _size = 0;
    _capacity = 0;
}
template<typename vec_type>
MemData<vec_type>& MemData<vec_type>::operator=(const MemData& m1) noexcept {
    if (this != &m1) {
        if (_data != nullptr)
            delete[]_data;
        this->_data = new vec_type[m1._capacity];
        this->_size = m1._size;
        this->_capacity = m1._capacity;
        for (int i = 0; i < _capacity; i++) {
            this->_data[i] = m1._data[i];
        }
    }
    return(*this);
}
template<typename vec_type>
MemData<vec_type>& MemData<vec_type>::operator=(MemData&& m1) noexcept {
    if (this != &m1) {
        if (_data != nullptr)
            delete[]_data;
        this->_data = m1._data;
        this->_capacity = m1._capacity;
        this->_size = m1._size;
        m1._data = nullptr;
        m1._size = 0;
        m1._capacity = 0;
    }
    return(*this);
}
template<typename vec_type>
void MemData<vec_type>::shrink_to_fit(size_t start_index)noexcept {
    (*this).reset_memory(_size, start_index);
    size_t old_capacity = _capacity;
    _capacity = _size;
    vec_type* tmp;
    if (_size != 0)
        tmp = new vec_type[_capacity];
    else
        tmp = nullptr;
    for (int i = 0; i < _size; i++) {
        tmp[i] = _data[i];
    }
    if (_data != nullptr)
        delete[]_data;
    _data = tmp;
}