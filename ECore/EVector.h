#pragma once

#include "ECommon.h"
#include "EMath.h"
#include "EUtil.h"


namespace E3D
{
	// 2D向量: VECTOR2D_TYP
	struct EVector2D
	{
		static EVector2D ZERO;
		static EVector2D UNIT_X;
		static EVector2D UNIT_Y;

		EFloat x;
		EFloat y;

		EVector2D() :x(0), y(0) {}
		EVector2D(EFloat x, EFloat y) :x(x), y(y) {}
		EVector2D(const EVector2D& v) :x(v.x), y(v.y) {}

		// 将向量规范化
		inline EFloat normalize()
		{
			EFloat len = length();
			if (len > EPSILON_E6)
			{
				EFloat invLength = 1.0f / len;
				x *= invLength;
				y *= invLength;

			}
			return len;
		}

		// 向量的点乘
		inline EFloat dotProduct(const EVector2D& right)const
		{
			return x * right.x + y * right.y;
		}

		inline EFloat angleBetween(const EVector2D& right)const
		{
			EFloat lenProduct = length()* right.length();

			if (lenProduct < EPSILON_E6)
				lenProduct = EPSILON_E6;

			EFloat f = dotProduct(right) / lenProduct;
			f = Clamp(f, -1.0f, 1.0f);

			return acos(f);
		}



		// 返回向量长度
		inline EFloat length()const 
		{
			return sqrt(x*x + y * y);
		}

		// 返回长度的平方
		inline EFloat SquaredLength()const 
		{
			return x * x + y * y;
		}
		
		// 向量与数的乘法
		inline EVector2D operator*(float right)const
		{
			return EVector2D(x*right, y*right);
		}

		// 向量点积
		inline EVector2D operator*(const EVector2D& right)const
		{
			return EVector2D(x*right.x, y *right.y);
		}
		
		// 向量加法
		inline EVector2D operator+(const EVector2D& right)const
		{
			return EVector2D(x + right.x, y + right.y);
		}

		// 向量减法
		inline EVector2D operator-(const EVector2D& right)const
		{
			return EVector2D(x - right.x, y - right.y);
		}

		// 向量取反
		inline EVector2D operator-()
		{
			x = -x;
			y = -y;
			return *this;
		}

		// 向量取正
		inline EVector2D operator+()
		{
			x = +x;
			y = +y;
			return *this;
		}

		// 判断两个向量是不是相等
		inline bool operator==(const EVector2D& right)const
		{
			return EqualFloat(x, right.x) && EqualFloat(y, right.y);
		}

		// 向量的赋值
		inline EVector2D operator=(const EVector2D& right)
		{
			x = right.x;
			y = right.y;
			return *this;
		}

	};


	// 3D向量: VECTOR3D_TYP
	struct EVector3D
	{
		static EVector3D ZERO;
		static EVector3D UNIT_X;
		static EVector3D UNIT_Y;
		static EVector3D UNIT_Z;

		EFloat x;
		EFloat y;
		EFloat z;

		EVector3D() :x(0), y(0),z(0) {}
		EVector3D(EFloat x, EFloat y,EFloat z) :x(x), y(y),z(z) {}
		EVector3D(const EVector3D& v) :x(v.x), y(v.y),z(v.z) {}

		// 向量点积
		inline EFloat dotProduct(const EVector3D& right)const
		{
			return x * right.x+y*right.y+z*right.z;
		}

		// 向量叉积
		inline EVector3D crossProduct(const EVector3D& right)const
		{
			return EVector3D(y*right.z - z * right.y,
							z*right.x - x * right.z,
							x*right.y - y * right.x);
		}


		// 将向量规范化
		inline EFloat normalize()
		{
			EFloat len = length();
			if (len > EPSILON_E6)
			{
				EFloat invLength = 1.0f / len;
				x *= invLength;
				y *= invLength;
				z *= invLength;
			}
			return len;
		}

		// 返回两个向量之间的夹角,返回方式为弧度
		inline EFloat angleBetween(const EVector3D& right)const
		{
			EFloat lenProduct = length()* right.length();

			if (lenProduct < EPSILON_E6)
				lenProduct = EPSILON_E6;

			EFloat f = dotProduct(right) / lenProduct;

			return acos(f);
		}



		// 返回向量长度
		inline EFloat length()const
		{
			return sqrt(x*x + y * y+z*z);
		}

		// 返回长度的平方
		inline EFloat SquaredLength()const
		{
			return x * x + y * y+z*z;
		}

