#include "Menu.h"
#include <iostream>
//--------------------------------------------------------------------------------------------------------------
Menu::Menu(SDL_Window* _window)
{
    m_menuWindowCopy = _window;
    m_menuScreenSurface = SDL_GetWindowSurface(m_menuWindowCopy);

    m_mainMenuStartGame = SDL_LoadBMP("textures/Start.bmp");
    m_mainMenuDiffucultyLevel = SDL_LoadBMP("textures/DL.bmp");
    m_mainMenuSoundSettings = SDL_LoadBMP("textures/Settings.bmp");
    m_mainMenuExit = SDL_LoadBMP("textures/Exit.bmp");
    m_DLEasy = SDL_LoadBMP("textures/DLEasy.bmp");
    m_DLMedium = SDL_LoadBMP("textures/DLMedium.bmp");
    m_DLHard = SDL_LoadBMP("textures/DLHard.bmp");
    m_DLSnakeKing = SDL_LoadBMP("textures/DLSK.bmp");
    m_PauseContinue = SDL_LoadBMP("textures/PCont.bmp");
    m_PauseExit = SDL_LoadBMP("textures/PExit.bmp");
    m_GOPlay = SDL_LoadBMP("textures/GOPlay.bmp");
    m_GODL = SDL_LoadBMP("textures/GODL.bmp");
    m_GOSettings = SDL_LoadBMP("textures/GOSettings.bmp");
    m_GOExit = SDL_LoadBMP("textures/GOExit.bmp");

    if (m_mainMenuStartGame == NULL ||
    m_mainMenuDiffucultyLevel == NULL ||
    m_mainMenuSoundSettings == NULL ||
    m_mainMenuExit == NULL ||
    m_DLEasy == NULL ||
    m_DLMedium == NULL ||
    m_DLHard == NULL ||
    m_DLSnakeKing == NULL ||
    m_PauseContinue == NULL ||
    m_PauseExit == NULL
    )
    {
        std::cout << "Could not load an image: " << SDL_GetError() << std::endl << std::endl;
    }
}
//--------------------------------------------------------------------------------------------------------------
Menu::~Menu()
{
    SDL_FreeSurface(m_mainMenuStartGame);
    SDL_FreeSurface(m_mainMenuDiffucultyLevel);
    SDL_FreeSurface(m_mainMenuSoundSettings);
    SDL_FreeSurface(m_mainMenuExit);
    SDL_FreeSurface(m_menuCurrentImageSurface);
    SDL_FreeSurface(m_DLEasy);
    SDL_FreeSurface(m_DLMedium);
    SDL_FreeSurface(m_DLHard);
    SDL_FreeSurface(m_DLSnakeKing);
    SDL_FreeSurface(m_PauseContinue);
    SDL_FreeSurface(m_PauseExit);
    SDL_FreeSurface(m_GOPlay);
    SDL_FreeSurface(m_GODL);
    SDL_FreeSurface(m_GOSettings);
    SDL_FreeSurface(m_GOExit);

    m_mainMenuStartGame = NULL;
    m_mainMenuDiffucultyLevel = NULL;
    m_mainMenuSoundSettings = NULL;
    m_mainMenuExit = NULL;
    m_menuCurrentImageSurface = NULL;
    m_DLEasy = NULL;
    m_DLMedium = NULL;
    m_DLHard = NULL;
    m_DLSnakeKing = NULL;
    m_PauseContinue = NULL;
    m_PauseExit = NULL;
    m_menuWindowCopy = NULL;
    m_GOPlay = NULL;
    m_GODL = NULL;
    m_GOSettings = NULL;
    m_GOExit = NULL;

    SDL_DestroyWindow(m_menuWindowCopy);
}
//--------------------------------------------------------------------------------------------------------------
void Menu::resizeMenu(int _newMenuWidth, int _newMenuHeight,SDL_Window* _window )
{
    glViewport(0, 0, _newMenuWidth, _newMenuHeight);
    m_menuWindowCopy = _window;
    m_menuScreenSurface = SDL_GetWindowSurface(m_menuWindowCopy);
    m_menuCurrentImageSurface = SDL_GetWindowSurface(m_menuWindowCopy);;
}
//--------------------------------------------------------------------------------------------------------------
void Menu::drawMainMenu()
{
    glUseProgram(0);
    m_currentMenu = m_mainMenu;

    switch (m_mainMenuMode)
    {
    case 0 :    // start game
        {
            m_menuCurrentImageSurface = m_mainMenuStartGame;
            break;
        }
    case 1 :    // difficulty level
        {
            m_menuCurrentImageSurface = m_mainMenuDiffucultyLevel;
            break;
        }
    case 2 :    // settings
        {
        m_menuCurrentImageSurface = m_mainMenuSoundSettings;
        break;
        }
    case 3 :    // exit
        {
        m_menuCurrentImageSurface = m_mainMenuExit;
        break;
        }
    }

    SDL_BlitSurface (m_menuCurrentImageSurface, NULL, m_menuScreenSurface, NULL);
    SDL_UpdateWindowSurface(m_menuWindowCopy);
}
//--------------------------------------------------------------------------------------------------------------
void Menu::drawDLSettings()
{
    glUseProgram(0);
    m_menuCurrentImageSurface = m_DLEasy;

    switch (m_difficultyLevelMenuMode)
    {
    case 0 :
        {
            m_menuCurrentImageSurface = m_DLEasy;
            break;
        }
    case 1 :
        {
            m_menuCurrentImageSurface = m_DLMedium;
            break;
        }
    case 2 :
        {
            m_menuCurrentImageSurface = m_DLHard;
            break;
        }
    case 3 :
        {
            m_menuCurrentImageSurface = m_DLSnakeKing;
            break;
        }
    }

    SDL_BlitSurface (m_menuCurrentImageSurface, NULL, m_menuScreenSurface, NULL);
    SDL_UpdateWindowSurface(m_menuWindowCopy);
}
//--------------------------------------------------------------------------------------------------------------
void Menu::drawPauseMenu()
{
    glUseProgram(0);
    m_menuCurrentImageSurface = m_PauseContinue;

    if (m_pauseMenuMode == m_continue)
    {
        m_menuCurrentImageSurface = m_PauseContinue;
    }
    else // quit game
    {
        m_menuCurrentImageSurface = m_PauseExit;
    }

    SDL_BlitSurface (m_menuCurrentImageSurface, NULL, m_menuScreenSurface, NULL);
    SDL_UpdateWindowSurface(m_menuWindowCopy);
}
//--------------------------------------------------------------------------------------------------------------
void Menu::drawGameOverMenu()
{
    glUseProgram(0);

    switch (m_gameOverMode)
    {
    case 0 :
        {
        m_menuCurrentImageSurface = m_GOPlay;
        break;
        }
    case 1 :
        {
        m_menuCurrentImageSurface = m_GODL;
        break;
        }
    case 2 :
        {
        m_menuCurrentImageSurface = m_GOSettings;
        break;
        }
    case 3 :
        {
        m_menuCurrentImageSurface = m_GOExit;
        break;
        }
    }

    SDL_BlitSurface (m_menuCurrentImageSurface, NULL, m_menuScreenSurface, NULL);
    SDL_UpdateWindowSurface(m_menuWindowCopy);
}
//--------------------------------------------------------------------------------------------------------------




