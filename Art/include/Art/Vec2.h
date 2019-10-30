#if !defined(_VEC2_H_)
#define _VEC2_H_

#if !defined(Assert)
#define Assert(_exp) ((void)0)
#endif // #if !defined(Assert)

#if !defined(CHECK_VALID)
#define CHECK_VALID(_v) Assert((_v).isValid())
#endif // #if !define(//CHECK_VALID)

#if defined(__GNUC__) || defined(__clang__)
#define FORCE_INLINE __attribute__((always_inline)) inline
#elif defined(_MSC_VER)
#define FORCE_INLINE __forceinline
#else
#define FORCE_INLINE inline
#endif

#include <iostream>
#include <cmath>
#include <limits>

namespace art
{
template <typename T>
class Vec2
{
public:
	union {
		T vecArray[2]; //__attribute__ ((aligned (16)));
		struct
		{
			T x;
			T y;
		} vecStruct;
	} vecUnion;

	Vec2<T>(void);
	Vec2<T>(T i);
	Vec2<T>(T X, T Y);
	void Init(T ix = 0.f, T iy = 0.f);
	FORCE_INLINE T const getX() const;
	FORCE_INLINE T const getY() const;
	FORCE_INLINE T operator[](int i) const;
	FORCE_INLINE T &operator[](int i);
	FORCE_INLINE Vec2<T> &operator++();
	FORCE_INLINE Vec2<T> operator++(int);
	FORCE_INLINE Vec2<T> &operator--();
	FORCE_INLINE Vec2<T> operator--(int);
	FORCE_INLINE bool operator==(const Vec2<T> &vOther) const;
	FORCE_INLINE bool operator!=(const Vec2<T> &vOther) const;
	FORCE_INLINE bool operator>(const Vec2<T> &vOther) const;
	FORCE_INLINE bool operator>(T s) const;
	FORCE_INLINE bool operator<(const Vec2<T> &vOther) const;
	FORCE_INLINE bool operator<(T s) const;
	FORCE_INLINE bool operator>=(const Vec2<T> &vOther) const;
	FORCE_INLINE bool operator>=(T s) const;
	FORCE_INLINE bool operator<=(const Vec2<T> &vOther) const;
	FORCE_INLINE bool operator<=(T s) const;
	FORCE_INLINE Vec2<T> &operator+=(const Vec2<T> &vOther);
	FORCE_INLINE Vec2<T> &operator+=(T fl);
	FORCE_INLINE Vec2<T> &operator-=(const Vec2<T> &vOther);
	FORCE_INLINE Vec2<T> &operator-=(T fl);
	FORCE_INLINE Vec2<T> &operator*=(const Vec2<T> &vOther);
	FORCE_INLINE Vec2<T> &operator*=(T s);
	FORCE_INLINE Vec2<T> &operator/=(const Vec2<T> &vOther);
	FORCE_INLINE Vec2<T> &operator/=(T s);
	FORCE_INLINE Vec2<T> &operator=(const Vec2<T> &vOther);
	FORCE_INLINE Vec2<T> operator+(const Vec2<T> &vOther) const;
	FORCE_INLINE Vec2<T> operator-(const Vec2<T> &vOther) const;
	FORCE_INLINE Vec2<T> operator*(const Vec2<T> &vOther) const;
	FORCE_INLINE Vec2<T> operator/(const Vec2<T> &vOther) const;
	FORCE_INLINE Vec2<T> operator+(T fl) const;
	FORCE_INLINE Vec2<T> operator-(T fl) const;
	FORCE_INLINE Vec2<T> operator*(T fl) const;
	FORCE_INLINE Vec2<T> operator/(T fl) const;
	FORCE_INLINE void Zero();
	FORCE_INLINE bool isValid() const;
	FORCE_INLINE T Length() const;
	FORCE_INLINE T LengthSqr(void) const;
	FORCE_INLINE bool IsZero(const T tolerance = 0.01f) const;
	FORCE_INLINE void NormalizeInPlace();
	FORCE_INLINE T DistToSqr(const Vec2<T> &vOther) const;
	FORCE_INLINE T DistTo(const Vec2<T> &vOther) const;
	FORCE_INLINE T Dot(const Vec2<T> &vOther) const;

