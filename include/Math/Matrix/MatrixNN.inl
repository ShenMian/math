// Copyright 2021 SMS
// License(Apache-2.0)

template <arithmetic T, size_t N>
inline MatrixT<T, N, N>::MatrixT()
{
	for(size_t n = 0; n < N; n++)
		m_[n][n] = T(1);
}
