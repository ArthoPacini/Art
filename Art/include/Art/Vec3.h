#if !defined(_VEC3_H_)
#define _VEC3_H_

#if !defined(Assert)
#define Assert(_exp) ((void)0)
#endif

#if !defined(CHECK_VALID)
#define CHECK_VALID(_v) Assert((_v).isValid())
#endif

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
class Vec3
{
public:
	union {
		T vecArray[3]; //__attribute__((aligned(16)));
		struct
		{
			T x;
			T y;
			T z;
		} vecStruct;
	} vecUnion;

	Vec3<T>(void);
	Vec3<T>(T i);
	Vec3<T>(T X, T Y, T Z);
	void Init(T ix = 0.f, T iy = 0.f, T iz = 0.f);
	FORCE_INLINE T const getX() const;
	FORCE_INLINE T const getY() const;
	FORCE_INLINE T const getZ() const;
	FORCE_INLINE T operator[](std::uint8_t i) const;
	FORCE_INLINE T &operator[](std::uint8_t i);
	FORCE_INLINE Vec3<T> &operator++();
	FORCE_INLINE Vec3<T> operator++(int);
	FORCE_INLINE Vec3<T> &operator--();
	FORCE_INLINE Vec3<T> operator--(int);
	FORCE_INLINE bool operator==(const Vec3<T> &vOther) const;
	FORCE_INLINE bool operator!=(const Vec3<T> &vOther) const;
	FORCE_INLINE bool operator>(const Vec3<T> &vOther) const;
	FORCE_INLINE bool operator>(T s) const;
	FORCE_INLINE bool operator<(const Vec3<T> &vOther) const;
	FORCE_INLINE bool operator<(T s) const;
	FORCE_INLINE bool operator>=(const Vec3<T> &vOther) const;
	FORCE_INLINE bool operator>=(T s) const;
	FORCE_INLINE bool operator<=(const Vec3<T> &vOther) const;
	FORCE_INLINE bool operator<=(T s) const;
	FORCE_INLINE Vec3<T> &operator+=(const Vec3<T> &vOther);
	FORCE_INLINE Vec3<T> &operator+=(T fl);
	FORCE_INLINE Vec3<T> &operator-=(const Vec3<T> &vOther);
	FORCE_INLINE Vec3<T> &operator-=(T fl);
	FORCE_INLINE Vec3<T> &operator*=(const Vec3<T> &vOther);
	FORCE_INLINE Vec3<T> &operator*=(T s);
	FORCE_INLINE Vec3<T> &operator/=(const Vec3<T> &vOther);
	FORCE_INLINE Vec3<T> &operator/=(T s);
	FORCE_INLINE Vec3<T> &operator=(const Vec3<T> &vOther);
	FORCE_INLINE Vec3<T> operator+(const Vec3<T> &vOther) const;
	FORCE_INLINE Vec3<T> operator-(const Vec3<T> &vOther) const;
	FORCE_INLINE Vec3<T> operator*(const Vec3<T> &vOther) const;
	FORCE_INLINE Vec3<T> operator/(const Vec3<T> &vOther) const;
	FORCE_INLINE Vec3<T> operator+(T fl) const;
	FORCE_INLINE Vec3<T> operator-(T fl) const;
	FORCE_INLINE Vec3<T> operator*(T fl) const;
	FORCE_INLINE Vec3<T> operator/(T fl) const;
	FORCE_INLINE void Zero();
	FORCE_INLINE bool isValid() const;
	FORCE_INLINE T Length() const;
	FORCE_INLINE T LengthSqr(void) const;
	FORCE_INLINE bool IsZero(const T tolerance = 0.01f) const;
	FORCE_INLINE void NormalizeInPlace();
	FORCE_INLINE T DistToSqr(const Vec3<T> &vOther) const;
	FORCE_INLINE T DistTo(const Vec3<T> &vOther) const;
	FORCE_INLINE T Dot(const Vec3<T> &vOther) const;
	FORCE_INLINE T Length2D(void) const;
	FORCE_INLINE T Length2DSqr(void) const;

