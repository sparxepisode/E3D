#include "stdafx.h"
#include "EGraphics.h"
#include "EUtil.h"

namespace E3D 
{
	EBitmap::EBitmap(const EString& filename) :name(filename), pixels(NULL), pitch(0), width(0), height(0), valid(false)
	{

		// 材质脚本,首先获取默认路径
		hBitmap = (HBITMAP)::LoadImage(GHInstance, GetPath(filename).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		if (hBitmap != NULL)
		{
			bitmapHDC = ::CreateCompatibleDC(NULL);
			::SelectObject(bitmapHDC, (HGDIOBJ)hBitmap);
			::GetObject(hBitmap, sizeof(BITMAP), &bitmap);

			width = bitmap.bmWidth;
			height = bitmap.bmHeight;
			pitch = bitmap.bmHeight;
			valid = true;

			pixels = new EColor[width*height];
			for (EInt i = 0; i < getHeight(); i++)
			{
				for (EInt j = 0; j <getWidth();i++)
				{
					COLORREF color = ::GetPixel(bitmapHDC, i, j);
					pixels[j*width + i] = EColor(GetRValue(color), GetGValue(color), GetBValue(color));
				}
			}
		}
	}

	// 析构函数
	EBitmap::EBitmap()
	{
		DeleteObject(hBitmap);
		DeleteDC(bitmapHDC);
		SafeDeleteArray(pixels);
	}

	//获取像素
	EColor EBitmap::getPixel(EInt x, EInt y)
	{
		return pixels[y*pitch + x];
	}

	HINSTANCE GHInstance;

	HBITMAP		EGraphics::GBufferedHandle;
	HDC			EGraphics::GBufferedHDC;
	HBRUSH		EGraphics::GBgBrush;
	HPEN		EGraphics::GPen;
	HINSTANCE	EGraphics::GInstance;
	RECT		EGraphics::GBufferSize;
	DIBSECTION	EGraphics::GDIBSection;
	BYTE		*EGraphics::GDatas;
	EInt		EGraphics::GPitch;
	
	EFloat		*EGraphics::GZBuffer;


	bool EGraphics::initGraphics(HINSTANCE hinstance)
	{
		GBufferedHDC = ::CreateCompatibleDC(NULL);

		BITMAPINFO info = { 0 };
		info.bmiHeader.biSize = sizeof(info.bmiHeader);
		info.bmiHeader.biWidth = SCREEN_WIDTH;
		info.bmiHeader.biHeight = SCREEN_HEIGHT;
		info.bmiHeader.biPlanes = 1;
		info.bmiHeader.biBitCount = 32;
		info.bmiHeader.biCompression = BI_RGB;
		info.bmiHeader.biSizeImage = SCREEN_WIDTH * SCREEN_HEIGHT * 32 / 8;

		//创建一块内存纹理并获取其数据指针

		void*pBits = NULL;
		GBufferedHandle = ::CreateDIBSection(GBufferedHDC, &info, DIB_RGB_COLORS, &pBits, NULL, 0);

		::SelectObject(GBufferedHDC, GBufferedHandle);

		// 这里: "dib.sdbm.bmbits" 将指向 hdib的像素
		::GetObject(GBufferedHandle, sizeof(DIBSECTION), &GDIBSection);
		GDatas = (BYTE*)GDIBSection.dsBm.bmBits;
		GPitch = GDIBSection.dsBm.bmWidthBytes;

		::SetRect(&GBufferSize, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		
		GPen = ::CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		::SelectObject(GBufferedHDC, GPen);

		GBgBrush = ::CreateSolidBrush(RGB(0, 0, 0));
		::SelectObject(GBufferedHDC, GBgBrush);

		HFONT hfnt = (HFONT)::GetStockObject(OEM_FIXED_FONT);
		::SelectObject(GBufferedHDC, hfnt);

		// 设置文字背景为透明色
		::SetBkMode(GBufferedHDC, TRANSPARENT);

		GZBuffer = new EFloat[SCREEN_WIDTH*SCREEN_HEIGHT];
		memset(GZBuffer, 0, sizeof(EFloat)*SCREEN_WIDTH*SCREEN_HEIGHT);

		return true;

	}

	//关闭绘图系统
	void EGraphics::shutdownGraphics()
	{
		::DeleteObject(GPen);
		::DeleteObject(GBgBrush);
		::DeleteObject(GBufferedHandle);
		::DeleteDC(GBufferedHDC);
	}

	//清空当前缓冲区 ,并将其颜色设置为黑色
	void EGraphics::clearBuffer(const EColor &c)
	{
		::FillRect(GBufferedHDC, &GBufferSize, GBgBrush);
		//重置深度缓存
		//注意,这里的memset只能对int 类型的数组进行初始化,所以直接使用了int 类型
		// 而没有使用float 类型,应该使用float
		::memset(GZBuffer, 0, sizeof(EFloat)*SCREEN_WIDTH*SCREEN_HEIGHT);

	}

	// 在当前缓冲区内绘制一条线
	void EGraphics::drawLine(EInt x0, EInt y0, EInt x1, EInt y1, const EColor &c)
	{
		::SelectObject(GBufferedHDC, GetStockObject(DC_PEN));
		::SetDCPenColor(GBufferedHDC, RGB(c.r, c.g, c.b));

		::MoveToEx(GBufferedHDC, x0, y0, NULL);
		::LineTo(GBufferedHDC, x1, y1);

		//:: deleteobject(hpen);
	}

	// 绘制字符串
	void EGraphics::drawString(const EString& str, EInt x, EInt y, const EColor &c)
	{
		::SetTextColor(GBufferedHDC, RGB(c.r, c.g, c.b));
		::TextOut(GBufferedHDC, x, y, str.c_str(), str.length);
	}


	void EGraphics::fillTriangle(EInt x0, EInt y0, EInt x1, EInt y1, EInt x2, EInt y2, const EColor &c)
	{

	}

	void EGraphics::enableSmoothingMode(EBool enable)
	{

	}

	//检查 z深度值
	EBool EGraphics::CheckZ(EInt x, EInt y, EFloat z)
	{
		// 这里z应该使用float 类型来存储,如果使用int 类型, 那么会导致精度丢失
		// 产生错误的现象
		EInt index = y * SCREEN_WIDTH + x;
		EFloat divZ = 1.0f / z;

		//这里是已于1/z做的比较
		if (GZBuffer[index] > divZ)
			return false;

		GZBuffer[index] = divZ;
		return true;
	}

	void EGraphics::setPixel(EInt x, EInt y,const EColor &c)
	{
		BYTE* pSrcPix = GDatas + (GPitch*y);
		pSrcPix += x * 4;

		// 颜色赋值，绿,蓝,红,透明度
		pSrcPix[0] = c.b;
		pSrcPix[1] = c.g;
		pSrcPix[2] = c.r;
		pSrcPix[3] = c.a;
	}


	EColor EGraphics::getPixel(EInt x, EInt y)
	{
		BYTE* pSrcPix = GDatas + (GPitch*y);
		pSrcPix += x * 4;
		return EColor(pSrcPix[2], pSrcPix[1], pSrcPix[0]);

	}

	// 将已经绘制好的缓冲区递交给graphics在屏幕上绘制,并将当前缓冲区设置为另一个缓冲区
	void EGraphics::fillBuffer(HDC hdc)
	{
		::BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GBufferedHDC, 0, 0, SRCCOPY);
	}


}

