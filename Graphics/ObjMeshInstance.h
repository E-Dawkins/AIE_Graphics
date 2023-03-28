#pragma once
#include "Instance.h"

namespace aie
{
    class OBJMesh;
}

class ObjMeshInstance : public Instance
{
public:
    ObjMeshInstance(glm::mat4 _transform, aie::OBJMesh& _mesh,
                aie::ShaderProgram& _shader);
    ObjMeshInstance(glm::vec3 _position, glm::vec3 _eulerAngles, glm::vec3 _scale,
                aie::OBJMesh& _mesh, aie::ShaderProgram& _shader);
    
    void Draw(Scene* _scene) override;
    
protected:
    aie::OBJMesh* m_objMesh;
};