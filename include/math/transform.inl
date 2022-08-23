// Copyright 2021 SMS
// License(Apache-2.0)

inline Transform::Transform(const Matrix4& mat)
{
	mat.decompose(&translation_, &rotation_, &scale_);
}

[[nodiscard]] inline const Vector3f& Transform::translation() const noexcept
{
	return translation_;
}

[[nodiscard]] inline const Quaternionf& Transform::rotation() const noexcept
{
	return rotation_;
}

[[nodiscard]] inline const Vector3f& Transform::scale() const noexcept
{
	return scale_;
}

[[nodiscard]] inline Vector3f& Transform::translation() noexcept
{
	dirty_ = true;
	return translation_;
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
	translation_ += rhs.translation_;
	rotation_ += rhs.rotation_;
	scale_ += rhs.scale_;
	return *this;
}

inline const Matrix4f& Transform::matrix() const
{
	if(dirty_)
	{
		matrix_.recompose(translation_, rotation_, scale_);
		dirty_ = false;
	}
	return matrix_;
}
