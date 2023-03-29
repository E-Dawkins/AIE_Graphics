#pragma once
#include "Instance.h"

#include "OBJMesh.h"

class ObjMeshInstance : public Instance
{
public:
    ObjMeshInstance(glm::mat4 _transform, aie::OBJMesh& _mesh,
                aie::ShaderProgram& _shader);
    ObjMeshInstance(glm::vec3 _position, glm::vec3 _eulerAngles, glm::vec3 _scale,
                aie::OBJMesh& _mesh, aie::ShaderProgram& _shader);

    ~ObjMeshInstance() override
    {
        delete m_objMesh;
    }
    
    void Draw(Scene* _scene) override;
    
protected:
    aie::OBJMesh* m_objMesh;
};