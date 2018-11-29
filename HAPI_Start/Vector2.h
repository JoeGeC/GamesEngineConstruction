#ifndef VECTOR2_H
#define VECTOR2_H

#include <ostream>

using namespace std;

class Vector2
{
public:
	Vector2() {};
	~Vector2() {};
	Vector2(float x, float y) : x(x), y(y) {};
	Vector2(const Vector2& other) : x(other.x), y(other.y) {};

	float x{ 0 };
	float y{ 0 };
	
	void operator+=(const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
	}

	void operator-=(const Vector2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
	}

	friend Vector2 operator+(Vector2 lhs, const Vector2& rhs);
	friend Vector2 operator-(Vector2 lhs, const Vector2& rhs);
	friend Vector2 operator*(Vector2 lhs, float rhs);
	friend Vector2 operator/(Vector2 lhs, float rhs);
	friend ostream& operator<<(ostream& os, const Vector2& rhs);

protected:

private:
	
};

inline Vector2 operator+(Vector2 lhs, const Vector2& rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	return lhs;
}

inline Vector2 operator-(Vector2 lhs, const Vector2& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	return lhs;
}

inline Vector2 operator*(Vector2 lhs, float rhs)
{
	lhs.x *= rhs;
	lhs.y *= rhs;
	return lhs;
}

inline Vector2 operator/(Vector2 lhs, float rhs)
{
	lhs.x /= rhs;
	lhs.y /= rhs;
	return lhs;
}

inline ostream& operator<<(ostream& os, const Vector2& rhs)
{
	os << "x: " << rhs.x << ", y: " << rhs.y << endl;
	return os;
}

#endif // VECTOR2_H