	friend std::ostream &operator<<(std::ostream &os, const Vec2<T> &vOther)
	{
		return os << vOther.vecUnion.vecStruct.x << ' ' << vOther.vecUnion.vecStruct.y;
	}
};

template <typename T>
inline T const Vec2<T>::getX() const
{
	return vecUnion.vecStruct.x;
}

template <typename T>
inline T const Vec2<T>::getY() const
{
	return vecUnion.vecStruct.y;
}

template <typename T>
inline bool Vec2<T>::isValid() const
{
	return std::isfinite(vecUnion.vecStruct.x) && std::isfinite(vecUnion.vecStruct.y);
}

template <typename T>
inline void Vec2<T>::Init(T ix, T iy)
{
	vecUnion.vecStruct.x = ix;
	vecUnion.vecStruct.y = iy;
	//CHECK_VALID(*this);
}

template <typename T>
inline Vec2<T>::Vec2(T X, T Y)
{
	vecUnion.vecStruct.x = X;
	vecUnion.vecStruct.y = Y;
	//CHECK_VALID(*this);
}

template <typename T>
inline Vec2<T>::Vec2(T i)
{
	vecUnion.vecStruct.x = i;
	vecUnion.vecStruct.y = i;
	//CHECK_VALID(*this);
}

template <typename T>
inline Vec2<T>::Vec2(void)
{
	vecUnion.vecStruct.x = 0;
	vecUnion.vecStruct.y = 0;
}

template <typename T>
inline void Vec2<T>::Zero()
{
	vecUnion.vecStruct.x = 0.f;
	vecUnion.vecStruct.y = 0.f;
}

template <typename T>
inline void Clear(Vec2<T> &a)
{
	a.vecUnion.vecStruct.x = 0.f;
	a.vecUnion.vecStruct.y = 0.f;
}

template <typename T>
inline Vec2<T> &Vec2<T>::operator++()
{
	++vecUnion.vecStruct.x;
	++vecUnion.vecStruct.y;
	return *this;
}

template <typename T>
inline Vec2<T> Vec2<T>::operator++(int)
{
	Vec2<T> temp = *this;
	++vecUnion.vecStruct.x;
	++vecUnion.vecStruct.y;
	return temp;
}

template <typename T>
inline Vec2<T> &Vec2<T>::operator--()
{
	--vecUnion.vecStruct.x;
	--vecUnion.vecStruct.y;
	return *this;
}

template <typename T>
inline Vec2<T> Vec2<T>::operator--(int)
{
	Vec2<T> temp = *this;
	--vecUnion.vecStruct.x;
	--vecUnion.vecStruct.y;
	return temp;
}

template <typename T>
inline Vec2<T> &Vec2<T>::operator=(const Vec2<T> &vOther)
{
	//CHECK_VALID(vOther);
	vecUnion.vecStruct.x = vOther.vecUnion.vecStruct.x;
	vecUnion.vecStruct.y = vOther.vecUnion.vecStruct.y;
	return *this;
}

template <typename T>
inline T &Vec2<T>::operator[](int i)
{
	Assert((i >= 0) && (i < 2));
	return ((T *)this)[i];
}

template <typename T>
inline T Vec2<T>::operator[](int i) const
{
	Assert((i >= 0) && (i < 2));
	return ((T *)this)[i];
}

template <typename T>
inline bool Vec2<T>::operator==(const Vec2<T> &vOther) const
{
	//CHECK_VALID(vOther);
	//CHECK_VALID(*this);
	return (vOther.vecUnion.vecStruct.x == vecUnion.vecStruct.x) && (vOther.vecUnion.vecStruct.y == vecUnion.vecStruct.y);
}

template <typename T>
inline bool Vec2<T>::operator!=(const Vec2<T> &vOther) const
{
	//CHECK_VALID(vOther);
	//CHECK_VALID(*this);
	return (vOther.vecUnion.vecStruct.x != vecUnion.vecStruct.x) && (vOther.vecUnion.vecStruct.x != vecUnion.vecStruct.y);
}

template <typename T>
inline bool Vec2<T>::operator>(const Vec2<T> &vOther) const
{
	//CHECK_VALID(vOther);
	//CHECK_VALID(*this);
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y) > (vOther.vecUnion.vecStruct.x + vOther.vecUnion.vecStruct.y);
}

template <typename T>
inline bool Vec2<T>::operator>(T s) const
{
	//CHECK_VALID(*this);
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y) > s;
}

template <typename T>
inline bool Vec2<T>::operator<(const Vec2<T> &vOther) const
{
	//CHECK_VALID(vOther);
	//CHECK_VALID(*this);
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y) < (vOther.vecUnion.vecStruct.x + vOther.vecUnion.vecStruct.y);
}

template <typename T>
inline bool Vec2<T>::operator<(T s) const
{
	//CHECK_VALID(*this);
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y) < s;
}

template <typename T>
inline bool Vec2<T>::operator>=(const Vec2<T> &vOther) const
{
	//CHECK_VALID(vOther);
	//CHECK_VALID(*this);
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y) >= (vOther.vecUnion.vecStruct.x + vOther.vecUnion.vecStruct.y);
}

