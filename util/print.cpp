/*
 * Python-style variadic print() functions.
 * 
 * By default prints to stdout; stream can be specified as the first argument.
 * Separator and line ending can be specified as template parameters (single char only).
 */
#include <iostream>

template<char Sep = ' ', char End = '\n', typename First, typename ...Args>
void print(const First &first, const Args &...args) {
    std::cout << first;
    ((std::cout << Sep << args), ...);
    std::cout << End;
}

template <char Sep = ' ', char End = '\n'>
void print() {
    std::cout << End;
}

template<char Sep = ' ', char End = '\n', typename First, typename ...Args>
void print(std::ostream &s, const First &first, const Args &...args) {
    s << first;
    ((s << Sep << args), ...);
    s << End;
}

template <char Sep = ' ', char End = '\n'>
void print(std::ostream &s) {
    s << End;
}
