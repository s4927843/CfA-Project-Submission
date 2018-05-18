#include "Platform.h"
#include <iostream>
#include "ngl/NGLInit.h"
#include "ngl/ShaderLib.h"
#include "ngl/VAOPrimitives.h"
#include <ngl/Transformation.h>
#include "ngl/Material.h"
#include "string"
#include "ngl/Mat4.h"
#include "ngl/Mat3.h"
#include <vector>
#include <memory>
#include "math.h"
//--------------------------------------------------------------------------------------------------------------
const ngl::Vec3 c_platformPos{0, 0, 0};
const ngl::Vec3 c_platformRot{0, 0, 0};
const ngl::Vec3 c_platformScale{1.8f, 0.1f, 1.8 };
//--------------------------------------------------------------------------------------------------------------
Platform::Platform(const ngl::Mat4 &_view, const ngl::Mat4 &_projection)
    :m_view(_view),
     m_projection(_projection)
{
    m_platformBorder[0] = -0.84f; //left
    m_platformBorder[1] = 0.84f; //right,
    m_platformBorder[2] = -0.83f; //upper,
    m_platformBorder[3] = 0.85f; //down
}
//--------------------------------------------------------------------------------------------------------------
Platform::~Platform()
{

}
//--------------------------------------------------------------------------------------------------------------
void Platform::loadMatricesToShader()
{
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    ngl::Transformation m_transPlatform;
    ngl::Mat4 MV;
    ngl::Mat4 MVP;
    ngl::Mat4 normalMatrix;
    ngl::Material m(ngl::STDMAT::PEWTER);
    m.loadToShader("material");

    m_transPlatform.setScale(c_platformScale);
    m_transPlatform.setPosition(c_platformPos);
    m_transPlatform.setRotation(c_platformRot);

    MV=  m_view * m_transPlatform.getMatrix();
    MVP= m_projection * m_transPlatform.getMatrix();
    normalMatrix=MV;
    normalMatrix.inverse().transpose();

    shader->setUniform("MV",MV);
    shader->setUniform("MVP",MVP);
    shader->setUniform("normalMatrix",normalMatrix);
}
//--------------------------------------------------------------------------------------------------------------
void Platform::drawPlatform()
{
    ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
    loadMatricesToShader();
    prim->draw("cube");
}
//--------------------------------------------------------------------------------------------------------------


