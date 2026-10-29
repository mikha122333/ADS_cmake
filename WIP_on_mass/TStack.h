// Copyright 2026 Ryabov M

#include <stdexcept>
template <typename data_type>
class Stack {
    data_type* _data;
    size_t _size;
    size_t _top;
 public:
     Stack(size_t size);
     Stack(const Stack& other);
     ~Stack();

     void push(const data_type& some);
     data_type pop();
     data_type& top();

     inline bool is_empty()const noexcept { return (_top == 0); }
     inline bool is_full()const noexcept { return (_top == _size); }
};
template<typename data_type>
Stack<data_type>::Stack(size_t size) {
    if (size <= 0)
        throw std::out_of_range("inapropriate size for Stack");
    _data = new data_type[size];
    _size = size;
    _top = 0;
}
template<typename data_type>
Stack<data_type>::Stack(const Stack& other) {
    _size = other._size;
    _data = new data_type[_size];
    _top = other._top;
    for (int i = 0; i <= _top; i++) {
        _data[i] = other._data[i];
    }
}
template<typename data_type>
Stack<data_type>::~Stack() {
    delete[]_data;
}
template<typename data_type>
void Stack<data_type>::push(const data_type& some) {
    if (is_full())
        throw std::out_of_range("trying to add to full stack");
    _top++;
    _data[_top - 1] = some;
}
template<typename data_type>
data_type Stack<data_type>::pop() {
    if (is_empty())
        throw std::out_of_range("trying to pop from empty stack");
    _top--;
    return _data[_top];
}
template<typename data_type>
data_type& Stack<data_type>::top() {
    if (is_empty())
        throw std::out_of_range("tryitng get top, when stack is empty");
    return _data[_top - 1];
}