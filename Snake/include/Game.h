#ifndef GAME_H
#define GAME_H

#include "Menu.h"
#include <SDL.h>
#include "Platform.h"
#include "Snake.h"
#include "Prize.h"
#include "Score.h"
#include "Text.h"
#include "Config.h"
#include <ngl/NGLInit.h>
#include <ngl/Camera.h>
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <memory>
#include <ngl/Light.h>
#include <iostream>
#include <vector>
//-------------------------------------------------------------------------------------------------------


class Game
{
    public:

        enum m_snakeDirections
        {
            m_right,
            m_left,
            m_up,
            m_down
        };
        int m_snakeDirection = m_right;
        float m_framDefaultDistance = 40;
        float m_frameDistance = m_framDefaultDistance;

        int m_difficultyLevel = 0; //easy by default
        bool m_cubeSnake = false;
        bool m_pauseGame = false;
        bool m_gameOver = false;
        bool m_showScoreHistory = false;


        Game();
        ~Game();
        void resizeGame(int _newWidth, int _newHeight);
        void setDifficultyLevel();
        void resetGame();
        void drawGame();
        void borderCheck();
        void eatPrizeCheck();
        void gameOverCheck();


//-------------------------------------------------------------------------------------------------------
    private:

        std::unique_ptr<Platform> m_platform;
        std::unique_ptr<Snake> m_snake;
        std::unique_ptr <Prize> m_prize;
        std::unique_ptr <Score> m_score;
        std::unique_ptr <Config> m_config;




        ngl::Camera m_cam;
        ngl::Light m_light;
        ngl::Mat4 m_view;
        ngl::Mat4 m_projection;
        ngl::Vec3 m_lightPos{0.0f, 1.0f, 0.0f}; // ROTdont need that
        ngl::Vec3 m_distanceVector;

        std::string m_currentSegment;
        int m_frameCount = 0;
        int m_snakeSegments = 0;
        int m_segmentDistance = 0;


        bool m_prizeActive = false;
        int m_timesPrizePut =0;
        int m_addScoreToHistCounter = 1;
};
//-------------------------------------------------------------------------------------------------------

#endif //GAME_H
