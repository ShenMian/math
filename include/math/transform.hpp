// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "matrix/matrix.hpp"
#include "quaternion.hpp"
#include "hash_combine.hpp"

class Transform
{
public:
	const Vector3& position() const noexcept;
	const Quaternion& rotation() const noexcept;
	const Vector3& scale() const noexcept;
	Vector3& position() noexcept;
	Quaternion& rotation() noexcept;
	Vector3& scale() noexcept;

	const Matrix4f& matrix() const;

	Transform& operator+=(const Transform&);

private:
	Vector3    position_;
	Quaternion rotation_;
	Vector3    scale_ = Vector3(1.f);

	mutable Matrix4f matrix_;
	mutable bool     dirty_ = true;
};

#include "transform.inl"

MAKE_HASHABLE(Transform, t.position(), t.rotation(), t.scale())
