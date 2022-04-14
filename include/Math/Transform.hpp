// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Matrix/Matrix.hpp"
#include "Quaternion.hpp"

class Transform
{
public:
    [[nodiscard]] const Vector3f& position() const noexcept;
    [[nodiscard]] const Quaternionf& rotation() const noexcept;
    [[nodiscard]] const Vector3f& scale() const noexcept;
    [[nodiscard]] Vector3f& position() noexcept;
    [[nodiscard]] Quaternionf& rotation() noexcept;
    [[nodiscard]] Vector3f& scale() noexcept;

    [[nodiscard]] const Matrix4f& matrix() const;

    Transform& operator+=(const Transform&);

private:
    Vector3f position_;
    Quaternionf rotation_;
    Vector3f scale_ = Vector3f(1.f);

    mutable Matrix4f matrix_;
    mutable bool dirty_ = true;
};

#include "Transform.inl"
