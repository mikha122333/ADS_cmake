
// Copyright 2026 Ryabov M

#include"../Dsu_lib/Dsu_lib.h"

Dsu::Dsu(size_t size) {
    if (size == 0) throw std::logic_error("size==0 in cons");
    _size = size;
    _data = new size_t[_size];
    _rank = new size_t[_size];
    for (size_t i = 0; i < _size; i++) {
        _data[i] = i;
        _rank[i] = 0;
    }
}

Dsu::~Dsu() {
    delete[] _data;
    delete[] _rank;
}

size_t Dsu::find(size_t which) {
    if (which == 0 || which > _size)
        throw std::out_of_range("which is bad in find");
    which--;
    if (_data[which] == which) {
        return which+1;
    } else {
        size_t tmp = find(_data[which]+1)-1;
        _data[which] = tmp;
        return tmp+1;
    }
}

void Dsu::t_union(size_t first, size_t second) {
    if (first == 0 || first > _size || second == 0 || second > _size)
        throw std::out_of_range("err in union");
    if (first == second)
        return;
    first--;
    second--;
    size_t t_1 = find(first + 1)-1, t_2 = find(second + 1)-1;
    if (_rank[t_1] >= _rank[t_2]) {
        _rank[t_1] += _rank[t_1] == _rank[t_2];
        _data[t_2] = t_1;
    } else {
        _data[t_1] = t_2;
    }
}
