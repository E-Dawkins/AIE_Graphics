#pragma once
#include "GraphicsApp.h"

class Scene
{
public:
    Scene() { m_graphicsApp = GraphicsApp::instance; }
    
    virtual void Start() {}

    virtual void Update(float _dt) {}
    virtual void Draw() {}

    virtual void Destroy() {}

    virtual void ImGuiRefresher() {}

protected:
    GraphicsApp* m_graphicsApp;
};
