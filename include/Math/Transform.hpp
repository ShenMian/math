// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Matrix/Matrix.hpp"
#include "Quaternion.hpp"

class Transform
{
public:
	const Vector3f& position() const noexcept;
	const Quaternionf& rotation() const noexcept;
	const Vector3f& scale() const noexcept;
	Vector3f& position() noexcept;
	Quaternionf& rotation() noexcept;
	Vector3f& scale() noexcept;

	const Matrix4f& matrix() const;

	Transform& operator+=(const Transform&);

private:
	Vector3f position_;
	Quaternionf rotation_;
	Vector3f scale_ = Vector3f(1.f);

	mutable Matrix4f matrix_;
	mutable bool dirty_ = true;
};

#include "Transform.inl"
