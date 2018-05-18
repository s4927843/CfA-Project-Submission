#include <SDL.h>
#include <ngl/NGLInit.h>
#include <iostream>
#include "Menu.h"
#include "Game.h"
#include "cstdlib"
//--------------------------------------------------------------------------------------------------------------
/// @brief function to quit SDL with error message
/// @param[in] _errorMessage the error message to send
void SDLError(const std::string &_errorMessage);

/// @brief initialize SDL OpenGL context
/// @param[in] _window the window we want the context for
SDL_GLContext getOpenGLContext(SDL_Window *_window);
//--------------------------------------------------------------------------------------------------------------
/// @brief bools to switch between menu and game polls. By default it's menu
bool static windowOpened = true;
bool static gameRunning = false;
//--------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    NGL_UNUSED(argc);
    NGL_UNUSED(argv);

    //Initializg SDL
    if ( SDL_Init(SDL_INIT_EVERYTHING) <0 )
    {
        SDLError("Unable to initialize SDL: ");
    }

    //Creating window with fixed resolution to best fit the menu textures resolution
    SDL_Window *window =  SDL_CreateWindow( "Snake",
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            1400, 1000,
                                            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
                                            );

    //Error checks
    if (!window)
    {
        SDLError("Unable to create window");
    }

    //Creating OpenGL context
    SDL_GLContext glContext = getOpenGLContext(window);

    if (!getOpenGLContext)
    {
        SDLError("Unable to create OpenGL context");
    }

    SDL_GL_MakeCurrent(window, glContext);
    SDL_GL_SetSwapInterval(1);


    ngl::NGLInit::instance();

    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);


    //Two separate events for menu and game controls separately
    //To avoid lots of if's and to make code more clear
    SDL_Event menuEvent;
    SDL_Event gameEvent;


    // Menu constructor loads in all BMP textures for MENU
    // Game constructor sets up the shader, camera, light, intiial values for game
    // Might take a while to load everything
    Menu menu(window);
    Game game;

    //Menu loop happens when gameRunning = false;
    while (windowOpened)
    {
        while ( SDL_PollEvent(&menuEvent))
        {
            switch (menuEvent.type)
            {
            case SDL_QUIT :
                {
                    windowOpened = false;
                    break;
                }
            case SDL_WINDOWEVENT :
                {
                    int m_newMenuWidth, m_newMenuHeight;
                    SDL_GetWindowSize(window, &m_newMenuWidth, &m_newMenuHeight);
                    menu.resizeMenu(m_newMenuWidth, m_newMenuHeight, window);
                    break;
                }
            case SDL_KEYDOWN :
                switch ( menuEvent.key.keysym.sym )
                {
                case SDLK_ESCAPE :
                    {
                        if (menu.m_currentMenu == menu.m_mainMenu ||
                        menu.m_currentMenu == menu.m_gameOverMenu
                        )
                        {
                            windowOpened = false;
                        }

                        if (menu.m_currentMenu == menu.m_difficultyLevelMenu ||
                        menu.m_currentMenu == menu.m_settingsMenu
                        )
                        {
                            menu.m_currentMenu = menu.m_mainMenu;
                        }

                        else if (game.m_gameOver)
                        {
                            gameRunning = false;
                            menu.m_currentMenu = menu.m_gameOverMenu;
                        }

                        if (menu.m_currentMenu == menu.m_pauseMenu)
                        {
                            gameRunning = true;

                        }
                        break;
                    } //end of case SDLK_ESCAPE

                case SDLK_UP :
                    {
                        if (menu.m_currentMenu == menu.m_mainMenu
                        || menu.m_currentMenu == menu.m_gameOverMenu
                        )
                        {
                            if (menu.m_mainMenuMode == menu.m_startGame ||
                            menu.m_gameOverMode == menu.m_playAgain
                            )
                            {
                                menu.m_mainMenuMode = menu.m_exit;
                                menu.m_gameOverMode = menu.m_Exit;
                            }
                            else
                            {
                                --menu.m_mainMenuMode;
                                --menu.m_gameOverMode;
                            }
                        }
                        else if (menu.m_currentMenu == menu.m_difficultyLevelMenu)
                        {
                            if (menu.m_difficultyLevelMenuMode == menu.m_easy)
                            {
                                menu.m_difficultyLevelMenuMode = menu.m_snakeKing;
                            }
                            else
                            {
                                --menu.m_difficultyLevelMenuMode;
                            }

                        }
                        else if (menu.m_currentMenu == menu.m_pauseMenu)
                        {
                            if (menu.m_pauseMenuMode == menu.m_continue)
                            {
                                menu.m_pauseMenuMode = menu.m_quitGame;
                            }
                            else
                            {
                                --menu.m_pauseMenuMode;
                            }
                        }
                        break;
                    } // end of case SDLK_UP

                case SDLK_DOWN :
                    {
                        if (menu.m_currentMenu == menu.m_mainMenu ||
                        menu.m_currentMenu == menu.m_gameOverMenu
                        )
                        {
                            if (menu.m_mainMenuMode == menu.m_exit ||
                            menu.m_gameOverMode == menu.m_Exit
                            )
                            {
                                menu.m_mainMenuMode = menu.m_startGame;
                                menu.m_gameOverMode = menu.m_playAgain;
                            }
                            else
                            {
                                ++menu.m_mainMenuMode;
                                ++menu.m_gameOverMode;
                            }
                        }
                        else if (menu.m_currentMenu == menu.m_difficultyLevelMenu)
                        {
                            if (menu.m_difficultyLevelMenuMode == menu.m_snakeKing)
                            {
                                menu.m_difficultyLevelMenuMode = menu.m_easy;
                            }
                            else
                            {
                                ++menu.m_difficultyLevelMenuMode;
                            }
                        }
                        else if (menu.m_currentMenu == menu.m_pauseMenu)
                        {
                            if (menu.m_pauseMenuMode == menu.m_quitGame)
                            {
                                menu.m_pauseMenuMode = menu.m_continue;
                            }
                            else
                            {
                                ++menu.m_pauseMenuMode;
                            }
                        }
                        break;
                    } // end of case SDLK_DOWN

                case SDLK_SPACE :
                case SDLK_RETURN :
                    {
                        if (menu.m_currentMenu == menu.m_mainMenu)
                        {
                            switch (menu.m_mainMenuMode)
                            {
                                case menu.m_startGame :
                                    {
                                        gameRunning = true;
                                        game.resetGame();
                                        break;
                                    }
                                case menu.m_difficultyLevel :
                                    {
                                        menu.m_currentMenu = menu.m_difficultyLevelMenu;
                                        continue;
                                    }
                                case menu.m_settings :
                                    {
                                        menu.m_currentMenu = menu.m_settingsMenu;
                                        break;
                                    }
                                case menu.m_exit :
                                    {
                                        windowOpened = false;
                                        break;
                                    }
                            } // end of switch (menu.m_mainMenuMode)
                        }
                        if (menu.m_currentMenu == menu.m_gameOverMenu)
                        {
                            switch (menu.m_gameOverMode)
                            {
                                case menu.m_playAgain :
                                    {
                                        gameRunning = true;
                                        game.resetGame();
                                        break;
                                    }
                                case menu.m_DifficulyLevel :
                                    {
                                        menu.m_currentMenu = menu.m_difficultyLevelMenu;
                                        continue;
                                    }
                                case menu.m_Settings :
                                    {
                                        menu.m_currentMenu = menu.m_settingsMenu;
                                        break;
                                    }
                                case menu.m_Exit :
                                    {
                                        windowOpened = false;
                                        break;
                                    }
                            } // end of switch (menu.m_gameOverMode)

                        } // end of if (menu.m_currentMenu == menu.m_gameOverMenu)

                        if (menu.m_currentMenu == menu.m_difficultyLevelMenu)
                        {
                            switch (menu.m_difficultyLevelMenuMode)
                            {
                                case menu.m_easy :
                                    {
                                        game.m_difficultyLevel = 0;
                                        break;
                                    }
                                case menu.m_medium :
                                    {
                                        game.m_difficultyLevel = 1;
                                        break;
                                    }
                                case menu.m_hard :
                                    {
                                        game.m_difficultyLevel = 2;
                                        break;
                                    }
                                case menu.m_snakeKing :
                                    {
                                        game.m_difficultyLevel = 3;
                                        break;
                                    }
                            } // end of switch(menu.m_difficultyLevelMenuMode)

                            game.setDifficultyLevel();
                            menu.m_currentMenu = menu.m_mainMenu;

                        } // end of if (menu.m_currentMenu == menu.m_difficultyLevelMenu)

                        if (game.m_pauseGame)
                        {
                            if (menu.m_pauseMenuMode == menu.m_continue)
                            {
                                gameRunning = true;
                                game.m_pauseGame = false;
                            }
                            else //quit game
                            {
                                gameRunning = false;
                                game.resetGame();
                                menu.m_currentMenu = menu.m_mainMenu;
                                game.m_pauseGame = false;
                            }
                        } // end of if (game.m_pauseGame)
                        break;
                    } // end of case SDLK_SPACE, SDLK_RETURN

                } // end of switch ( m_menuEvent.key.keysym.sym )

            } // end of switch (m_menuEvent.type)

        } // end of while  SDL_PollEvent(m_menuEvent)


        // If depth test active, menu textures will only blit for main menu, before the game starts
        glDepthMask(GL_FALSE);


        //Choosing the right Menu to draw
        if (menu.m_currentMenu == menu.m_mainMenu &&
        !game.m_gameOver
        )
        {
            menu.drawMainMenu();
        }

        if (menu.m_currentMenu == menu.m_difficultyLevelMenu)
        {
            menu.drawDLSettings();
        }

        else if (game.m_pauseGame)
        {
            menu.drawPauseMenu();
        }

        if (game.m_gameOver &&
        menu.m_currentMenu != menu.m_difficultyLevelMenu
        )
        {
            menu.drawGameOverMenu();
        }

        SDL_GL_SwapWindow(window);



        // Game loop
        while (gameRunning)
        {
            while (SDL_PollEvent(&gameEvent))
            {
                switch (gameEvent.type)
                {
                    case SDL_QUIT:
                        {
                            gameRunning = false;
                            windowOpened= false;
                            break;
                        }
                    case SDL_WINDOWEVENT :
                        {
                            int m_newGameWidth, m_newGameHeight;
                            SDL_GetWindowSize(window, &m_newGameWidth, &m_newGameHeight);
                            game.resizeGame(m_newGameWidth, m_newGameHeight);
                            break;
                        }
                    case SDL_KEYDOWN :
                        switch ( gameEvent.key.keysym.sym )
                        {
                            case SDLK_ESCAPE :
                                {
                                    if (!game.m_gameOver)
                                    {
                                        game.m_pauseGame = true;
                                        menu.m_currentMenu = menu.m_pauseMenu;
                                        gameRunning = false;
                                    }
                                    else // game over
                                    {

                                        game.m_gameOver = true;
                                        menu.m_currentMenu = menu.m_gameOverMenu;
                                        gameRunning = false;
                                    }
                                    break;
                                }
                            case SDLK_RIGHT :
                                {
                                    if (game.m_snakeDirection != game.m_left)
                                    {
                                        game.m_snakeDirection = game.m_right;
                                    }
                                    break;
                                }
                            case SDLK_LEFT :
                                {
                                    if (game.m_snakeDirection != game.m_right)
                                    {
                                        game.m_snakeDirection = game.m_left;
                                    }
                                    break;
                                }
                            case SDLK_UP :
                                {
                                    if (game.m_snakeDirection != game.m_down)
                                    {
                                        game.m_snakeDirection = game.m_up;
                                    }
                                    break;
                                }
                            case SDLK_DOWN :
                                {
                                    if (game.m_snakeDirection != game.m_up)
                                    {
                                        game.m_snakeDirection = game.m_down;
                                    }
                                    break;
                                }
                            case SDLK_RETURN :
                                {
                                    if (game.m_gameOver)
                                    {
                                        game.m_showScoreHistory = true;
                                    }
                                }
                            default :  break;

                    } // end of switch m_gameEvent.key.keysym.sym

                    default : break;

                    } // end of switch (m_gameEvent.type)
                }   // end of while (SDL_PollEvent(&m_gameEvent))


            //Depth has to be enabled for 3D snake game
            glDepthMask(GL_TRUE);
            game.drawGame();
            SDL_GL_SwapWindow(window);

        } // end of while (m_gameRunning)
    } //end of while (m_windowOpened)

    SDL_Quit();
    return EXIT_SUCCESS;
}
//--------------------------------------------------------------------------------------------------------------
SDL_GLContext getOpenGLContext(SDL_Window *_window)
{
    #ifdef __APPLE__
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    #else

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    #endif

        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,4);
        // Turn on double buffering with a 24bit Z buffer.
        // You may need to change this to 16 or 32 for your system
        // on mac up to 32 will work but under linux centos build only 16
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        // enable double buffering (should be on by default)
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        //
        return SDL_GL_CreateContext(_window);
}
//--------------------------------------------------------------------------------------------------------------
void SDLError(const std::string &_errorMessage)
{
    std::cerr <<_errorMessage << std::endl;
    std::cerr << SDL_GetError() << std::endl;
    SDL_Quit();
    exit(EXIT_FAILURE);
}
//--------------------------------------------------------------------------------------------------------------
