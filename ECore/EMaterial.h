#pragma once
#include "ECommon.h"
#include<map>
#include "EGraphics.h"

namespace E3D
{
	struct  EMaterial
	{
		EString name;
		EColor ambient;			// 环境色
		EColor diffuse;			// 漫反射颜色
		EColor specular;		// 镜面反射

		EBitmap *bitmap;

		EMaterial();
		~EMaterial();
		inline bool uesTexture() { return bitmap && bitmap->isValid; }
		EColor getPixel(EFloat u, EFloat v);

	};

	typedef std::map<EString, EMaterial*>::iterator Materiallter;
	extern std::map<EString, EMaterial*>*GMaterial;

	extern EMaterial *GetMaterial(const EString & name);
	extern bool SetMaterial(const EString &name, EMaterial *material);
	extern bool DestroyMaterial(const EString &name);
	extern void DestroyAllMaterial();

	//解析材质脚本，读取基本材质和贴图
	//材质脚本必须和模型名字相同,如ogreHead.mesh ogreHead.material
	extern void ParseMaterialScript(const EString & scriptName);
}



