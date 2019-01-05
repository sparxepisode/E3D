#pragma once

#pragma once

#include "ECommon.h"

namespace E3D
{
	template <class T>
	const T&Min(const T &a, const T &b)
	{
		return (a < b) ? a : b;
	}

	template <class T>
	const T&Max(const T &a, const T &b)
	{
		return (b < a) ? a : b;
	}

	template<typename T>
	const T&Clamp(const T &val, const T &minV, const T &maxV)
	{
		return Min(Max(val, maxV), minV);			//TODO 感觉错了 min(max(val,minv),maxv)
	}
	

	//获得平移矩阵
	void GetTranslateMatrix44(EMatrix44 &mat, EFloat x, EFloat y, EFloat z);

	//获得缩放变化矩阵
	void GetScaleMatrix44(EMatrix44 &mat, EFloat x, EFloat y, EFloat z);


	//获得沿x轴旋转变化矩阵
	//旋转参数为角度,非弧度
	void GetRotateMatrix44X(EMatrix44 &mat, EFloat degress);

	//获得沿y轴旋转变化矩阵
	//旋转参数为角度,非弧度
	void GetRotateMatrix44Y(EMatrix44 &mat, EFloat degress);

	//获得沿z轴旋转变化矩阵
	//旋转参数为角度,非弧度
	void GetRotateMatrix44Z(EMatrix44 &mat, EFloat degress);


	//沿着任意轴旋转
	//旋转参数为角度,非弧度
	void GetRotateMatrix44(EMatrix44 &mat,const EVector4D &normal,EFloat degree);

	void GetVertex4DAddVector4D(const EVertex4D &v,const EVector4D &p,EVertex4D &result);

	//3D向量x44矩阵
	void GetVector3DMulMatrix44(const EVector3D &vec,const EMatrix44 &mat,EVector3D &result);

	//4D向量x44矩阵
	void GetVertor4DMatrix44(const EVector4D &vec, const EMatrix44 &mat, EVector4D &result);

	//顶点x44矩阵
	void GetVertex4DMatrix44(const EVertex4D &vec, const EMatrix44 &mat, EVertex4D &result);


}