	friend std::ostream &operator<<(std::ostream &os, const Vec3<T> &vOther)
	{
		return os << vOther.vecUnion.vecStruct.x << ' ' << vOther.vecUnion.vecStruct.y << ' ' << vOther.vecUnion.vecStruct.z;
	}
};

template <typename T>
inline T const Vec3<T>::getX() const
{
	return vecUnion.vecStruct.x;
}

template <typename T>
inline T const Vec3<T>::getY() const
{
	return vecUnion.vecStruct.y;
}

template <typename T>
inline T const Vec3<T>::getZ() const
{
	return vecUnion.vecStruct.z;
}

template <typename T>
inline bool Vec3<T>::isValid() const
{
	return std::isfinite(vecUnion.vecStruct.x) && std::isfinite(vecUnion.vecStruct.y) && std::isfinite(vecUnion.vecStruct.z);
}

template <typename T>
inline void Vec3<T>::Init(T ix, T iy, T iz)
{
	//CHECK_VALID(*this);
	vecUnion.vecStruct.x = ix;
	vecUnion.vecStruct.y = iy;
	vecUnion.vecStruct.z = iz;
}

template <typename T>
inline Vec3<T>::Vec3(T X, T Y, T Z)
{
	//CHECK_VALID(*this);
	vecUnion.vecStruct.x = X;
	vecUnion.vecStruct.y = Y;
	vecUnion.vecStruct.z = Z;
}

template <typename T>
inline Vec3<T>::Vec3(T i)
{
	vecUnion.vecStruct.x = i;
	vecUnion.vecStruct.y = i;
	vecUnion.vecStruct.z = i;
	//CHECK_VALID(*this);
}

template <typename T>
inline Vec3<T>::Vec3(void)
{
	vecUnion.vecStruct.x = 0;
	vecUnion.vecStruct.y = 0;
	vecUnion.vecStruct.z = 0;
}

template <typename T>
inline void Vec3<T>::Zero()
{
	vecUnion.vecStruct.x = 0.f;
	vecUnion.vecStruct.y = 0.f;
	vecUnion.vecStruct.z = 0.f;
}

template <typename T>
inline void Clear(Vec3<T> &vOther)
{
	vOther.vecUnion.vecStruct.x = 0.f;
	vOther.vecUnion.vecStruct.y = 0.f;
	vOther.vecUnion.vecStruct.z = 0.f;
}

template <typename T>
inline Vec3<T> &Vec3<T>::operator++()
{
	++vecUnion.vecStruct.x;
	++vecUnion.vecStruct.y;
	++vecUnion.vecStruct.z;
	return *this;
}

template <typename T>
inline Vec3<T> Vec3<T>::operator++(int)
{
	Vec3<T> temp = *this;
	++vecUnion.vecStruct.x;
	++vecUnion.vecStruct.y;
	++vecUnion.vecStruct.z;
	return temp;
}

template <typename T>
inline Vec3<T> &Vec3<T>::operator--()
{
	--vecUnion.vecStruct.x;
	--vecUnion.vecStruct.y;
	--vecUnion.vecStruct.z;
	return *this;
}

template <typename T>
inline Vec3<T> Vec3<T>::operator--(int)
{
	Vec3<T> temp = *this;
	--vecUnion.vecStruct.x;
	--vecUnion.vecStruct.y;
	--vecUnion.vecStruct.z;
	return temp;
}

template <typename T>
inline Vec3<T> &Vec3<T>::operator=(const Vec3<T> &vOther)
{
	//CHECK_VALID(vOther);
	//CHECK_VALID(*this);
	vecUnion.vecStruct.x = vOther.vecUnion.vecStruct.x;
	vecUnion.vecStruct.y = vOther.vecUnion.vecStruct.y;
	vecUnion.vecStruct.z = vOther.vecUnion.vecStruct.z;
	return *this;
}

