#include "Snake.h"
#include <iostream>
#include <ngl/ShaderLib.h>
#include <ngl/Transformation.h>
#include <ngl/Material.h>
#include "string"
#include "ngl/Mat4.h"
#include "ngl/Mat3.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <memory>
//--------------------------------------------------------------------------------------------------------------
Snake::Snake(const ngl::Mat4 &_view, const ngl::Mat4 &_projection)
: m_view(_view),
 m_projection(_projection)
{
    m_snakeRot[0] = 0.0f;
    m_snakeRot[2] = 0.0f;
    m_snakeHeadCurrentPos[0] = 0.0f;
    m_snakeHeadCurrentPos[1] = 0.1f;
    m_snakeHeadCurrentPos[2] = 0.0f;
    m_snakeCurrentPos[0] = 0.0f;
    m_snakeCurrentPos[1] = 0.1f;
    m_snakeCurrentPos[2] = 0.0f;
    m_teapotAndOvalRotDir[0] = 0;
    m_teapotAndOvalRotDir[1] = 180;
    m_teapotAndOvalRotDir[2] = 90;
    m_teapotAndOvalRotDir[3] = 270;

    m_snakeSegmentPos[1] = 0.1f;

    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    shader->use("Phong");
}
//--------------------------------------------------------------------------------------------------------------
Snake::~Snake()
{

}
//--------------------------------------------------------------------------------------------------------------
void Snake::moveSnake(int _snakeDirection)
{
    auto m_snakeDirection = _snakeDirection;

        if (m_currentSnakeSegment == 0) //head
        {
            switch (m_snakeDirection)
            {
                case 0 : //right
                    {
                        m_snakeHeadCurrentPos[0] += m_snakeSpeed;
                        m_snakeRot[1] = m_teapotAndOvalRotDir[0];
                        break;
                    }
                case 1 : //left
                    {
                        m_snakeHeadCurrentPos[0] -= m_snakeSpeed;
                        m_snakeRot[1] = m_teapotAndOvalRotDir[1];
                        break;
                    }
                case 2 : //up
                    {
                        m_snakeHeadCurrentPos[2] -= m_snakeSpeed;
                        m_snakeRot[1] = m_teapotAndOvalRotDir[2];
                        break;
                    }
                case 3 : //down
                    {
                    m_snakeHeadCurrentPos[2] += m_snakeSpeed;
                    m_snakeRot[1] = m_teapotAndOvalRotDir[3];
                    break;
                    }
                default :
                    break;
            }
        }

        m_snakeHeadBorder[0] = m_snakeCurrentPos[0] - 0.02f; //left border
        m_snakeHeadBorder[1] = m_snakeCurrentPos[0] + 0.02f; //right border
        m_snakeHeadBorder[2] = m_snakeCurrentPos[2] + 0.02f; // down border
        m_snakeHeadBorder[3] = m_snakeCurrentPos[2] - 0.02f; //up border
}
//--------------------------------------------------------------------------------------------------------------
void Snake::drawSnakeHead()
{
    ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();

    m_snakePos.push_back(m_snakeHeadCurrentPos);
    m_currentSnakeSegmentRot.push_back(m_snakeRot[1]);
    m_snakeHeadBorders.push_back(m_snakeHeadBorder);

    loadMatrixToShader();
    prim->draw("teapot");
}
//--------------------------------------------------------------------------------------------------------------
void Snake::drawSnakeSegment(std::string _currentSegment)
{
    auto m_currentSegment = _currentSegment;
    ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();

    loadMatrixToShader();
    prim->draw(m_currentSegment);
}
//--------------------------------------------------------------------------------------------------------------
void Snake::loadMatrixToShader()
{
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    ngl::Material m(ngl::STDMAT::CHROME);
    m.loadToShader("material");

    ngl::Mat4 MV;
    ngl::Mat4 MVP;
    ngl::Mat3 normalMatrix;
    ngl::Mat4 M;
    ngl::Transformation m_transSnake;

    m_transSnake.setScale(m_currentSnakeSegmentScale);


    if (m_currentSnakeSegment == 0) //head
        {
            m_transSnake.setRotation(m_snakeRot);
            m_snakeCurrentPos[0] = m_snakePos.back()[0];
            m_snakeCurrentPos[2] = m_snakePos.back()[2];
            m_transSnake.setPosition(m_snakeCurrentPos);
        }
        else // body segment
        {
            m_transSnake.setRotation(m_snakeSegmentRot);
            m_transSnake.setPosition(m_snakeSegmentPos);
        }

    MV=  m_view * m_transSnake.getMatrix();
    MVP= m_projection * m_transSnake.getMatrix();
    normalMatrix=MV;
    normalMatrix.inverse().transpose();

    shader->setUniform("MV",MV);
    shader->setUniform("MVP",MVP);
    shader->setUniform("normalMatrix",normalMatrix);
}
//--------------------------------------------------------------------------------------------------------------


