// Copyright 2021 SMS
// License(Apache-2.0)

template <typename T>
requires std::floating_point<T>
QuaternionT<T>::QuaternionT(const T& x, const T& y, const T& z, const T& w)
    : x(x), y(y), z(z), w(w)
{
}