#pragma once
#pragma once

#include "ECommon.h"
#include<Windows.h>

namespace E3D
{
	extern HINSTANCE GHInstance;

	// 图片封装，由于图片使用的gdi+的图片类
	// 所以这里对它进行封装,将平台相关的东西隐藏

	class EBitmap
	{
	public:
		EInt width, height;
		EBitmap(const EString &filename);
		EBitmap();

		inline EString getName() const { return name; }
		inline bool isValid()const { return valid; }
		EColor getPixel(EInt x, EInt y);
		inline EInt getHeight()const { return height; }
		inline EInt getWidth()const { return width; }

	private:
		EString name;

		HBITMAP hBitmap;
		BITMAP bitmap;
		HDC bitmapHDC;

	public:
		EColor *pixels;
		EInt pitch;
		EBool valid;

	};

	class EGraphics
	{
	public :
		//初始化绘图系统
		static bool initGraphics(HINSTANCE hinstance);
		
		// 关闭绘图系统
		static void shutdownGraphics();

		//检测z值，返回true 则表示通过,可以调用setpixel
		static EBool CheckZ(EInt x, EInt y, EFloat z);
		static void setPixel(EInt x, EInt y,/*EFloat z,*/const EColor &c);
		static EColor getPixel(EInt x, EInt y);

		//在当前缓冲区内绘制一条线
		static void drawLine(EInt x0, EInt y0, EInt x1, EInt y1, const EColor &c);

		//绘制字符串
		static void drawString(const EString &str, EInt x, EInt y, const EColor &c = EColor(255, 255, 255));

		//填充三角形
		static void fillTriangle(EInt x0, EInt y0, EInt x1, EInt y1, EInt x2, EInt y2, const EColor &c = EColor(255, 255, 255));

		//平滑模式
		static void enableSmoothingMode(EBool enable);

		//清空当前缓冲区,并将其颜色设置为黑色
		static void clearBuffer(const EColor &c = EColor());

		//将已经绘制好的缓冲区递交给graphics在屏幕上绘制,并将当前缓冲区设置为另一个缓冲区
		static void fillBuffer(HDC hdc);
		
		//获得屏幕的宽和高
		static EInt getScreenWidth() { return SCREEN_WIDTH;};
		static EInt getScreenHeight() { return SCREEN_HEIGHT; };

	private:

		// 设置缓冲区
		static HBITMAP GBufferedHandle;
		static HDC GBufferedHDC;
		static HBRUSH GBgBrush;
		static HPEN GPen;
		static HINSTANCE GInstance;

		static BYTE *GDatas;
		static EInt GPitch;

		static DIBSECTION GDIBSection;
		static RECT GBufferSize;
		static EFloat *GZBuffer;

	};



}

