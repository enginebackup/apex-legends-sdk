#pragma once
#include <map>

#define M_PI 3.14159265358979323846

float bog2grd(float BOG) {
	return (180 / M_PI) * BOG;
}

float grd2bog(float GRD) {
	return (M_PI / 180) * GRD;
}

double rad2deg(double rad) {
	return rad * 180 / M_PI;
}

double deg2rad(double deg) {
	return deg * M_PI / 180;
}

class c_vec2
{
public:
	float x, y;

	c_vec2() = default;

	c_vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	};

	bool is_valid()
	{
		return (x != 0 && y != 0);
	}

	/*float length() const
	{
		return std::sqrt((x * x) + (y * y));
	}*/

	float distance(c_vec2 b)
	{
		return sqrt(pow(b.x - x, 2) + pow(b.y - y, 2));
	}

	void normalize()
	{

		if (x < -89)
			x = -89;


		else if (x > 89)
			x = 89;


		if (y < -360)
			y += 360;


		else if (y > 360)
			y -= 360;
	}

	c_vec2 operator+(const c_vec2& input)
	{
		return c_vec2{ x + input.x, y + input.y };
	}

	c_vec2& operator*=(float input)
	{
		x *= input;
		y *= input;
		return *this;
	}
};

class c_vec3
{
public:
	c_vec3()
	{
		x = y = z = 0.f;
	}

	c_vec3(float fx, float fy, float fz)
	{
		x = fx;
		y = fy;
		z = fz;
	}

	float x, y, z;

	c_vec3 operator+(const c_vec3& input) const
	{
		return c_vec3{ x + input.x, y + input.y, z + input.z };
	}

	c_vec3 operator-(const c_vec3& input) const
	{
		return c_vec3{ x - input.x, y - input.y, z - input.z };
	}

	c_vec3 operator/(float input) const
	{
		return c_vec3{ x / input, y / input, z / input };
	}

	c_vec3 operator*(float input) const
	{
		return c_vec3{ x * input, y * input, z * input };
	}

