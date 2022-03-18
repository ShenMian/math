// Copyright 2021 SMS
// License(Apache-2.0)

inline Vector3f Transform::position() const
{
    return Vector3f();
}

inline Vector3f Transform::scale() const
{
    return Vector3f();
}

inline Quaternionf Transform::rotation() const
{
    return Quaternionf();
}

inline Vector3f Transform::front() const
{
    return matrix.front();
}

inline Vector3f Transform::back() const
{
    return matrix.back();
}

inline Vector3f Transform::left() const
{
    return matrix.left();
}

inline Vector3f Transform::right() const
{
    return matrix.right();
}

inline Vector3f Transform::up() const
{
    return matrix.up();
}

inline Vector3f Transform::down() const
{
    return matrix.down();
}

inline Transform& Transform::operator*=(const Transform& rhs)
{
    matrix *= rhs.matrix;
    return *this;
}

inline Transform::operator Matrix4f() const
{
	return matrix;
}
