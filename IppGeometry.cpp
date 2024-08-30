#include "IppGeometry.h"

void IppTranslate(IppByteImage& imgSrc, IppByteImage& imgDst, int sx, int sy)
{

	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(w, h);

	BYTE** pSrc = imgSrc.GetPixels2D();
	BYTE** pDst = imgDst.GetPixels2D();

	int i, j, x, y;
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			x = i - sx;
			y = j - sy;

			if (x >= 0 && x < w && y >= 0 && y < h) {
				pDst[j][i] = pSrc[y][x];
			}
		}
	}

}

void IppResizeNearest(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(nw, nh);

	BYTE** pSrc = imgSrc.GetPixels2D();
	BYTE** pDst = imgDst.GetPixels2D();

	int i, j, x, y;
	double rx, ry; //입력 영상에서 참조할 픽셀값의 실수 좌표

	for (j = 0; j < nh; j++) {
		for (i = 0; i < nw; i++) {

			rx = static_cast<double>(w - 1) * i / (nw - 1);
			ry = static_cast<double>(h - 1) * j / (nh - 1);
			x = static_cast<int>(rx + 0.5);
			y = static_cast<int>(ry + 0.5);

			if (x >= w) x = w - 1;
			if (y >= h) y = h - 1;

			pDst[j][i] = pSrc[y][x];
		}
	}

}

void IppResizeBilinear(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(nw, nh);

	BYTE** pSrc = imgSrc.GetPixels2D();
	BYTE** pDst = imgDst.GetPixels2D();

	int i, j;
	double rx, ry; //입력 영상에서 참조할 픽셀값의 실수 좌표
	int x1, y1, x2, y2;//rx, ry를 둘러싼 4개의 픽셀 좌표
	double p, q, value;

	for (j = 0; j < nh; j++) {
		for (i = 0; i < nw; i++) {
			rx = static_cast<double>(w - 1) * i / (nw - 1);
			ry = static_cast<double>(h - 1) * j / (nh - 1);

			x1 = static_cast<double>(rx);
			y1 = static_cast<double>(ry);

			x2 = x1 + 1; if (x2 == w) x2 = w - 1;
			y2 = y1 + 1; if (y2 == h) y2 = h - 1;

			p = rx - x1;
			q = ry - y1;

			value = (1. - p) * (1. - q) * pSrc[y1][x1]
				+ p * (1. - q) * pSrc[y1][x2]
				+ (1. - p) * q * pSrc[y2][x1]
				+ p * q * pSrc[y2][x2];

			pDst[j][i] = static_cast<BYTE>(limit(value + 0.5));
		}
	}// for


}

void IppRotate180(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(w, h);

	BYTE** pSrc = imgSrc.GetPixels2D();
	BYTE** pDst = imgDst.GetPixels2D();

	int i, j;
	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			pDst[j][i] = pSrc[h - 1 - j][w - 1 - i];
		}

}

void IppRotate270(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	IppByteImage cpy = imgSrc;

	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(h, w);

	BYTE** pSrc = imgSrc.GetPixels2D();
	BYTE** pDst = imgDst.GetPixels2D();

	int i, j;
	for (j = 0; j < w; j++)
		for (i = 0; i < h; i++)
		{
			pDst[j][i] = pSrc[i][w - 1 - j];
		}

}

void IppMirror(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(w, h);

	BYTE** pSrc = imgSrc.GetPixels2D();
	BYTE** pDst = imgDst.GetPixels2D();

	int i, j;
	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			pDst[j][i] = pSrc[j][w - 1 - i];
		}
}

void IppFlip(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(w, h);

	BYTE** pSrc = imgSrc.GetPixels2D();
	BYTE** pDst = imgDst.GetPixels2D();

	int i, j;
	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			pDst[j][i] = pSrc[h - 1 - j][i];
		}

}

void IppRotate90(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(h, w);

	BYTE** pSrc = imgSrc.GetPixels2D();
	BYTE** pDst = imgDst.GetPixels2D();

	int i, j;
	for (j = 0; j < w; j++)
		for (i = 0; i < h; i++)
		{
			pDst[j][i] = pSrc[h - 1 - i][j];
		}
}
