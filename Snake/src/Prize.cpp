#include "Prize.h"
#include <iostream>
#include "ngl/NGLInit.h"
#include "ngl/ShaderLib.h"
#include "ngl/VAOPrimitives.h"
#include <ngl/Transformation.h>
#include "ngl/Material.h"
#include "ngl/Random.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <memory>
#include "ngl/Mat3.h"
#include "ngl/Mat4.h"
//--------------------------------------------------------------------------------------------------------------
Prize::Prize(const ngl::Mat4 &_view, const ngl::Mat4 &_projection)
:m_view(_view),
m_projection(_projection)
{
    m_prizeRot.set(0.0f, 0.0f, 0.0f);
    m_prizeRotIncrement.set(0.07f, 0.07f, 0.07f);
    m_prizeRotIncrement.set(0.07f, 0.07f, 0.07f);

    m_teapotScale.set(0.1f, 0.1f, 0.1f);
    m_cubeScale.set(0.1f, 0.1f, 0.1f);
    m_trollScale.set(0.15f, 0.15f, 0.15f);
    m_dragonScale.set(0.008f, 0.008f, 0.008f);
    m_bunnyScale.set(0.01f, 0.01f, 0.01f);
    m_footballScale.set(0.06f, 0.06f, 0.06f);
    m_hedronScale.set(0.06f, 0.06f, 0.06f);
}
//--------------------------------------------------------------------------------------------------------------
Prize::~Prize()
{

}
//--------------------------------------------------------------------------------------------------------------
void Prize::loadMatrixToShader()
{
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    ngl::Transformation m_transPrize;
    ngl::Mat4 MV;
    ngl::Mat4 MVP;
    ngl::Mat3 normalMatrix;
    ngl::Mat4 M;

    ngl::Material m(ngl::STDMAT::GOLD);
    m.loadToShader("material");

    m_prizeRot[0] = 0.0f;
    m_prizeRot[1] += 0.2f;
    m_prizeRot[2] = 0.0f;

    m_transPrize.setScale(m_prizeScale);
    m_transPrize.setPosition(m_prizePos);
    m_transPrize.setRotation(m_prizeRot);

    MV=  m_view * m_transPrize.getMatrix();
    MVP= m_projection * m_transPrize.getMatrix();
    normalMatrix=MV;
    normalMatrix.inverse().transpose();

    shader->setUniform("MV",MV);
    shader->setUniform("MVP",MVP);
    shader->setUniform("normalMatrix",normalMatrix);
    shader->setUniform("M",M); // DOESNT DO ANYTHING M is NOTHING
}
//--------------------------------------------------------------------------------------------------------------
void Prize::drawPrize()
{
    ngl::ShaderLib *shader = ngl::ShaderLib::instance();
    (*shader)["Phong"]->use();
    ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
    loadMatrixToShader();
    prim->draw(m_randomVAO);
}
//--------------------------------------------------------------------------------------------------------------
void Prize::putPrize()
{
    ngl::Random *rand = ngl::Random::instance();
    rand->setSeed(time(0));
    m_randVAO = rand->randomPositiveNumber(9);

    switch (m_randVAO)
    {
    case 0 :
        {
            m_randomVAO = m_teapot;
            m_prizeScale = m_teapotScale;
            m_prizePos[1] = m_teapotYPos;
            break;
        }
    case 1 :
        {
            m_randomVAO = m_cube;
            m_prizeScale = m_cubeScale;
            m_prizePos[1] = m_cubeYPos;
            break;
        }
    case 2 :
        {
            m_randomVAO = m_troll;
            m_prizeScale = m_trollScale;
            m_prizePos[1] = m_trollYPos;
            break;
        }
    case 3 :
        {
            m_randomVAO = m_dragon;
            m_prizeScale = m_dragonScale;
            m_prizePos[1] = m_dragonYPos;
            break;
        }
    case 4 :
        {
            m_randomVAO = m_bunny;
            m_prizeScale = m_bunnyScale;
            m_prizePos[1] = m_bunnyYPos;
            break;
        }
    case 5 :
        {
            m_randomVAO = m_football;
            m_prizeScale = m_footballScale;
            m_prizePos[1] = m_footballYPos;
            break;
        }
    case 6 :
    case 7 :
    case 8 :
        {
            m_prizeScale = m_hedronScale;


            switch (m_randVAO)
            {
            case 6:
                {
                    m_randomVAO = m_icosahedron;
                    m_prizePos[1] = m_icosahedronYPos;
                    break;
                }
            case 7:
                {
                    m_randomVAO = m_dodecahedron;
                    m_prizePos[1] = m_dodecahedronYPos;
                    break;
                }
            case 8:
                {
                    m_randomVAO = m_tetrahedron;
                    m_prizePos[1] = m_tetrahedronYPos;
                    break;
                }
            } // end of switch (m_randVAO)
            break;
        }
    default : // default of switch (m_randVAO)
        {
            m_prizeScale.set(0.1f, 0.1f,0.1f);
            break;
        }
    } // end of switch (m_randVAO)

    m_prizePos[0] = rand->randomNumber( 0.8);
    m_prizePos[2] = rand->randomNumber(0.8);

    m_prizeBorder[0] = m_prizePos[0] - 0.09f; //left border
    m_prizeBorder[1] = m_prizePos[0] + 0.09f; //right border
    m_prizeBorder[2] = m_prizePos[2] + 0.09f; // down border
    m_prizeBorder[3] = m_prizePos[2] - 0.09f; //up border

    m_currentPrize.push_back(m_randomVAO);
    m_currentPrizeScale.push_back(m_prizeScale);
    m_currentPrizeYPos.push_back(m_prizePos[1]);
}
//--------------------------------------------------------------------------------------------------------------
