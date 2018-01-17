#ifndef PERSISTENT_SET_H
#define PERSISTENT_SET_H

#include <cstddef>  // for size_t, nullptr
#include <utility>  // for swap
#include <iostream> // for cerr

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

    explicit shared_ptr(T*);
    T* operator ->() const noexcept;
    T& operator*() const noexcept;

    T* get() const noexcept;
    void reset(T*) noexcept;
    size_t count() const noexcept;
    void swap(shared_ptr<T> &) noexcept;

    template<typename U>
    friend void swap(shared_ptr<U> &, shared_ptr<U> &) noexcept;
};

template<typename T>
constexpr shared_ptr<T>::shared_ptr() noexcept
    : counter_(nullptr), ptr_(nullptr)
{}

template<typename T>
inline shared_ptr<T>::shared_ptr(const shared_ptr<T> & other) noexcept
    : counter_(other.counter_), ptr_(other.ptr_)
{
    if (counter_) {
        ++*counter_;
    }
}

template<typename T>
inline shared_ptr<T>::shared_ptr(shared_ptr<T> && other) noexcept
    : shared_ptr()
{
    swap(other);
}

template<typename T>
inline shared_ptr<T>& shared_ptr<T>::operator =(shared_ptr<T> const & other) noexcept
{
    shared_ptr<T> temp(other);
    swap(temp);
    return *this;
}

template<typename T>
inline shared_ptr<T>& shared_ptr<T>::operator =(shared_ptr<T> && other) noexcept
{
    swap(other);
    return *this;
}

template<typename T>
inline shared_ptr<T>::shared_ptr(T * ptr)
    : counter_(nullptr), ptr_(ptr)
{
    if (ptr_) {
        counter_ = new size_t(1);
    }
}

template<typename T>
inline shared_ptr<T>::~shared_ptr() noexcept {
    if (counter_ && !--*counter_) {
        delete ptr_;
        delete counter_;
    }
}

template<typename T>
inline T* shared_ptr<T>::operator ->() const noexcept {
    return ptr_;
}

template<typename T>
inline T& shared_ptr<T>::operator *() const noexcept {
    return *ptr_;
}

template<typename T>
inline T* shared_ptr<T>::get() const noexcept {
    return ptr_;
}

template<typename T>
inline void shared_ptr<T>::reset(T * ptr) noexcept {
    shared_ptr<T> temp(ptr);
    swap(temp);
}

template<typename T>
inline size_t shared_ptr<T>::count() const noexcept {
    return counter_ ? *counter_ : 0;
}

template<typename T>
inline void shared_ptr<T>::swap(shared_ptr<T> & other) noexcept {
    std::swap(counter_, other.counter_);
    std::swap(ptr_, other.ptr_);
}

template<typename T>
inline void swap(shared_ptr<T> & a, shared_ptr<T> & b) noexcept {
    std::swap(a, b);
}

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

    explicit linked_ptr(T*) noexcept;
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
