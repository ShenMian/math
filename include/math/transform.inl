﻿// Copyright 2021 SMS
// License(Apache-2.0)

[[nodiscard]] inline const Vector3f& Transform::position() const noexcept
{
	return position_;
}

[[nodiscard]] inline const Quaternionf& Transform::rotation() const noexcept
{
	return rotation_;
}

[[nodiscard]] inline const Vector3f& Transform::scale() const noexcept
{
	return scale_;
}

[[nodiscard]] inline Vector3f& Transform::position() noexcept
{
	dirty_ = true;
	return position_;
}

[[nodiscard]] inline Quaternionf& Transform::rotation() noexcept
{
	dirty_ = true;
	return rotation_;
}

[[nodiscard]] inline Vector3f& Transform::scale() noexcept
{
	dirty_ = true;
	return scale_;
}

inline Transform& Transform::operator+=(const Transform& rhs)
{
	dirty_ = true;
	position_ += rhs.position_;
	rotation_ += rhs.rotation_;
	scale_ += rhs.scale_;
	return *this;
}

inline const Matrix4f& Transform::matrix() const
{
	if(dirty_)
	{
		matrix_.recompose(position_, rotation_, scale_);
		dirty_ = false;
	}
	return matrix_;
}
