#include"MathUtils.h"
//颜色ZCFloat3(r,b,g,a)转化为UINT
UINT MathUtils::colorToUINT(const SRVector3& color)
{
    BYTE red = 255 * color.x/*  color.w*/;
    BYTE green = 255 * color.y/* color.w*/;
    BYTE blue = 255 * color.z /* color.w*/;
    return (UINT)((BYTE)blue | (WORD)((BYTE)green << 8) | (DWORD)((BYTE)red << 16));
}
