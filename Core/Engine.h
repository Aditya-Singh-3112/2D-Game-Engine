#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"
#include "SDL_image.h"
#include "GameMap.h"

#define SCREEN_WIDTH 1720
#define SCREEN_HEIGHT 880

class Engine
{
    public:
        static Engine* GetInstance(){
            /*
            Making the engine class singleton, meaning only one instance of the class can exist at a time
            */
            return s_Instance = (s_Instance != nullptr)? s_Instance : new Engine();
        }

        bool Init(); // Initialize the Engine
        bool Clean(); // Clean the file, makes sure everything closes
        void Quit(); // Quits the engines

        void Update(); // Update the engine state
        void Render(); // Renders the animations
        void Events(); // Handles the events

        inline GameMap* GetMap(){return m_LevelMap;}
        inline bool IsRunning(){return m_IsRunning;}
        inline SDL_Renderer* GetRenderer(){return m_Renderer;}

    private:
        Engine(){}
        bool m_IsRunning;
        GameMap* m_LevelMap;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        static Engine* s_Instance;
};

#endif