template <typename T>
inline T &Vec3<T>::operator[](std::uint8_t i)
{
	Assert((i >= 0) && (i < 3));
	switch (i)
	{
	case 0:
		return vecUnion.vecStruct.x;
	case 1:
		return vecUnion.vecStruct.y;
	case 2:
		return vecUnion.vecStruct.z;
	default:
		return vecUnion.vecStruct.x;
	}
}

template <typename T>
inline T Vec3<T>::operator[](std::uint8_t i) const
{
	Assert((i >= 0) && (i < 3));
	switch (i)
	{
	case 0:
		return vecUnion.vecStruct.x;
	case 1:
		return vecUnion.vecStruct.y;
	case 2:
		return vecUnion.vecStruct.z;
	default:
		return vecUnion.vecStruct.x;
	}
}

template <typename T>
inline bool Vec3<T>::operator==(const Vec3<T> &vOther) const
{
	//CHECK_VALID(vOther);
	//CHECK_VALID(*this);
	return (vOther.vecUnion.vecStruct.x == vecUnion.vecStruct.x) && (vOther.vecUnion.vecStruct.y == vecUnion.vecStruct.y) && (vOther.vecUnion.vecStruct.z == vecUnion.vecStruct.z);
}

template <typename T>
inline bool Vec3<T>::operator!=(const Vec3<T> &vOther) const
{
	//CHECK_VALID(vOther);
	//CHECK_VALID(*this);
	return (vOther.vecUnion.vecStruct.x != vecUnion.vecStruct.x) && (vOther.vecUnion.vecStruct.y != vecUnion.vecStruct.y) && (vOther.vecUnion.vecStruct.z != vecUnion.vecStruct.z);
}

template <typename T>
inline bool Vec3<T>::operator>(const Vec3<T> &vOther) const
{
	//CHECK_VALID(vOther);
	//CHECK_VALID(*this);
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y + vecUnion.vecStruct.z) > (vOther.vecUnion.vecStruct.x + vOther.vecUnion.vecStruct.y + vOther.vecUnion.vecStruct.z);
}

template <typename T>
inline bool Vec3<T>::operator>(T s) const
{
	//CHECK_VALID(vOther);
	//CHECK_VALID(*this);
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y + vecUnion.vecStruct.z) > s;
}

template <typename T>
inline bool Vec3<T>::operator<(const Vec3<T> &vOther) const
{
	//CHECK_VALID(vOther);
	//CHECK_VALID(*this);
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y + vecUnion.vecStruct.z) < (vOther.vecUnion.vecStruct.x + vOther.vecUnion.vecStruct.y + vOther.vecUnion.vecStruct.z);
}

template <typename T>
inline bool Vec3<T>::operator<(T s) const
{
	//CHECK_VALID(vOther);
	//CHECK_VALID(*this);
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y + vecUnion.vecStruct.z) < s;
}

template <typename T>
inline bool Vec3<T>::operator>=(const Vec3<T> &vOther) const
{
	//CHECK_VALID(vOther);
	//CHECK_VALID(*this);
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y + vecUnion.vecStruct.z) >= (vOther.vecUnion.vecStruct.x + vOther.vecUnion.vecStruct.y + vOther.vecUnion.vecStruct.z);
}

template <typename T>
inline bool Vec3<T>::operator>=(T s) const
{
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y + vecUnion.vecStruct.z) >= s;
}

template <typename T>
inline bool Vec3<T>::operator<=(const Vec3<T> &vOther) const
{
	//CHECK_VALID(vOther);
	//CHECK_VALID(*this);
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y + vecUnion.vecStruct.z) <= (vOther.vecUnion.vecStruct.x + vOther.vecUnion.vecStruct.y + vOther.vecUnion.vecStruct.z);
}

