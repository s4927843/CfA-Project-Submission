#ifndef SNAKE_H
#define SNAKE_H

#include <SDL.h>
#include <ngl/NGLInit.h>
#include <ngl/Mat4.h>
#include <ngl/Vec4.h>

class Snake
{

    private:


        ngl::Mat4 m_view;
        ngl::Mat4 m_projection;
        int m_snakeDirection;
        ngl::Vec4 m_teapotAndOvalRotDir;


    protected:

    public:
        Snake(const ngl::Mat4 &_view, const ngl::Mat4 &_projection);
        ~Snake();
        void moveSnake(int _snakeDirection);
        void drawSnakeHead();
        void drawSnakeSegment(std::string _currentSegment);
        void loadMatrixToShader();


        float m_defaultSnakeSpeed = 0.003f;
        float m_snakeSpeed = m_defaultSnakeSpeed;
        int m_currentSnakeSegment = 0;


        ngl::Vec3 m_snakeRot;
        std::vector <ngl::Vec3> m_snakePos;

        ngl::Vec3 m_currentSnakeSegmentScale;
        std::vector <float> m_currentSnakeSegmentRot;
        ngl::Vec3 m_snakeHeadCurrentPos;
        ngl::Vec3 m_snakeCurrentPos;

        ngl::Vec3 m_snakeSegmentRot;
        ngl::Vec3 m_snakeSegmentPos;

        ngl::Vec4 m_snakeHeadBorder;
        std::vector <ngl::Vec4> m_snakeHeadBorders;
        ngl::Vec4 m_currentSegmentBorder;
};



#endif // SNAKE_H
