#ifndef PRIZE_H
#define PRIZE_H

#include <SDL.h>
#include <ngl/NGLInit.h>
#include <ngl/Mat4.h>
#include <ngl/Vec4.h>
#include <ngl/Vec3.h>

//-------------------------------------------------------------------------------------------------------
class Prize
{
    public:

        ngl::Vec4 m_prizeBorder;

        ngl::Vec3 m_teapotScale;
        float m_teapotYPos = 0.1f;
        ngl::Vec3 m_cubeScale;
        float m_cubeYPos = 0.11f;

        //-------------------------------------------------------------------------------------------------------
        ///@brief prize arrays for snake to be able to use these values in  a VAO Primitive queue
        std::vector <std::string> m_currentPrize;
        std::vector <ngl::Vec3> m_currentPrizeScale;
        std::vector <float> m_currentPrizeYPos;

        //-----------------------------------------------------------------------------------------------
        /// @brief ctor this will have a valid OpenGL context so we can create gl stuff
        /// @param[in] _&view const reference m_cam.getViewMatrix()from Game class
        /// ~param[in] _&projection const reference  m_cam.getVPMatrix() from Game class
        Prize(const ngl::Mat4 &_view, const ngl::Mat4 &_projection);
        //-----------------------------------------------------------------------------------------------
        ~Prize();
        void loadMatrixToShader();
        void drawPrize();
        void putPrize();
//-------------------------------------------------------------------------------------------------------
    private:
        ngl::Mat4 m_view;
        ngl::Mat4 m_projection;

        ngl::Vec3 m_prizeScale;
        ngl::Vec3 m_prizePos;
        ngl::Vec3 m_prizeRot;
        ngl::Vec3 m_prizeRotIncrement;


        //-------------------------------------------------------------------------------------------------------
        ///@brief prize transformations
        int m_randVAO = 0;
        std::string m_randomVAO;
        std::string m_teapot = "teapot";
        std::string m_cube = "cube";
        std::string m_troll = "troll";
        std::string m_dragon = "dragon";
        std::string m_bunny = "bunny";
        std::string m_football = "football";
        std::string m_icosahedron = "icosahedron";
        std::string m_dodecahedron = "dodecahedron";
        std::string m_tetrahedron = "tetrahedron";


        ngl::Vec3 m_trollScale;
        float m_trollYPos = 0.15f;

        ngl::Vec3 m_dragonScale;
        float m_dragonYPos = 0.07f;


        ngl::Vec3 m_bunnyScale;
        float m_bunnyYPos = 0.065f;


        ngl::Vec3 m_footballScale;
        float m_footballYPos = 0.115f;


        ngl::Vec3 m_hedronScale;
        float m_icosahedronYPos = 0.115f;
        float m_dodecahedronYPos = 0.12f;
        float m_tetrahedronYPos = 0.13f;
//-------------------------------------------------------------------------------------------------------
};

#endif // PRIZE_H