template <typename T>
inline bool Vec2<T>::operator>=(T s) const
{
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y) >= s;
}

template <typename T>
inline bool Vec2<T>::operator<=(const Vec2<T> &vOther) const
{
	//CHECK_VALID(vOther);
	//CHECK_VALID(*this);
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y) <= (vOther.vecUnion.vecStruct.x + vOther.vecUnion.vecStruct.y);
}

template <typename T>
inline bool Vec2<T>::operator<=(T s) const
{
	//CHECK_VALID(*this);
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y) <= s;
}

template <typename T>
FORCE_INLINE void Copy(const Vec2<T> &vOther, Vec2<T> &dst)
{
	//CHECK_VALID(vOther);
	dst.x = vOther.vecUnion.vecStruct.x;
	dst.y = vOther.vecUnion.vecStruct.y;
}

template <typename T>
FORCE_INLINE Vec2<T> &Vec2<T>::operator+=(const Vec2<T> &vOther)
{
	//CHECK_VALID(*this);
	//CHECK_VALID(vOther);
	vecUnion.vecStruct.x += vOther.vecUnion.vecStruct.x;
	vecUnion.vecStruct.y += vOther.vecUnion.vecStruct.y;
	return *this;
}

template <typename T>
FORCE_INLINE Vec2<T> &Vec2<T>::operator-=(const Vec2<T> &vOther)
{
	//CHECK_VALID(*this);
	//CHECK_VALID(vOther);
	vecUnion.vecStruct.x -= vOther.vecUnion.vecStruct.x;
	vecUnion.vecStruct.y -= vOther.vecUnion.vecStruct.y;
	return *this;
}

template <typename T>
FORCE_INLINE Vec2<T> &Vec2<T>::operator*=(T fl)
{
	vecUnion.vecStruct.x *= fl;
	vecUnion.vecStruct.y *= fl;
	//CHECK_VALID(*this);
	return *this;
}

template <typename T>
FORCE_INLINE Vec2<T> &Vec2<T>::operator*=(const Vec2<T> &vOther)
{
	//CHECK_VALID(vOther);
	vecUnion.vecStruct.x *= vOther.vecUnion.vecStruct.x;
	vecUnion.vecStruct.y *= vOther.vecUnion.vecStruct.y;
	//CHECK_VALID(*this);
	return *this;
}

template <typename T>
FORCE_INLINE Vec2<T> &Vec2<T>::operator+=(T fl)
{
	vecUnion.vecStruct.x += fl;
	vecUnion.vecStruct.y += fl;
	//CHECK_VALID(*this);
	return *this;
}

template <typename T>
FORCE_INLINE Vec2<T> &Vec2<T>::operator-=(T fl)
{
	vecUnion.vecStruct.x -= fl;
	vecUnion.vecStruct.y -= fl;
	//CHECK_VALID(*this);
	return *this;
}

template <typename T>
FORCE_INLINE Vec2<T> &Vec2<T>::operator/=(T fl)
{
	Assert(fl != 0.f);
	T oofl = 1.0f / fl;
	vecUnion.vecStruct.x *= oofl;
	vecUnion.vecStruct.y *= oofl;
	//CHECK_VALID(*this);
	return *this;
}

template <typename T>
FORCE_INLINE Vec2<T> &Vec2<T>::operator/=(const Vec2<T> &vOther)
{
	//CHECK_VALID(vOther);
	Assert(vOther.x != 0.f && vOther.y != 0.f && vOther.z != 0.f);
	vecUnion.vecStruct.x /= vOther.vecUnion.vecStruct.x;
	vecUnion.vecStruct.y /= vOther.vecUnion.vecStruct.y;
	//CHECK_VALID(*this);
	return *this;
}

template <typename T>
inline T Vec2<T>::Length(void) const
{
	//CHECK_VALID(*this);

	T root = 0.f;

	T sqsr = vecUnion.vecStruct.x * vecUnion.vecStruct.x + vecUnion.vecStruct.y * vecUnion.vecStruct.y;

#if defined(__GNUC__) || defined(__clang__)
	__asm__("sqrtss %1, %0"
			: "=x"(root)
			: "x"(sqsr));
#elif defined(_MSC_VER)
	__asm
	{
		sqrtss xmm0, sqsr
		movss root, xmm0
	}
#else
	return sqrt(sqsr);
#endif

	return root;
}

template <typename T>
FORCE_INLINE T Vec2<T>::LengthSqr(void) const
{
	//CHECK_VALID(*this);
	return (vecUnion.vecStruct.x * vecUnion.vecStruct.x + vecUnion.vecStruct.y * vecUnion.vecStruct.y);
}

