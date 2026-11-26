#pragma once

// Copyright 2026 Ryabov M

#include<stdexcept>

class Dsu {
    size_t* _data;
    size_t _size;
    size_t* _rank;
 public:

     explicit Dsu(size_t size);
     ~Dsu();
     void t_union(size_t first, size_t second);
     size_t find(size_t which);
};