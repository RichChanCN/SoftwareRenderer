#ifndef __MYGL_H__
#define __MYGL_H__

#include "SRDevice.h"
#include <vector>

class MyGL
{
public:
    MyGL(SRDevice* pDevice);
    ~MyGL();

public:
    void draw(int delta);
    void clear(SRVector3 color = SRVector3(1.0f,1.0f,1.0f));

    void drawTriangle(const SRVector3& v1, const SRVector3& v2, const SRVector3& v3);
    void drawLine(const SRVector3& v1, const SRVector3& v2);
    void setVAO(std::vector<SRVector3>& vertexs);

private:
    SRDevice* m_pDevice;
    
    std::vector<SRVector3> m_vertexs;
};

#endif