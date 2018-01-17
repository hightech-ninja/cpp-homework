#ifndef PERSISTENT_SET_H
#define PERSISTENT_SET_H

#include <cstddef> // for size_t, nullptr
#include <utility> // for swap

namespace bezborodov {

namespace pointers {

template<typename T>
class shared_ptr {
    size_t* counter_;
    T* ptr_;
public:
    constexpr shared_ptr() noexcept;
    shared_ptr(shared_ptr<T> const &) noexcept;
    shared_ptr(shared_ptr<T> &&) noexcept;
    shared_ptr<T>& operator =(shared_ptr<T> const &) noexcept;
    shared_ptr<T>& operator =(shared_ptr<T> &&) noexcept;
    ~shared_ptr() noexcept;

    explicit shared_ptr(T*) noexcept;
    T* operator ->() const noexcept;
    T& operator*() const noexcept;

    T* get() const noexcept;
    void reset(T*) noexcept;
    void swap(shared_ptr<T> &) noexcept;

    template<typename U>
    friend void swap(shared_ptr<U> &, shared_ptr<U> &) noexcept;
};

template<typename T>
class linked_ptr
{
    linked_ptr* left_;
    linked_ptr* right_;
    T* ptr_;
public:
    constexpr linked_ptr() noexcept;
    linked_ptr(linked_ptr<T> const &) noexcept;
    linked_ptr(linked_ptr<T> &&) noexcept;
    linked_ptr<T>& operator =(linked_ptr<T> const &) noexcept;
    linked_ptr<T>& operator =(linked_ptr<T> &&) noexcept;
    ~linked_ptr() noexcept;

    extern linked_ptr(T*) noexcept;
    T* operator ->() const noexcept;
    T& operator*() const noexcept;

    T* get() const noexcept;
    void reset(T*) noexcept;

    template<typename U>
    friend void swap(linked_ptr<U> &, linked_ptr<U> &) noexcept;
};

} // pointers namespace

} // bezborodov namespace

#endif // PERSISTENT_SET_H