template <typename T>
FORCE_INLINE bool Vec2<T>::IsZero(T tolerance) const
{
	return (vecUnion.vecStruct.x > -tolerance && vecUnion.vecStruct.x < tolerance &&
			vecUnion.vecStruct.y > -tolerance && vecUnion.vecStruct.y < tolerance);
}

template <typename T>
inline Vec2<T> CrossProduct(const Vec2<T> &a, const Vec2<T> &b)
{
	return Vec2<T>(a.vecUnion.vecStruct.x * b.vecUnion.vecStruct.y - a.vecUnion.vecStruct.y * b.vecUnion.vecStruct.x);
}

template <typename T>
T Vec2<T>::DistToSqr(const Vec2<T> &vOther) const
{
	Vec2<T> delta;

	delta.vecUnion.vecStruct.x = vecUnion.vecStruct.x - vOther.vecUnion.vecStruct.x;
	delta.vecUnion.vecStruct.y = vecUnion.vecStruct.y - vOther.vecUnion.vecStruct.y;

	return delta.LengthSqr();
}

template <typename T>
FORCE_INLINE T Vec2<T>::DistTo(const Vec2<T> &vOther) const
{
	//CHECK_VALID(*this);
	return std::sqrt((vecUnion.vecStruct.x - vOther.vecUnion.vecStruct.x) * (vecUnion.vecStruct.x - vOther.vecUnion.vecStruct.x) + (vecUnion.vecStruct.y - vOther.vecUnion.vecStruct.y) * (vecUnion.vecStruct.y - vOther.vecUnion.vecStruct.y));
}

template <typename T>
inline void Vec2<T>::NormalizeInPlace()
{
	Vec2<T> &vOther = *this;

	T iradius = 1.f / (this->Length() + 1.192092896e-07F); //FLT_EPSILON

	vOther.vecUnion.vecStruct.x *= iradius;
	vOther.vecUnion.vecStruct.y *= iradius;
}

template <typename T>
inline Vec2<T> Vec2<T>::operator+(const Vec2<T> &vOther) const
{
	Vec2<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x + vOther.vecUnion.vecStruct.x;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y + vOther.vecUnion.vecStruct.y;
	return res;
}

template <typename T>
inline Vec2<T> Vec2<T>::operator-(const Vec2<T> &vOther) const
{
	Vec2<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x - vOther.vecUnion.vecStruct.x;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y - vOther.vecUnion.vecStruct.y;
	return res;
}

template <typename T>
inline Vec2<T> Vec2<T>::operator+(T fl) const
{
	Vec2<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x + fl;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y + fl;
	return res;
}

template <typename T>
inline Vec2<T> Vec2<T>::operator-(T fl) const
{
	Vec2<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x - fl;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y - fl;
	return res;
}

template <typename T>
inline Vec2<T> Vec2<T>::operator*(T fl) const
{
	Vec2<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x * fl;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y * fl;
	return res;
}

template <typename T>
inline Vec2<T> Vec2<T>::operator*(const Vec2<T> &vOther) const
{
	Vec2<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x * vOther.vecUnion.vecStruct.x;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y * vOther.vecUnion.vecStruct.y;
	return res;
}

template <typename T>
inline Vec2<T> Vec2<T>::operator/(T fl) const
{
	Vec2<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x / fl;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y / fl;
	return res;
}

template <typename T>
inline Vec2<T> Vec2<T>::operator/(const Vec2<T> &vOther) const
{
	Vec2<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x / vOther.vecUnion.vecStruct.x;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y / vOther.vecUnion.vecStruct.y;
	return res;
}

template <typename T>
inline T Vec2<T>::Dot(const Vec2<T> &vOther) const
{
	const Vec2<T> &a = *this;

	return (a.vecUnion.vecStruct.x * vOther.vecUnion.vecStruct.x + a.vecUnion.vecStruct.y * vOther.vecUnion.vecStruct.y);
}
} // namespace art

/*
std::numeric_limits<T>::max()
std::numeric_limits<T>::lowest()
std::numeric_limits<T>::min()

*/

namespace std
{
template <typename T>
class numeric_limits<art::Vec2<T>>
{
public:
	static art::Vec2<T> max() { return art::Vec2<T>(std::numeric_limits<T>::max()); }
	static art::Vec2<T> min() { return art::Vec2<T>(std::numeric_limits<T>::min()); }
	static art::Vec2<T> lowest() { return art::Vec2<T>(std::numeric_limits<T>::lowest()); }
};
} // namespace std

#endif //_VEC3_H_