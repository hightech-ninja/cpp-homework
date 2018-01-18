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
    a.swap(b);
}

template<typename T>
class linked_ptr
{
    mutable linked_ptr const * left_;
    mutable linked_ptr const * right_;
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
    void swap(linked_ptr<T> &) noexcept;

    template<typename U>
    friend void swap(linked_ptr<U> &, linked_ptr<U> &) noexcept;
};

template<typename T>
constexpr linked_ptr<T>::linked_ptr() noexcept
    : left_(nullptr), right_(nullptr), ptr_(nullptr)
{}

template<typename T>
linked_ptr<T>::linked_ptr(linked_ptr<T> const & other) noexcept
    : linked_ptr(other.ptr_)
{
    if (ptr_) {
        if (other.left_ != nullptr) {
            other.left_->right_ = this;
            left_ = other.left_;
        }
        other.left_ = this;
        right_ = &other;
    }
}

template<typename T>
linked_ptr<T>::linked_ptr(linked_ptr<T> && other) noexcept
    : linked_ptr()
{
    swap(other);
}

template<typename T>
linked_ptr<T>& linked_ptr<T>::operator =(linked_ptr<T> const & other) noexcept
{
    if (ptr_ != other.ptr_) {
        linked_ptr<T> temp(other);
        swap(temp);
    }
    return *this;
}

template<typename T>
linked_ptr<T>& linked_ptr<T>::operator =(linked_ptr<T> && other) noexcept
{
    swap(other);
    return *this;
}

template<typename T>
linked_ptr<T>::~linked_ptr() noexcept
{
    if (left_)
        left_->right_ = right_;
    if (right_)
        right_->left_ = left_;
    if (left_ == right_)
        delete ptr_;
}

template<typename T>
linked_ptr<T>::linked_ptr(T* ptr) noexcept
    : left_(nullptr), right_(nullptr), ptr_(ptr)
{}

template<typename T>
T* linked_ptr<T>::operator ->() const noexcept
{
    return ptr_;
}

template<typename T>

T& linked_ptr<T>::operator *() const noexcept
{
    return *ptr_;
}

template<typename T>
T* linked_ptr<T>::get() const noexcept
{
    return ptr_;
}

template<typename T>
void linked_ptr<T>::reset(T* ptr) noexcept
{
    linked_ptr<T> temp(ptr);
    swap(temp);
}

template<typename T>
void linked_ptr<T>::swap(linked_ptr<T> & other) noexcept
{
    if (ptr_ != other.ptr_) {
        std::swap(left_, other.left_);
        std::swap(right_, other.right_);
        std::swap(ptr_, other.ptr_);
        if (left_)
            left_->right_ = this;
        if (right_)
            right_->left_ = this;
        if (other.left_)
            other.left_->right_ = &other;
        if (other.right_)
            other.right_->left_ = &other;
    }
}

template<typename T>
void swap(linked_ptr<T> & a, linked_ptr<T> & b) noexcept
{
    a.swap(b);
}

} // pointers namespace

} // bezborodov namespace

#endif // PERSISTENT_SET_H
