// Copyright 2026 Ryabov M

#include <stdexcept>
#include "../lib_easy_example/easy_example.h"

float division(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("Input Error: can't divide by zero!");
    }
    return static_cast<float>(a) / b;
}

bool check_breckets(std::string expressiion) {
    Stack<char> st(expressiion.length());
    for (int i = 0; i < expressiion.length(); i++) {
        try {
            if (expressiion[i] == '(' ||
                expressiion[i] == '[' ||
                expressiion[i] == '{') {
                st.push(expressiion[i]);
            }
            else if (expressiion[i] == ')' && st.top() == '(') {
                st.pop();
            }
            else if (expressiion[i] == ']' && st.top() == '[') {
                st.pop();
            }
            else if (expressiion[i] == '}' && st.top() == '{') {
                st.pop();
            }
        } catch (...) {
            return false;
        }
    }
    return(st.is_empty());
}