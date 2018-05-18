#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <ngl/NGLInit.h>


//-------------------------------------------------------------------------------------------------------
class Menu
{
    public:


        enum m_Menus
        {
            m_mainMenu,
            m_difficultyLevelMenu,
            m_settingsMenu,
            m_pauseMenu,
            m_gameOverMenu
        };
        m_Menus m_currentMenu = m_mainMenu;



        enum m_mainMenuModes
        {
            m_startGame,
            m_difficultyLevel,
            m_settings,
            m_exit
        };
        int m_mainMenuMode = m_startGame;

        enum m_DifficultyLevelModes
        {
            m_easy,
            m_medium,
            m_hard,
            m_snakeKing
        };
        int m_difficultyLevelMenuMode = m_easy;

        enum m_pauseMenuModes
        {
            m_continue,
            m_quitGame
        };
        int m_pauseMenuMode = m_continue;

        enum m_gameOverModes
        {
            m_playAgain,
            m_DifficulyLevel,
            m_Settings,
            m_Exit
        };
        int m_gameOverMode = m_playAgain;


        Menu(SDL_Window* _window);
        ~Menu();
        void resizeMenu(int _newWidth, int _newHeight, SDL_Window* _window);
        void drawMainMenu();
        void drawDLSettings();
        void drawPauseMenu();
        void drawGameOverMenu();

//-------------------------------------------------------------------------------------------------------
    private:

        SDL_Window *m_menuWindowCopy;

        SDL_Surface* m_menuScreenSurface = NULL;    //gScreenSurface
        SDL_Surface* m_mainMenuStartGame = NULL;
        SDL_Surface* m_mainMenuDiffucultyLevel =NULL;
        SDL_Surface* m_mainMenuSoundSettings = NULL;
        SDL_Surface* m_mainMenuExit = NULL;
        SDL_Surface* m_DLEasy = NULL;
        SDL_Surface* m_DLMedium = NULL;
        SDL_Surface* m_DLHard = NULL;
        SDL_Surface* m_DLSnakeKing = NULL;
        SDL_Surface* m_menuCurrentImageSurface = NULL;
        SDL_Surface* m_PauseContinue = NULL;
        SDL_Surface* m_PauseExit = NULL;
        SDL_Surface* m_GOPlay = NULL;
        SDL_Surface* m_GODL = NULL;
        SDL_Surface* m_GOSettings = NULL;
        SDL_Surface* m_GOExit = NULL;

};
//-------------------------------------------------------------------------------------------------------
#endif  //MENU_H'

