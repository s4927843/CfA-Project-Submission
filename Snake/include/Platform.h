#ifndef PLATFORM_H
#define PLATFORM_H
#include <SDL.h>
#include <ngl/NGLInit.h>
#include <ngl/Mat4.h>
#include <ngl/Vec4.h>
#include <ngl/Vec3.h>
//-------------------------------------------------------------------------------------------------------
class Platform
{

    public:
        ngl::Vec4 m_platformBorder;

        //-----------------------------------------------------------------------------------------------
        /// @brief ctor this will have a valid OpenGL context so we can create gl stuff
        /// @param[in] _&view const reference m_cam.getViewMatrix()from Game class
        /// ~param[in] _&projection const reference  m_cam.getVPMatrix() from Game class
        Platform(const ngl::Mat4 &_view, const ngl::Mat4 &_projection);
        //-----------------------------------------------------------------------------------------------
        ~Platform();
        void loadMatricesToShader();
        void drawPlatform();

        //-----------------------------------------------------------------------------------------------
    private:
        ngl::Mat4 m_view;
        ngl::Mat4 m_projection;
        //-----------------------------------------------------------------------------------------------
};




#endif // PLATFORM_H
