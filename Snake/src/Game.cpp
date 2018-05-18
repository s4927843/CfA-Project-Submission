#include "Game.h"
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
#include "math.h"
//--------------------------------------------------------------------------------------------------------------
Game::Game()
{
    //Setting up the shader
    glClearColor(0.1f, 0.5, 0.5f, 1.0f);
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    shader->createShaderProgram("Phong");
    shader->attachShader("PhongVertex",ngl::ShaderType::VERTEX);
    shader->attachShader("PhongFragment",ngl::ShaderType::FRAGMENT);
    shader->loadShaderSource("PhongVertex","shaders/PhongVertex.glsl");
    shader->loadShaderSource("PhongFragment","shaders/PhongFragment.glsl");
    shader->compileShader("PhongVertex");
    shader->compileShader("PhongFragment");
    shader->attachShaderToProgram("Phong","PhongVertex");
    shader->attachShaderToProgram("Phong","PhongFragment");
    shader->bindAttribute("Phong",0,"inVert");
    shader->bindAttribute("Phong",1,"inUV");
    shader->bindAttribute("Phong",2,"inNormal");
    shader->linkProgramObject("Phong");
    (*shader)["Phong"]->use();

    //Setting up the camera
    const ngl::Vec3 from(0,1.1,1);
    const ngl::Vec3 to(0, -1.5,-1);
    const ngl::Vec3 up(0,1,0);
    m_cam = ngl::Camera(from,to,up);
    m_cam.setShape(45,(float)720.0/576.0,0.05,350);
    shader->setUniform("viewerPos",m_cam.getEye().toVec3());

    //Setting up the light
    m_light = ngl::Light(ngl::Vec3(0, 0, 1) ,ngl::Colour(1,1,1,1),ngl::Colour(1,1,1,1),ngl::LightModes::POINTLIGHT);
    m_light.loadToShader("light");

    ngl::ShaderLib::instance()->setUniform("light.pos", m_lightPos);

    m_view = m_cam.getViewMatrix();
    m_projection = m_cam.getVPMatrix();

    //Instantiating classes
    m_config.reset (new Config(m_view, m_projection));
    m_snake.reset(new Snake(m_view, m_projection));
    m_platform.reset(new Platform(m_view, m_projection));
    m_prize.reset(new Prize(m_view, m_projection));
    m_score.reset(new Score(m_view, m_projection));

    //Setting up the scren size for text rendering
    m_score->resize();
}
//--------------------------------------------------------------------------------------------------------------
Game::~Game()
{

}
//--------------------------------------------------------------------------------------------------------------
void Game::setDifficultyLevel()
{
    // Here the game is being configured according to the performance
    // by tweaking values with //CONFIG

    switch (m_difficultyLevel)
    {
    case 0 :
    {
        m_snake->m_snakeSpeed = m_snake->m_defaultSnakeSpeed;
        m_snake->m_snakeSpeed -= 0.0003f; //CONFIG
        m_frameDistance = m_framDefaultDistance;
        m_frameDistance += 0; //CONFIG
        break;
    }
    case 1 :
    {
        m_snake->m_snakeSpeed = m_snake->m_defaultSnakeSpeed;
        m_frameDistance = m_framDefaultDistance;
        m_frameDistance += 0;
        break;
    }
    case 2 :
    {
        m_snake->m_snakeSpeed = m_snake->m_defaultSnakeSpeed;
        m_snake->m_snakeSpeed += 0.0006f; //CONFIG
        m_frameDistance = m_framDefaultDistance;
        m_frameDistance += 0;  //CONFIG
        break;
    }
    case 3 :
    {
        m_snake->m_snakeSpeed = m_snake->m_defaultSnakeSpeed;
        m_snake->m_snakeSpeed += 0.003f; //CONFIG
        m_frameDistance = m_framDefaultDistance;
        m_frameDistance -= 20; //CONFIG
        break;
    }
    } // end of switch (m_difficultyLevel)
}
//--------------------------------------------------------------------------------------------------------------
void Game::resetGame()
{
    //All of these need to be reset in order for game to work
    m_gameOver = false;
    m_showScoreHistory = false;
    m_snake->m_snakeSpeed = m_snake->m_defaultSnakeSpeed;
    setDifficultyLevel();
    m_snake->m_snakeHeadCurrentPos[0] = 0.0f;
    m_snake->m_snakeHeadCurrentPos[2] = 0.0f;
    m_snake->m_snakePos.clear();
    m_snake->m_currentSnakeSegmentRot.clear();
    m_snake->m_snakeHeadBorders.clear();
    m_frameCount = 1;
    m_snakeSegments = 0;
    m_score->m_scoreValue = -10;
    m_prizeActive = false;
    m_addScoreToHistCounter = 1;
}
//--------------------------------------------------------------------------------------------------------------
void Game::resizeGame(int _newGameWidth, int _newGameHeight)
{
    glViewport(0, 0, _newGameWidth, _newGameHeight);
    m_cam.setShape(45,(float)_newGameWidth/_newGameHeight,0.05,350);
}
//--------------------------------------------------------------------------------------------------------------
void Game::drawGame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_platform->drawPlatform();

    m_frameCount = m_snake->m_snakePos.size();

    // Just to push back the first element to the array, otherwise game will crash
    // because of trying to access elements which are not yet there
    if (m_frameCount == 0)
    {
        m_snake->drawSnakeHead();
    }

    borderCheck();
    eatPrizeCheck();



    //snake drawing loop
    for (int i = 0; i < m_snakeSegments; i++)   // 0 is head
    {

        m_snake->m_currentSnakeSegment = i;

        //This value is different for every iteration
        m_segmentDistance = m_snake->m_currentSnakeSegment * m_frameDistance;

        //Current X and Z coordinates of the current segment
        m_snake->m_snakeSegmentPos[0] = m_snake->m_snakePos[m_frameCount - m_segmentDistance][0];
        m_snake->m_snakeSegmentPos[2] = m_snake->m_snakePos[m_frameCount - m_segmentDistance][2];


        m_snake->m_snakeSegmentRot[1] = m_snake->m_currentSnakeSegmentRot[m_frameCount - m_segmentDistance];

        if (m_snake->m_currentSnakeSegment == 0) //head
        {
            m_snake->m_currentSnakeSegmentScale = m_prize->m_teapotScale;
            m_snake->moveSnake(m_snakeDirection);
            m_snake->drawSnakeHead();
        }
        else //segments
        {
            m_snake->m_currentSegmentBorder = m_snake->m_snakeHeadBorders[m_frameCount - m_segmentDistance];
            gameOverCheck();

            //Trolls are rotated differently by deafult
            if (m_prize->m_currentPrize[m_snake->m_currentSnakeSegment - 1] == "troll")
            {
                m_snake->m_snakeSegmentRot[1] += 90;
            }

            //Same for dragons and bunnies
            else if (m_prize->m_currentPrize[m_snake->m_currentSnakeSegment - 1] == "dragon" ||
            m_prize->m_currentPrize[m_snake->m_currentSnakeSegment - 1] == "bunny"
            )
            {
                m_snake->m_snakeSegmentRot[1] += 180;
            }

            m_snake->m_currentSnakeSegmentScale = m_prize->m_currentPrizeScale[m_snake->m_currentSnakeSegment - 1];
            m_snake->m_snakeSegmentPos[1] = m_prize->m_currentPrizeYPos[m_snake->m_currentSnakeSegment - 1];

            m_currentSegment = m_prize->m_currentPrize[m_snake->m_currentSnakeSegment - 1];
            m_snake->drawSnakeSegment(m_currentSegment);
        }



    }

    //put new prize
    if (!m_prizeActive)
    {
        if (m_timesPrizePut == 0)
        {
            m_prize->putPrize();
            m_prizeActive = true;

            //incrementing this to prevent from spawning new priz multiple times
            m_timesPrizePut++;
            m_snakeSegments++;
            m_score->updateScore();
        }
    }
    m_score->drawScore();
    m_prize->drawPrize();
}
//--------------------------------------------------------------------------------------------------------------
void Game::borderCheck()
{

    if (m_snake->m_snakeCurrentPos[0] <= m_platform->m_platformBorder[0])
    {
        m_snake->m_snakeHeadCurrentPos[0] = m_platform->m_platformBorder[1] - 0.0001f;
    }

    if (m_snake->m_snakeCurrentPos[0] >= m_platform->m_platformBorder[1])
    {
        m_snake->m_snakeHeadCurrentPos[0] = m_platform->m_platformBorder[0] + 0.0001f;
    }

    if (m_snake->m_snakeCurrentPos[2] >= m_platform->m_platformBorder[3])
    {
        m_snake->m_snakeHeadCurrentPos[2] = m_platform->m_platformBorder[2] + 0.0001f;
    }

    if (m_snake->m_snakeCurrentPos[2] <= m_platform->m_platformBorder[2])
    {
        m_snake->m_snakeHeadCurrentPos[2] = m_platform->m_platformBorder[3] - 0.0001f;
    }

}
//--------------------------------------------------------------------------------------------------------------
void Game::eatPrizeCheck()
{
    if (m_snake->m_snakeHeadBorder[0] >= m_prize->m_prizeBorder[0] &&
    m_snake->m_snakeHeadBorder[1] <= m_prize->m_prizeBorder[1] &&
    m_snake->m_snakeHeadBorder[2] <= m_prize->m_prizeBorder[2] &&
    m_snake->m_snakeHeadBorder[3] >= m_prize->m_prizeBorder[3]
    )
    {
        if (m_timesPrizePut == 0) // makes sure  it happens only once and not like 200 (when snake head is still in the prize "bbox")
        {
            m_prizeActive = false; // spawn new prize
        }
    }
    else
    {
        m_timesPrizePut = 0; //reset when out of the collision area
    }
}
//--------------------------------------------------------------------------------------------------------------
void Game::gameOverCheck()
{
    m_distanceVector = m_snake->m_snakePos.back() - m_snake->m_snakeSegmentPos;

    if (m_distanceVector.length() < 0.05)
    {
        m_gameOver = true;

        //stop the game
        m_snake->m_snakeSpeed = 0;


        if (m_score->drawGameOver(m_showScoreHistory))  // return true if history needs to be cleaned (8 scores in the config file)
        {
            m_config->clearHistory();
            m_score->m_counter = 1;
            m_score->m_clearHistory = false;
        }
        if (m_addScoreToHistCounter == 1)
        {
            m_config->addScoreToHistory( m_difficultyLevel, m_score->m_scoreValue);
        }
        ++m_addScoreToHistCounter;
    }
}
//--------------------------------------------------------------------------------------------------------------

