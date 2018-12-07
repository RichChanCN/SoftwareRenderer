#include "MyGL.h"

MyGL::MyGL(SRDevice* pDevice)
{
    m_pDevice = pDevice;
}

MyGL::~MyGL()
{
}

void MyGL::setVAO(std::vector<SRVector3>& vertexs){
    m_vertexs = vertexs;
}

void MyGL::clear(SRVector3 color){
    m_pDevice->clearBuffer(color);
}

void MyGL::draw(int delta){

    for (int i = 0; i < m_vertexs.size(); i++)
    {
        m_pDevice->drawPixel(m_vertexs[i].x, m_vertexs[i].y, SRVector3(0.0f, 0.0f, 0.0f));
    }
}

void MyGL::drawTriangle(const SRVector3& v1, const SRVector3& v2, const SRVector3& v3){
    drawLine(v1, v2);
    drawLine(v2, v3);
    drawLine(v3, v1);
}

void MyGL::drawLine(const SRVector3& v1, const SRVector3& v2){
    int dx = v2.x - v1.x;
    int dy = v2.y - v1.y;

    int step_x = 1;
    int step_y = 1;

    if (dx < 0){
        step_x = -1;
        dx = abs(dx);
    }

    if (dy < 0){
        step_y = -1;
        dy = abs(dy);
    }

    int x = v1.x;
    int y = v1.y;

    int dy_2 = 2 * dy;
    int dx_2 = 2 * dx;

    if (dx > dy){
        int e = -dx;
        for (int i = 0; i < dx; i++)
        {
            if (x >= 0 && x < m_pDevice->getWindowWidth() && y >= 0 && y < m_pDevice->getWindowHeight())
                m_pDevice->drawPixel(x, y, SRVector3(0, 0, 0));
            x += step_x;
            e = e + dy_2;
            if (e >= 0){
                e -= dx_2;
                y += step_y;
            }
        }
    }
    else{
        int e = -dy;
        for (int i = 0; i < dy; i++)
        {
            if (x >= 0 && x < m_pDevice->getWindowWidth() && y >= 0 && y < m_pDevice->getWindowHeight())
                m_pDevice->drawPixel(x, y, SRVector3(0, 0, 0));
            y += step_y;
            e = e + dx_2;
            if (e >= 0){
                e -= dy_2;
                x += step_x;
            }
        }
    }
}