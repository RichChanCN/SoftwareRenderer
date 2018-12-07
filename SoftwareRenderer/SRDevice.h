#ifndef __SRDEVICE_H__
#define __SRDEVICE_H__

#include "SRVector.h"
#include "MathUtils.h"


class SRDevice
{
public:
    SRDevice(int width, int height);
    ~SRDevice();
public:
    int getWindowWidth(){ return m_width; }
    int getWindowHeight(){ return m_height; }
    UINT*& getFrameBuffer(){ return m_pFramebuffer; }
    float getZ(int x, int y);
    void setZ(int x, int y, float z);
    void drawPixel(int x, int y, SRVector3 color);
    void clearBuffer(SRVector3 color);

private:
    int m_width;
    int m_height;
    UINT* m_pFramebuffer;
    float **m_zBuffer;
};

#endif