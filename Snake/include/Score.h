#ifndef SCORE_H
#define SCORE_H

#include <SDL.h>
#include "Text.h"
#include "ngl/Mat4.h"
#include <sstream>
#include <fstream>
#include <iostream>
//-------------------------------------------------------------------------------------------------------
class Score
{
    public:
        //-------------------------------------------------------------------------------------------------------
        ///@brief counting score records in config file
        int m_counter = 1;
        bool m_clearHistory = false;
        int m_scoreValue = -10;

        std::stringstream m_stringStream;
        std::string m_scoreString;
        std::string m_scoreHistoryString;
        //-----------------------------------------------------------------------------------------------
        /// @brief ctor this will have a valid OpenGL context so we can create gl stuff
        /// @param[in] _&view const reference m_cam.getViewMatrix()from Game class
        /// ~param[in] _&projection const reference  m_cam.getVPMatrix() from Game class
        Score(const ngl::Mat4 &_view, const ngl::Mat4 &_projection);
        //-----------------------------------------------------------------------------------------------
        ~Score();
        void updateScore();
        void drawScore();
        bool drawGameOver(bool _showScoreHistory);
        void resize();
//-------------------------------------------------------------------------------------------------------
    private:
        //-------------------------------------------------------------------------------------------------------
        ///@brief rendering messages
        Text *m_currentScore;
        Text *m_gameOverMsg;
        Text *m_finalScore;
        Text *m_scoreHistory;

        ngl::Mat4 m_view;
        ngl::Mat4 m_projection;
        //-------------------------------------------------------------------------------------------------------
        ///@brief rect for setting up screen size for text rendering
        SDL_Rect m_rect;
        //-------------------------------------------------------------------------------------------------------
        ///@brief prize arrays for snake to be able to use these values in  a VAO Primitive queue
        std::ifstream m_inConfigFile;
//-------------------------------------------------------------------------------------------------------
};
















#endif // SCORE_H
