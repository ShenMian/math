// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "hash_combine.hpp"
#include "matrix/matrix.hpp"
#include "quaternion.hpp"

class Transform
{
public:
	Transform() = default;
	Transform(const Matrix4& mat);

	const Vector3&    translation() const noexcept;
	const Quaternion& rotation() const noexcept;
	const Vector3&    scale() const noexcept;
	Vector3&          translation() noexcept;
	Quaternion&       rotation() noexcept;
	Vector3&          scale() noexcept;

	const Matrix4f& matrix() const;

	Transform& operator+=(const Transform&);

private:
	Vector3    translation_;
	Quaternion rotation_;
	Vector3    scale_ = Vector3(1.f);

	mutable Matrix4f matrix_;
	mutable bool     dirty_ = true;
};

#include "transform.inl"

MAKE_HASHABLE(Transform, t.translation(), t.rotation(), t.scale())
