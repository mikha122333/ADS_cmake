// Copyright 2026 Ryabov M
#pragma once
#include<stdexcept>
#include<set>

template<typename st>
class multiset {
    size_t _amount;
    size_t _size;
    st* _data;
    int* _tops;
    size_t* _firsts;
    size_t* _lasts;

    size_t amount_of_empty(size_t set)const;
    size_t amount_of_elements(size_t set)const;
    void repackage(size_t prior_set);

 public:
     explicit multiset(size_t size, size_t amount = 1);
     multiset(const multiset& other);

     ~multiset();

     st& top(size_t set);
     st pop(size_t set);
     void push(size_t set, const st& data);

     bool is_empty(size_t set)const;
     bool is_empty()const noexcept;
     bool is_full(size_t set)const;
     bool is_full()const noexcept;
};

template<typename st>
size_t multiset<st>::amount_of_empty(size_t set) const {
    if (set >= _amount)throw std::out_of_range("err w empt for set");
    return(_lasts[set] - _tops[set]);
}
template<typename st>
size_t multiset<st>::amount_of_elements(size_t set) const {
    if (set >= _amount)throw std::out_of_range("err w elem for set");
    return(_tops[set]-_firsts[set]+1);
}
template<typename st>
void multiset<st>::repackage(size_t prior_set) {
    if (prior_set >= _amount) throw std::out_of_range("re w wrong set num");
    if (is_full()) throw std::logic_error("trying repack full mst");
    bool is_any_nonecessary_empty = 0;
    for (size_t i = 0; i < _amount&&(!is_any_nonecessary_empty); i++) {
        if (amount_of_empty(i) > 0 && _firsts[i] != _lasts[i])
            is_any_nonecessary_empty = 1;
    }
    if (!is_any_nonecessary_empty)
        throw std::logic_error("all emptyness used by other sets");
    st* res = new st[_size];
    size_t empt_c = 0, elem_c = 0;
    size_t* elem = new size_t[_amount];
    size_t* empt = new size_t[_amount];
    size_t *r_firsts = new size_t[_amount];
    size_t* r_lasts = new size_t[_amount];
    int* r_tops = new int[_amount];
    for (size_t i = 0; i < _amount; i++) {
        empt[i] = 0;
        elem[i] = amount_of_elements(i);
        empt_c += amount_of_empty(i);
        elem_c+= amount_of_elements(i);
    }
    empt[prior_set] = 1;
    empt_c--;
    size_t tmp = 0;
    for (size_t i = 0; i < _amount && (empt_c > 0); i++) {
        if (elem[i] == 0&&i != prior_set) {
            empt[i] += 1;
            empt_c--;
        }
    }
    for (size_t i = 0; i < _amount&&(empt_c > 0); i++) {
        if (!(elem[i] == 0)) {
            tmp = static_cast<size_t>(
                (static_cast<double>(elem[i]) / elem_c) *
                (static_cast<double>empt_c));
            empt[i] += tmp;
            empt_c -= tmp;
        }
    }
    if (empt_c != 0) {
        empt[prior_set] += empt_c;
    }
    int end = -1;
    for (size_t i = 0; i < _amount; i++) {
        r_firsts[i] = end+1;
        r_lasts[i] = r_firsts[i] + empt[i] + elem[i] - 1;
        r_tops[i] = r_firsts[i] + elem[i] - 1;
        for (size_t i2 = 0; i2 <elem[i]; i2++) {
            res[r_tops[i] - i2] = pop(i);
        }
        end = r_lasts[i];
    }
    delete[] _data;
    delete[] _lasts;
    delete[] _tops;
    delete[] _firsts;
    _data = res;
    _lasts = r_lasts;
    _firsts = r_firsts;
    _tops = r_tops;
    delete[] elem;
    delete[] empt;
}
template<typename st>
multiset<st>::multiset(size_t size, size_t amount) {
    if (amount > size || (amount == 0))
        throw std::logic_error("tryitng to create strange multiset");
    _data = new st[size];
    _tops = new int[amount];
    _firsts = new size_t[amount];
    _lasts = new size_t[amount];
    size_t tmp_am = amount;
    size_t tmp_sz = size;
    int end = -1;
    for (int i = 0; i < amount; i++) {
        _firsts[i] = end + 1;
        _tops[i] = end;
        end += tmp_sz / tmp_am;
        tmp_sz -= (tmp_sz / tmp_am);
        tmp_am--;
        _lasts[i] = end;
    }
    _amount = amount;
    _size = size;
}
template<typename st>
multiset<st>::multiset(const multiset& other) {
    _data = new st[other._size];
    _tops = new int[other._amount];
    _firsts = new size_t[other._amount];
    _lasts = new size_t[other._amount];
    _size = other._size;
    _amount = other._amount;
    for (int i = 0; i < _size; i++) {
        _data[i] = other._data[i];
    }
    for (int i = 0; i < _amount; i++) {
        _tops[i] = other._tops[i];
        _firsts[i] = other._firsts[i];
        _lasts[i] = other._lasts[i];
    }
}
template<typename st>
multiset<st>::~multiset() {
    delete[] _tops;
    delete[] _firsts;
    delete[] _lasts;
    delete[] _data;
}
template<typename st>
st& multiset<st>::top(size_t set) {
    if (set >= _amount || is_empty(set))
        throw std::out_of_range("err with top");
    return _data[_tops[set]];
}
template<typename st>
st multiset<st>::pop(size_t set) {
    if (set >= _amount || is_empty(set))
        throw std::out_of_range("err with pop");
    st res = _data[_tops[set]];
    _tops[set]--;
    return res;
}
template<typename st>
void multiset<st>::push(size_t set, const st& data) {
    if (set >= _amount)
        throw std::out_of_range("err with push");
    if (is_full(set)) {
        repackage(set);
    }
    if (is_full(set)) throw std::logic_error("no free space");
    _tops[set]++;
    _data[_tops[set]] = data;
}
template<typename st>
bool multiset<st>::is_empty(size_t set)const {
    if (set >= _amount)throw std::out_of_range("err w empty");
    return (_tops[set] == _firsts[set]-1);
}
template<typename st>
bool multiset<st>::is_empty()const noexcept {
    bool res = 1;
    for (size_t i = 0; i < _amount&&res; i++) {
        if (!is_empty(i))
            res = 0;
    }
    return res;
}
template<typename st>
bool multiset<st>::is_full(size_t set)const {
    if (set >= _amount)throw std::out_of_range("err w full");
    return(_tops[set] == _lasts[set]);
}
template<typename st>
bool multiset<st>::is_full()const noexcept {
    bool res = 1;
    for (size_t i = 0; i < _amount && res; i++) {
        if (!is_full(i))
            res = 0;
    }
    return res;
}
