// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Matrix/Matrix.hpp"

class Transform
{
public:
    Vector3f position() const;
    Quaternionf rotation() const;
    Vector3f scale() const;

    Vector3f front() const;
    Vector3f back() const;
    Vector3f left() const;
    Vector3f right() const;
    Vector3f up() const;
    Vector3f down() const;

    Transform& operator*=(const Transform&);

	operator Matrix4f() const;

private:
    Matrix4f matrix;
};

#include "Transform.inl"
