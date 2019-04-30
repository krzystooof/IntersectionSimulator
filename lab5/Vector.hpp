#pragma once

#include <iostream>

template <typename T>
class Vector {
private:
    size_t dimensions;
    T *data;

public:
    Vector<T>(size_t dimensions)
        : dimensions(dimensions), data(new T[dimensions]()) {}

    Vector<T>(const Vector<T> &a)
        : dimensions(a.dimensions), data(new T[a.dimensions]()) {
        for (size_t i = 0; i < dimensions; i++)
            data[i] = a[i];
    }

    Vector<T> &operator=(const Vector<T> &a) {
        Vector temp(a);
        std::swap(temp.dimensions, dimensions); // std::copy or std::move?
        std::swap(temp.data, data);
        return *this;
    }

    virtual ~Vector<T>() {
        delete[] data;
    }

    size_t size() const {
        return dimensions;
    }

    T &at(size_t index) {
        return data[index];
    }

    const T &at(size_t index) const {
        return data[index];
    }

    T &operator[](size_t index) {
        return data[index];
    }

    const T &operator[](size_t index) const {
        return data[index];
    }

    Vector<T> operator+(const Vector<T> &a) {
        Vector<T> v(dimensions);
        if (dimensions == a.size()) {

            for (size_t i = 0; i < dimensions; i++)
                v[i] = a[i] + data[i];
            return v;
        }
        return v;
    }

    Vector<T> operator-(const Vector<T> &a) {
        if (dimensions == a.size()) {
            Vector<T> v(dimensions);
            for (size_t i = 0; i < dimensions; i++)
                data[i] -= a[i];
            return v;
        }
    }

    bool operator==(const Vector<T> &a) {
        if (a.size() != dimensions)
            return false;
        for (size_t i = 0; i < dimensions; i++) {
            if (a[i] != data[i])
                return false;
        }
        return true;
    }

    bool operator!=(const Vector<T> &a) {
        if (a.size() != dimensions)
            return true;
        for (size_t i = 0; i < dimensions; i++) {
            if (a[i] != data[i])
                return true;
        }
        return false;
    }
};

template <typename T> Vector<T> add(const Vector<T> &a, const Vector<T> &b) {
    Vector<T> c(a.size());
    for (size_t i = 0; i < a.size(); i++)
        c[i] = a[i] + b[i];
    return c;
}

template <typename T> bool equals(const Vector<T> &a, const Vector<T> &b) {
    if (&a == &b)
        return true;
    if (a.size() != b.size())
        return false;
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

template <typename T>
std::ostream &operator<<(std::ostream &stream, const Vector<T> &a) {
    stream << "[";
    for (size_t i = 0; i < a.size(); i++)
        stream << a[i] << " ";
    return stream << "]";
}
