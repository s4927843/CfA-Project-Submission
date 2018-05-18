#include "Score.h"
#include <iostream>
#include "SDL.h"
#include "ngl/ShaderLib.h"
#include <ngl/Transformation.h>
#include <ngl/NGLInit.h>
#include <iostream>
//--------------------------------------------------------------------------------------------------------------
Score::Score(const ngl::Mat4 &_view, const ngl::Mat4 &_projection)
:m_view(_view),
m_projection(_projection)
{
    m_currentScore = new Text("font/Xcelsion.ttf", 100);
    m_gameOverMsg = new Text("font/Xcelsion.ttf",200);
    m_finalScore = new Text("font/Xcelsion.ttf", 100);
    m_scoreHistory = new Text("font/Xcelsion.ttf", 60);
}
//--------------------------------------------------------------------------------------------------------------
Score::~Score()
{

}
//--------------------------------------------------------------------------------------------------------------
void Score::resize()
{
    SDL_GetDisplayBounds(0, &m_rect);
    m_currentScore->setScreenSize(m_rect.w, m_rect.h);
}
//--------------------------------------------------------------------------------------------------------------
void Score::updateScore()
{
    m_scoreValue +=10;
    m_stringStream.str("");
    m_stringStream << m_scoreValue;
    m_scoreString = m_stringStream.str();
}
//--------------------------------------------------------------------------------------------------------------
void Score::drawScore()
{
    m_currentScore->setColour(1, 1, 0.3);
    m_currentScore->renderText(10,40,"SCORE " + m_scoreString);
}
//--------------------------------------------------------------------------------------------------------------
bool Score::drawGameOver(bool _showScoreHistory)
{
    auto m_showScoreHistory = _showScoreHistory;

    if (!m_showScoreHistory)
    {
        m_gameOverMsg->setColour(1, 0, 0);
        m_gameOverMsg->renderText(m_rect.x + 600, m_rect.h/2 - 300, "GAME OVER!!!");
        m_finalScore->setColour(1, 1, 0.3);
        m_finalScore->renderText(m_rect.w/2 - 560, m_rect.h/2 - 50, "YOUR SCORE: " + m_scoreString);
        m_finalScore->renderText(m_rect.x + 520, m_rect.h/2 + 300, "Press ESCAPE to CONTINUE");
    }
    else // draw score history
    {
        std::ifstream inConfigFile("config/score_history.txt");
        m_scoreHistory->setColour(1,1,1);

        m_counter = 1;
        while (inConfigFile >> m_scoreHistoryString)
        {

            if (m_counter < 9)
            {
                m_scoreHistory->renderText(m_rect.x + 300, (m_rect.y + 120) * m_counter , m_scoreHistoryString);
                ++m_counter;
            }
            else
            {
                m_clearHistory = true;
            }
        }
    }
    return m_clearHistory;
}
//--------------------------------------------------------------------------------------------------------------

