#include<vector>
#include "SRDevice.h"
#include "MyGL.h"

class My3DApp
{
public:
    My3DApp(SRDevice* pDevive);
    ~My3DApp();
public:
    void init();
    //ºÁÃë¼¶±ð
    void render(int delta);

private:
    SRDevice* m_pDevice;
    MyGL m_gl;

    std::vector<SRVector3> m_vertexs;
};