		// 向量与数的乘法
		inline EVector3D operator*(float right)const
		{
			return EVector3D(x*right, y*right,z*right);
		}

		// 向量点积
		inline EVector3D operator*(const EVector3D& right)const
		{
			return EVector3D(x*right.x, y *right.y,z*right.z);
		}

		// 向量加法
		inline EVector3D operator+(const EVector3D& right)const
		{
			return EVector3D(x + right.x, y + right.y,z+right.z);
		}

		// 向量减法
		inline EVector3D operator-(const EVector3D& right)const
		{
			return EVector3D(x - right.x, y - right.y,z-right.z);
		}

		// 向量取反
		inline EVector3D operator-()
		{
			x = -x;
			y = -y;
			z = -z;
			return *this;
		}

		// 向量取正
		inline EVector3D operator+()
		{
			x = +x;
			y = +y;
			z = +z;
			return *this;
		}

		// 判断两个向量是不是相等
		inline bool operator==(const EVector3D& right)const
		{
			return EqualFloat(x, right.x) && EqualFloat(y, right.y)&&EqualFloat(z,right.z);
		}

		// 向量的赋值
		inline EVector3D operator=(const EVector3D& right)
		{
			x = right.x;
			y = right.y;
			z = right.z;

			return *this;
		}

	};


	// 4D向量: VECTOR4D_TYP
	struct EVector4D
	{
		static EVector4D ZERO;
		static EVector4D UNIT_X;
		static EVector4D UNIT_Y;
		static EVector4D UNIT_Z;

		EFloat x;
		EFloat y;
		EFloat z;
		EFloat w;

		EVector4D() :x(0), y(0), z(0), w(1) {}
		EVector4D(EFloat xf, EFloat yf, EFloat zf, EFloat wf = 1) :x(xf), y(yf), z(zf), w(wf) {}
		EVector4D(const EVector4D& v) :x(v.x), y(v.y), z(v.z), w(v.w) {}


		// 向量点积
		inline EFloat dotProduct(const EVector4D& right)const
		{
			return x * right.x + y * right.y + z * right.z;
		}

		// 向量叉积
		inline EVector4D crossProduct(const EVector4D& right)const
		{
			return EVector4D(y*right.z - z * right.y,
				z*right.x - x * right.z,
				x*right.y - y * right.x, 1);
		}

		// 将向量规范化
		inline EFloat normalize()
		{
			EFloat len = length();
			if (len > EPSILON_E6)
			{
				EFloat invLength = 1.0f / len;
				x *= invLength;
				y *= invLength;
				z *= invLength;
				w = 1;
			}
			return len;
		}

		// 向量长度是否为零
		inline bool isZero()const
		{
			return length() < EPSILON_E6;
		}

		// 返回两个向量之间的夹角,返回方式为弧度
		inline EFloat angleBetween(const EVector4D& right)const
		{
			EFloat lenProduct = length()* right.length();

			if (lenProduct < EPSILON_E6)
				lenProduct = EPSILON_E6;

			EFloat f = dotProduct(right) / lenProduct;
			f = Clamp(f, -1.0f, 1.0f);

			return acos(f);
		}

		// 返回向量长度
		inline EFloat length()const
		{
			return sqrt(x*x + y * y + z * z);
		}

		// 返回长度的平方
		inline EFloat SquaredLength()const
		{
			return x * x + y * y + z * z;
		}

		// 向量与数的乘法
		inline EVector4D operator*(float right)const
		{
			return EVector4D(x*right, y*right, z*right, 1);
		}

		// 向量点积
		inline EVector4D operator*(const EVector4D& right)const
		{
			return EVector4D(x*right.x, y *right.y, z*right.z, 1);
		}

		// 向量加法
		inline EVector4D operator+(const EVector4D& right)const
		{
			return EVector4D(x + right.x, y + right.y, z + right.z, 1);
		}

		// 向量减法
		inline EVector4D operator-(const EVector4D& right)const
		{
			return EVector4D(x - right.x, y - right.y, z - right.z, 1);
		}

		// 向量取反
		inline EVector4D operator-()
		{
			return EVector4D(-x, -y, -z, w);
		}

		// 判断两个向量是不是相等
		inline bool operator==(const EVector4D& right)const
		{
			return EqualFloat(x, right.x) && EqualFloat(y, right.y) && EqualFloat(z, right.z) && EqualFloat(w, right.w);
		}

		// 向量的赋值
		inline EVector4D operator=(const EVector4D& right)
		{
			x = right.x;
			y = right.y;
			z = right.z;
			w = right.w;

			return *this;
		}

	};


}