	c_vec3& operator+=(const c_vec3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	c_vec3& operator-=(const c_vec3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	c_vec3& operator/=(float input)
	{
		x /= input;
		y /= input;
		z /= input;
		return *this;
	}

	c_vec3& operator*=(float input)
	{
		x *= input;
		y *= input;
		z *= input;
		return *this;
	}

	bool operator==(const c_vec3& input) const
	{
		return x == input.x && y == input.y && z == input.z;
	}

	void make_absolute()
	{
		x = std::abs(x);
		y = std::abs(y);
		z = std::abs(z);
	}

	float clamp0to1(float value)
	{
		float result;
		if (value < 0)
		{
			result = 0;
		}
		else if (value > 1.f)
		{
			result = 1.f;
		}
		else
		{
			result = value;
		}
		return result;
	}

	float lerp()
	{
		return x + (y - x) * clamp0to1(z);
	}

	float length_sqr() const
	{
		return (x * x) + (y * y) + (z * z);
	}

	float length() const
	{
		return (float)sqrt(length_sqr());
	}

	float length_2d() const
	{
		return (float)sqrt((x * x) + (y * y));
	}

	c_vec3 normalize()
	{
		c_vec3 out = *this;
		auto len = length();
		if (!len)
			return *this;

		out.x /= len;
		out.y /= len;
		out.z /= len;
		return out;
	}

	c_vec3 cross(c_vec3 rhs)
	{
		return c_vec3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
	}

	float unity_magnitude()
	{
		return (float)sqrt((double)(x * x + y * y + z * z));
	}

	c_vec3 unity_normalize()
	{
		float num = unity_magnitude();
		if (num > 1E-05f)
		{
			x /= num;
			y /= num;
			z /= num;
		}
		else
		{
			x = 0;
			y = 0;
			z = 0;
		}

		return { x,y,z };
	}

	c_vec3 normalized() const
	{
		return { x == 0 ? 0 : x / length(), y == 0 ? 0 : y / length(), z == 0 ? 0 : z / length() };
	}

	float dot(c_vec3 input) const
	{
		return (x * input.x) + (y * input.y) + (z * input.z);
	}

	float distance(c_vec3 input) const
	{
		return (*this - input).length();
	}

	float distancesqr(c_vec3 input) const
	{
		c_vec3 dif = { x - input.x, y - input.y, z - input.z };
		return dif.x * dif.x + dif.y * dif.y + dif.z * dif.z;
	}

	float distance_2d(c_vec3 input) const
	{
		return (*this - input).length_2d();
	}

	/*void clamp()
	{
		static_cast<void>(std::clamp(x, -89.f, 89.f));
		static_cast<void>(std::clamp(y, -180.f, 180.f));
		z = 0.f;
		return;
	}*/

	bool is_valid() const
	{
		return !(x == 0.f && y == 0.f && z == 0.f) || (x == -1.f && y == -1.f && z == -1.f);
	}
};

class c_vec4
{
public:
	c_vec4()
	{
		x = y = z = w = 0.f;
	}

	c_vec4(float fx, float fy, float fz, float fw)
	{
		x = fx;
		y = fy;
		z = fz;
		w = fw;
	}

	float x, y, z, w;

	c_vec4 operator+(const c_vec4& input) const
	{
		return c_vec4{ x + input.x, y + input.y, z + input.z, w + input.w };
	}

	c_vec4 operator-(const c_vec4& input) const
	{
		return c_vec4{ x - input.x, y - input.y, z - input.z, w - input.w };
	}

	c_vec4 operator/(float input) const
	{
		return c_vec4{ x / input, y / input, z / input, w / input };
	}

	c_vec4 operator*(float input) const
	{
		return c_vec4{ x * input, y * input, z * input, w * input };
	}

	c_vec4& operator-=(const c_vec4& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;

		return *this;
	}

	c_vec4& operator/=(float input)
	{
		x /= input;
		y /= input;
		z /= input;
		w /= input;
		return *this;
	}

	c_vec4& operator*=(float input)
	{
		x *= input;
		y *= input;
		z *= input;
		w *= input;
		return *this;
	}

	bool operator==(const c_vec4& input) const
	{
		return x == input.x && y == input.y && z == input.z && w == input.w;
	}

	void make_absolute()
	{
		x = std::abs(x);
		y = std::abs(y);
		z = std::abs(z);
		w = std::abs(w);
	}

	float length_sqr() const
	{
		return (x * x) + (y * y) + (z * z) + (w * w);
	}

	float length() const
	{
		return (float)sqrt(length_sqr());
	}

	float length_2d() const
	{
		return (float)sqrt((x * x) + (y * y));
	}

	c_vec4 normalized() const
	{
		return { x / length(), y / length(), z / length(), w / length() };
	}

	float dot(c_vec4 input) const
	{
		return (x * input.x) + (y * input.y) + (z * input.z) + (w * input.w);
	}

	float distance(c_vec4 input) const
	{
		return (*this - input).length();
	}

	float distance_2d(c_vec4 input) const
	{
		return (*this - input).length_2d();
	}
	/*void clamp()
	{
		static_cast<void>(std::clamp(x, -89.f, 89.f));
		static_cast<void>(std::clamp(y, -180.f, 180.f));

		z = 0.f;
		w = 0.f;
	}*/

	static c_vec4 QuaternionLookRotation(c_vec3 forward, c_vec3 up)
	{
		c_vec3 vector = forward.unity_normalize();
		c_vec3 c_vec2 = (up).cross(vector).unity_normalize();
		c_vec3 c_vec3 = (vector).cross(c_vec2);
		auto m00 = c_vec2.x;
		auto m01 = c_vec2.y;
		auto m02 = c_vec2.z;
		auto m10 = c_vec3.x;
		auto m11 = c_vec3.y;
		auto m12 = c_vec3.z;
		auto m20 = vector.x;
		auto m21 = vector.y;
		auto m22 = vector.z;


		float num8 = (m00 + m11) + m22;
		auto quaternion = c_vec4();
		if (num8 > 0.f)
		{
			auto num = (float)sqrt(num8 + 1.f);
			quaternion.w = num * 0.5f;
			num = 0.5f / num;
			quaternion.x = (m12 - m21) * num;
			quaternion.y = (m20 - m02) * num;
			quaternion.z = (m01 - m10) * num;
			return quaternion;
		}
		if ((m00 >= m11) && (m00 >= m22))
		{
			auto num7 = (float)sqrt(((1.f + m00) - m11) - m22);
			auto num4 = 0.5f / num7;
			quaternion.x = 0.5f * num7;
			quaternion.y = (m01 + m10) * num4;
			quaternion.z = (m02 + m20) * num4;
			quaternion.w = (m12 - m21) * num4;
			return quaternion;
		}
		if (m11 > m22)
		{
			auto num6 = (float)sqrt(((1.f + m11) - m00) - m22);
			auto num3 = 0.5f / num6;
			quaternion.x = (m10 + m01) * num3;
			quaternion.y = 0.5f * num6;
			quaternion.z = (m21 + m12) * num3;
			quaternion.w = (m20 - m02) * num3;
			return quaternion;
		}
		auto num5 = (float)sqrt(((1.f + m22) - m00) - m11);
		auto num2 = 0.5f / num5;
		quaternion.x = (m20 + m02) * num2;
		quaternion.y = (m21 + m12) * num2;
		quaternion.z = 0.5f * num5;
		quaternion.w = (m01 - m10) * num2;
		return quaternion;
	}

	bool is_valid() const
	{
		return !((x == 0.f && y == 0.f && z == 0.f && w == 0.f) || (x == -1.f && y == -1.f && z == -1.f && w == -1.f));
	}
};

c_vec2 calculate_angle(c_vec3 source, c_vec3 destination)
{
	c_vec3 difference = source - destination;
	float length = difference.length();

	c_vec2 ret{};

	ret.y = asinf(difference.y / length);
	ret.x = -atan2f(difference.x, -difference.z);

	ret = { ret.x * 57.29578f, ret.y * 57.29578f };

	return ret;
}

float normalize_angle(float angle)
{
	while (angle > 360) angle -= 360;
	while (angle < 0) angle += 360;
	return angle;
}

c_vec2 rotate_point(c_vec2 point_to_rotate, c_vec2 center_point, float angle)
{
	float rad = ((normalize_angle(angle)) * static_cast<float>((M_PI / 180.f)));
	float s = -sin(rad);
	float c = cos(rad);
	float xnew = point_to_rotate.x * c - point_to_rotate.y * s;
	float znew = point_to_rotate.x * s + point_to_rotate.y * c;
	point_to_rotate.x -= center_point.x;
	point_to_rotate.y -= center_point.y;
	point_to_rotate.x = xnew + center_point.x;
	point_to_rotate.y = znew + center_point.y;
	return point_to_rotate;
}

inline float dist(const c_vec3 p1, const c_vec3 p2)
{
	float x = p1.x - p2.x;
	float y = p1.y - p2.y;
	float z = p1.z - p2.z;
	return sqrt(x * x + y * y + z * z);
}

struct vmatrix_t
{
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};