template <typename T>
inline bool Vec3<T>::operator<=(T s) const
{
	//CHECK_VALID(*this);
	return (vecUnion.vecStruct.x + vecUnion.vecStruct.y + vecUnion.vecStruct.z) <= s;
}

template <typename T>
FORCE_INLINE void Copy(const Vec3<T> &vOther, Vec3<T> &dst)
{
	//CHECK_VALID(vOther);
	dst.vecUnion.vecStruct.x = vOther.vecUnion.vecStruct.x;
	dst.vecUnion.vecStruct.y = vOther.vecUnion.vecStruct.y;
	dst.vecUnion.vecStruct.z = vOther.vecUnion.vecStruct.z;
}

template <typename T>
FORCE_INLINE Vec3<T> &Vec3<T>::operator+=(const Vec3<T> &vOther)
{
	//CHECK_VALID(*this);
	//CHECK_VALID(vOther);
	vecUnion.vecStruct.x += vOther.vecUnion.vecStruct.x;
	vecUnion.vecStruct.y += vOther.vecUnion.vecStruct.y;
	vecUnion.vecStruct.z += vOther.vecUnion.vecStruct.z;
	return *this;
}

template <typename T>
FORCE_INLINE Vec3<T> &Vec3<T>::operator-=(const Vec3<T> &vOther)
{
	//CHECK_VALID(*this);
	//CHECK_VALID(vOther);
	vecUnion.vecStruct.x -= vOther.vecUnion.vecStruct.x;
	vecUnion.vecStruct.y -= vOther.vecUnion.vecStruct.y;
	vecUnion.vecStruct.z -= vOther.vecUnion.vecStruct.z;
	return *this;
}

template <typename T>
FORCE_INLINE Vec3<T> &Vec3<T>::operator*=(T fl)
{
	vecUnion.vecStruct.x *= fl;
	vecUnion.vecStruct.y *= fl;
	vecUnion.vecStruct.z *= fl;
	//CHECK_VALID(*this);
	return *this;
}

template <typename T>
FORCE_INLINE Vec3<T> &Vec3<T>::operator*=(const Vec3<T> &vOther)
{
	//CHECK_VALID(vOther);
	vecUnion.vecStruct.x *= vOther.vecUnion.vecStruct.x;
	vecUnion.vecStruct.y *= vOther.vecUnion.vecStruct.y;
	vecUnion.vecStruct.z *= vOther.vecUnion.vecStruct.z;
	//CHECK_VALID(*this);
	return *this;
}

template <typename T>
FORCE_INLINE Vec3<T> &Vec3<T>::operator+=(T fl)
{
	vecUnion.vecStruct.x += fl;
	vecUnion.vecStruct.y += fl;
	vecUnion.vecStruct.z += fl;
	//CHECK_VALID(*this);
	return *this;
}

template <typename T>
FORCE_INLINE Vec3<T> &Vec3<T>::operator-=(T fl)
{
	vecUnion.vecStruct.x -= fl;
	vecUnion.vecStruct.y -= fl;
	vecUnion.vecStruct.z -= fl;
	//CHECK_VALID(*this);
	return *this;
}

template <typename T>
FORCE_INLINE Vec3<T> &Vec3<T>::operator/=(T fl)
{
	Assert(fl != 0.f);
	T oofl = 1.0f / fl;
	vecUnion.vecStruct.x *= oofl;
	vecUnion.vecStruct.y *= oofl;
	vecUnion.vecStruct.z *= oofl;
	//CHECK_VALID(*this);
	return *this;
}

template <typename T>
FORCE_INLINE Vec3<T> &Vec3<T>::operator/=(const Vec3<T> &vOther)
{
	//CHECK_VALID(vOther);
	Assert(vOther.x != 0.f && vOther.y != 0.f && vOther.z != 0.f);
	vecUnion.vecStruct.x /= vOther.vecUnion.vecStruct.x;
	vecUnion.vecStruct.y /= vOther.vecUnion.vecStruct.y;
	vecUnion.vecStruct.z /= vOther.vecUnion.vecStruct.z;
	//CHECK_VALID(*this);
	return *this;
}

