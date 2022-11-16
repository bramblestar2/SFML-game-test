#pragma once
#include <iostream>
#include <fstream>

template<typename T>
struct Vec2
{
	T x, y;

	Vec2(T _x, T _y) { x = _x; y = _y; }
	Vec2() { x = 0; y = 0; }

	Vec2& operator+=(const Vec2& right) {
		this->x += right.x;
		this->y += right.y;
		return *this;
	}

	bool operator==(const Vec2& right) {
		return	this->x == right.x &&
			this->y == right.y;
	}

	bool operator!=(const Vec2& right) {
		return	this->x != right.x ||
			this->y != right.y;
	}

	friend std::fstream& operator<<(std::fstream& a, const Vec2& vec)
	{
		a << vec.x << " " << vec.y;
		return a;
	}
};

typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;
typedef Vec2<int> Vec2i;

template<typename T>
struct Vec3
{
public:
	T x, y, z;

	Vec3(T _x,T _y,T _z) { x = _x, y = _y, z = _z; }
	Vec3() { x = 0, y = 0, z = 0; }

	Vec3& operator+=(const Vec3& right) {
		this->x += right.x;
		this->y += right.y;
		this->z += right.z;
		return *this;
	}

	friend std::fstream& operator<<(std::fstream& a, const Vec3& vec)
	{
		a << vec.x << " " << vec.y << " " << vec.z;
		return a;
	}
};

typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;
typedef Vec3<int> Vec3i;

struct ID
{
public:
	ID(const std::string);
	ID();
	int id;
	Vec3f color;
	
	//returns the type name
	//ex: "Block", "Player", "Enemy"
	std::string getType() const { return type; }
private:
	std::string type;

	friend std::fstream& operator<<(std::fstream& a, const ID& id)
	{
		a << id.type << " " << id.id << " " << id.color.x << " " << id.color.y << " " << id.color.z;
		return a;
	}
};

