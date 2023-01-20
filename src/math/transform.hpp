// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include "hash_combine.hpp"
#include "matrix/matrix.hpp"
#include "quaternion.hpp"

class Transform
{
public:
	Transform() = default;
	Transform(const Matrix4& mat) { mat.decompose(&translation_, &rotation_, &scale_); }

	const Vector3&    translation() const noexcept { return translation_; }
	const Quaternion& rotation() const noexcept { return rotation_; }
	const Vector3&    scale() const noexcept { return scale_; }

	Vector3& translation() noexcept
	{
		dirty_ = true;
		return translation_;
	}

	Quaternion& rotation() noexcept
	{
		dirty_ = true;
		return rotation_;
	}

	Vector3& scale() noexcept
	{
		dirty_ = true;
		return scale_;
	}

	const Matrix4f& matrix() const
	{
		if(dirty_)
		{
			matrix_.recompose(translation_, rotation_, scale_);
			dirty_ = false;
		}
		return matrix_;
	}

	Transform& operator+=(const Transform& rhs)
	{
		dirty_ = true;
		translation_ += rhs.translation_;
		rotation_ += rhs.rotation_;
		scale_ += rhs.scale_;
		return *this;
	}

private:
	Vector3    translation_;
	Quaternion rotation_;
	Vector3    scale_ = Vector3(1.f);

	mutable Matrix4f matrix_;
	mutable bool     dirty_ = true;
};

MAKE_HASHABLE(Transform, t.translation(), t.rotation(), t.scale())
