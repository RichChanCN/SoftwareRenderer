#include "My3DApp.h"
My3DApp::My3DApp(SRDevice* pDevice) :m_gl(pDevice)
{
    m_pDevice = pDevice;

    init();
}

My3DApp::~My3DApp()
{
}

void My3DApp::init(){
    m_vertexs.push_back(SRVector3(200, 200, 0));
    m_vertexs.push_back(SRVector3(600, 200, 0));
    m_vertexs.push_back(SRVector3(200, 400, 0));
    m_vertexs.push_back(SRVector3(600, 400, 0));

    m_gl.setVAO(m_vertexs);
}

void My3DApp::render(int delta){

    m_gl.clear();
    m_gl.drawTriangle(m_vertexs[0], m_vertexs[1], m_vertexs[2]);
}