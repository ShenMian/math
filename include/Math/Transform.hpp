// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Matrix/Matrix.hpp"
#include "Quaternion.hpp"

class Transform
{
public:
    [[nodiscard]] const Vector3f& position() const;
    [[nodiscard]] const Quaternionf& rotation() const;
    [[nodiscard]] const Vector3f& scale() const;
    [[nodiscard]] Vector3f& position();
    [[nodiscard]] Quaternionf& rotation();
    [[nodiscard]] Vector3f& scale();

    [[nodiscard]] const Matrix4f& matrix() const;

    Transform& operator+=(const Transform&);

private:
    Vector3f position_;
    Quaternionf rotation_;
    Vector3f scale_;

    mutable Matrix4f matrix_;
    mutable bool dirty_;
};

#include "Transform.inl"