template <typename T>
inline T Vec3<T>::Length(void) const
{
	//CHECK_VALID(*this);

	T root = 0.f;

	T sqsr = vecUnion.vecStruct.x * vecUnion.vecStruct.x + vecUnion.vecStruct.y * vecUnion.vecStruct.y + vecUnion.vecStruct.z * vecUnion.vecStruct.z;

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
FORCE_INLINE T Vec3<T>::LengthSqr(void) const
{
	//CHECK_VALID(*this);
	return (vecUnion.vecStruct.x * vecUnion.vecStruct.x + vecUnion.vecStruct.y * vecUnion.vecStruct.y + vecUnion.vecStruct.z * vecUnion.vecStruct.z);
}

template <typename T>
FORCE_INLINE bool Vec3<T>::IsZero(T tolerance) const
{
	return (vecUnion.vecStruct.x > -tolerance && vecUnion.vecStruct.x < tolerance &&
			vecUnion.vecStruct.y > -tolerance && vecUnion.vecStruct.y < tolerance &&
			vecUnion.vecStruct.z > -tolerance && vecUnion.vecStruct.z < tolerance);
}

template <typename T>
inline T Vec3<T>::Length2D(void) const
{
	//CHECK_VALID(*this);

	T root = 0.f;

	T sqst = vecUnion.vecStruct.x * vecUnion.vecStruct.x + vecUnion.vecStruct.y * vecUnion.vecStruct.y;

#if defined(__GNUC__) || defined(__clang__)
	__asm__("sqrtss %1, %0"
			: "=x"(root)
			: "x"(sqst));
#elif defined(_MSC_VER)
	__asm
	{
		sqrtss xmm0, sqst
		movss root, xmm0
	}
#else
	return std::sqrt(sqsr);
#endif

	return root;
}

template <typename T>
inline T Vec3<T>::Length2DSqr(void) const
{
	return (vecUnion.vecStruct.x * vecUnion.vecStruct.x + vecUnion.vecStruct.y * vecUnion.vecStruct.y);
}

template <typename T>
inline Vec3<T> CrossProduct(const Vec3<T> &a, const Vec3<T> &b)
{
	return Vec3<T>(a.vecUnion.vecStruct.y * b.vecUnion.vecStruct.z - a.vecUnion.vecStruct.z * b.vecUnion.vecStruct.y, a.vecUnion.vecStruct.z * b.vecUnion.vecStruct.x - a.vecUnion.vecStruct.x * b.vecUnion.vecStruct.z, a.vecUnion.vecStruct.x * b.vecUnion.vecStruct.y - a.vecUnion.vecStruct.y * b.vecUnion.vecStruct.x);
}

template <typename T>
T Vec3<T>::DistToSqr(const Vec3<T> &vOther) const
{
	Vec3<T> delta;

	delta.vecUnion.vecStruct.x = vecUnion.vecStruct.x - vOther.vecUnion.vecStruct.x;
	delta.vecUnion.vecStruct.y = vecUnion.vecStruct.y - vOther.vecUnion.vecStruct.y;
	delta.vecUnion.vecStruct.z = vecUnion.vecStruct.z - vOther.vecUnion.vecStruct.z;

	return delta.LengthSqr();
}

template <typename T>
FORCE_INLINE T Vec3<T>::DistTo(const Vec3<T> &vOther) const
{
	//CHECK_VALID(*this);
	return std::sqrt((vecUnion.vecStruct.x - vOther.vecUnion.vecStruct.x) * (vecUnion.vecStruct.x - vOther.vecUnion.vecStruct.x) + (vecUnion.vecStruct.y - vOther.vecUnion.vecStruct.y) * (vecUnion.vecStruct.y - vOther.vecUnion.vecStruct.y) + (vecUnion.vecStruct.z - vOther.vecUnion.vecStruct.z) * (vecUnion.vecStruct.z - vOther.vecUnion.vecStruct.z));
}

template <typename T>
inline void Vec3<T>::NormalizeInPlace()
{
	Vec3<T> &vOther = *this;

	T iradius = 1.f / (this->Length() + 1.192092896e-07F); //FLT_EPSILON

	vOther.vecUnion.vecStruct.x *= iradius;
	vOther.vecUnion.vecStruct.y *= iradius;
	vOther.vecUnion.vecStruct.z *= iradius;
}

template <typename T>
inline Vec3<T> Vec3<T>::operator+(const Vec3<T> &vOther) const
{
	Vec3<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x + vOther.vecUnion.vecStruct.x;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y + vOther.vecUnion.vecStruct.y;
	res.vecUnion.vecStruct.z = vecUnion.vecStruct.z + vOther.vecUnion.vecStruct.z;
	return res;
}

template <typename T>
inline Vec3<T> Vec3<T>::operator-(const Vec3<T> &vOther) const
{
	Vec3<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x - vOther.vecUnion.vecStruct.x;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y - vOther.vecUnion.vecStruct.y;
	res.vecUnion.vecStruct.z = vecUnion.vecStruct.z - vOther.vecUnion.vecStruct.z;
	return res;
}

template <typename T>
inline Vec3<T> Vec3<T>::operator+(T fl) const
{
	Vec3<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x + fl;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y + fl;
	res.vecUnion.vecStruct.z = vecUnion.vecStruct.z + fl;
	return res;
}

template <typename T>
inline Vec3<T> Vec3<T>::operator-(T fl) const
{
	Vec3<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x - fl;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y - fl;
	res.vecUnion.vecStruct.z = vecUnion.vecStruct.z - fl;
	return res;
}

template <typename T>
inline Vec3<T> Vec3<T>::operator*(T fl) const
{
	Vec3<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x * fl;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y * fl;
	res.vecUnion.vecStruct.z = vecUnion.vecStruct.z * fl;
	return res;
}

template <typename T>
inline Vec3<T> Vec3<T>::operator*(const Vec3<T> &vOther) const
{
	Vec3<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x * vOther.vecUnion.vecStruct.x;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y * vOther.vecUnion.vecStruct.y;
	res.vecUnion.vecStruct.z = vecUnion.vecStruct.z * vOther.vecUnion.vecStruct.z;
	return res;
}

template <typename T>
inline Vec3<T> Vec3<T>::operator/(T fl) const
{
	Vec3<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x / fl;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y / fl;
	res.vecUnion.vecStruct.z = vecUnion.vecStruct.z / fl;
	return res;
}

template <typename T>
inline Vec3<T> Vec3<T>::operator/(const Vec3<T> &vOther) const
{
	Vec3<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x / vOther.vecUnion.vecStruct.x;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y / vOther.vecUnion.vecStruct.y;
	res.vecUnion.vecStruct.z = vecUnion.vecStruct.z / vOther.vecUnion.vecStruct.z;
	return res;
}

template <typename T>
inline T Vec3<T>::Dot(const Vec3<T> &vOther) const
{
	const Vec3<T> &a = *this;

	return (a.vecUnion.vecStruct.x * vOther.vecUnion.vecStruct.x + a.vecUnion.vecStruct.y * vOther.vecUnion.vecStruct.y + a.vecUnion.vecStruct.z * vOther.vecUnion.vecStruct.z);
}
} // namespace art

namespace std
{
template <typename T>
class numeric_limits<art::Vec3<T>>
{
public:
	static art::Vec3<T> max() { return art::Vec3<T>(std::numeric_limits<T>::max()); }
	static art::Vec3<T> min() { return art::Vec3<T>(std::numeric_limits<T>::min()); }
	static art::Vec3<T> lowest() { return art::Vec3<T>(std::numeric_limits<T>::lowest()); }
};
} // namespace std

#endif //_VEC3_H_