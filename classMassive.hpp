#ifndef DATA_MASSIVE_H
#define DATA_MASSIVE_H

#include <iostream>

template <typename T>
class Massive
{
public:
    Massive()
    {
        arr_ = new T[1];
        capacity_ = 1;
    }
    Massive(Massive &other)
    {
        if (this != &other)
        {
            delete[] arr_;
            arr_ = other.arr_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.arr_ = nullptr;
            other.size_ = other.capacity_ = 0;
        }
    }
    Massive(Massive &&other) noexcept
    {
        if (this != &other)
        {
            delete[] arr_;
            arr_ = other.arr_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.arr_ = nullptr;
            other.size_ = other.capacity_ = 0;
        }
    }
    Massive &operator=(Massive &other)
    {
        if (this != &other)
        {
            delete[] arr_;
            arr_ = other.arr_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.arr_ = nullptr;
            other.size_ = other.capacity_ = 0;
        }
        return *this;
    }

    bool contains(const T& element) const {
        for (size_t i = 0; i < size_; ++i)
        {
            if (arr_[i] == element)
                return true;
        }
        return false;
    }

    Massive &operator=(Massive &&other) noexcept
    {
        if (this != &other)
        {
            delete[] arr_;
            arr_ = other.arr_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.arr_ = nullptr;
            other.size_ = other.capacity_ = 0;
        }
        return *this;
    }

    ~Massive()
    {
        delete[] arr_;
    }

    [[nodiscard]] bool isEmpty() const
    {
        return size_ == 0;
    }

    [[nodiscard]] size_t size() const
    {
        return size_;
    }

    [[nodiscard]] size_t capacity() const
    {
        return capacity_;
    }

    void pushBack(const T &value)
    {
        if (size_ >= capacity_)
            addMemory();
        arr_[size_++] = value;
    }

    void remove(size_t index)
    {
        for (size_t i = index + 1; i < size_; ++i)
        {
            arr_[i - 1] = arr_[i];
        }
        --size_;
    }

    void clear()
    {

        while (size_ != 0)
            remove(0);
    }

    T *begin()
    {
        return &arr_[0];
    }

    const T *begin() const
    {
        return &arr_[0];
    }

    T *end()
    {
        return &arr_[size_];
    }

    const T *end() const
    {
        return &arr_[size_];
    }

    T &operator[](size_t index)
    {
        return arr_[index];
    }

    const T &operator[](size_t index) const
    {
        return arr_[index];
    }

private:
    void addMemory()
    {
        capacity_ *= 2;
        T *tmp = arr_;
        arr_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i)
            arr_[i] = tmp[i];
        delete[] tmp;
    }

    T *arr_;
    size_t size_{};
    size_t capacity_{};
};

template <typename T>
inline std::ostream &operator<<(std::ostream &os, const Massive<T> &vec)
{
    for (const T &val : vec)
        os << val << " ";
    return os;
}

#endif
