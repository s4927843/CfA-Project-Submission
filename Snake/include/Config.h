#ifndef CONFIG_H
#define CONFIG_H

#include <SDL.h>
#include "ngl/Mat4.h"
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
//-------------------------------------------------------------------------------------------------------
class Config
{

    public:

        //-----------------------------------------------------------------------------------------------
        /// @brief ctor this will have a valid OpenGL context so we can create gl stuff
        /// @param[in] _&view const reference m_cam.getViewMatrix()from Game class
        /// ~param[in] _&projection const reference  m_cam.getVPMatrix() from Game class
        Config(const ngl::Mat4 &_view, const ngl::Mat4 &_projection);
        //-----------------------------------------------------------------------------------------------
        ~Config();
        void addScoreToHistory(int _difficultyLevel, int _score);
        void clearHistory();
//-------------------------------------------------------------------------------------------------------
    private:
        std::string m_scoreHistory;
        std::ofstream m_outConfigFile;

        ngl::Mat4 m_view;
        ngl::Mat4 m_projection;


};
//-------------------------------------------------------------------------------------------------------
#endif // CONFIG_H
