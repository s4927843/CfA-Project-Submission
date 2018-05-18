#include "Config.h"
#include <iostream>
#include "SDL.h"
#include "ngl/ShaderLib.h"
#include <ngl/Transformation.h>
#include <ngl/NGLInit.h>
#include <iostream>
#include <fstream>
//--------------------------------------------------------------------------------------------------------------
Config::Config(const ngl::Mat4 &_view, const ngl::Mat4 &_projection)
: m_view(_view),
m_projection(_projection)
{

}
//--------------------------------------------------------------------------------------------------------------
Config::~Config()
{

}
//--------------------------------------------------------------------------------------------------------------
void Config::addScoreToHistory(int _difficultyLevel, int _score)
{
    auto m_difficultyLevel = _difficultyLevel;
    auto m_score = _score;
    std::string m_difficultyLvl = "EASY";

    switch  (m_difficultyLevel)
    {
        case 0 :
            m_difficultyLvl = "EASY";
            break;
        case 1 :
            m_difficultyLvl = "MEDIUM";
            break;
        case 2 :
            m_difficultyLvl = "HARD";
            break;
        case 3 :
            m_difficultyLvl = "SNAKE_KING";
    }

    m_outConfigFile.open("config/score_history.txt", std::ios::out | std::ios::app);
    m_outConfigFile << "Difficulty_Level:_" << m_difficultyLvl << "___________Score:_" << m_score  << std::endl;
    m_outConfigFile.close();
}
//--------------------------------------------------------------------------------------------------------------
void Config::clearHistory()
{
    m_outConfigFile.open("config/score_history.txt");

}
//--------------------------------------------------------------------------------------------------------------





