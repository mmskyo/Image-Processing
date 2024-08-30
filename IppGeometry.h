#pragma once
#include "IppImage.h"

void IppTranslate(IppByteImage& imgSrc, IppByteImage& imgDst, int sx, int sy);
void IppResizeNearest(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh);
void IppResizeBilinear(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh);

void IppRotate90(IppByteImage& imgSrc, IppByteImage& imgDst);
void IppRotate180(IppByteImage& imgSrc, IppByteImage& imgDst);
void IppRotate270(IppByteImage& imgSrc, IppByteImage& imgDst);


void IppMirror(IppByteImage& imgSrc, IppByteImage& imgDst);
void IppFlip(IppByteImage& imgSrc, IppByteImage& imgDst);
