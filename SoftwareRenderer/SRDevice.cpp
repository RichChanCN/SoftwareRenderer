#include "SRDevice.h"

SRDevice::SRDevice(int width, int height){
    m_width = width;
    m_height = height;

    m_zBuffer = new float*[m_width];
    for (int i = 0; i < m_width; i++)
    {
        m_zBuffer[i] = new float[m_height];
    }
}

SRDevice::~SRDevice(){
    if (m_pFramebuffer)
        delete m_pFramebuffer;
    if (m_zBuffer)
    {
        for (int i = 0; i < m_width; i++)
        {
            delete[] m_zBuffer[i];
        }
        delete[] m_zBuffer;
    }
}

void SRDevice::drawPixel(int x, int y, SRVector3 color){
    m_pFramebuffer[m_width*y + x] = MathUtils::colorToUINT(color);
}

float SRDevice::getZ(int x, int y){
    if (x >= 0 && x < m_width && y >= 0 && y < m_height)
        return m_zBuffer[x][y];
    else
        return 1.f;
}

void SRDevice::setZ(int x, int y, float z)
{
    if (x >= 0 && x < m_width && y >= 0 && y < m_height)
    {
        m_zBuffer[x][y] = z;
    }
}

void SRDevice::clearBuffer(SRVector3 color)
{
    for (int x = 0; x < m_width; ++x)
    {
        for (int y = 0; y < m_height; ++y)
        {
            m_pFramebuffer[m_width*y + x] = MathUtils::colorToUINT(color);
            m_zBuffer[x][y] = 0;
        }
    }
}
