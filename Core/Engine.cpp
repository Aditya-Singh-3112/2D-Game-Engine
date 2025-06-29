#include "Engine.h"
#include <iostream>
#include "TextureManager.h"
#include "Vector2D.h"
#include "Transform.h"
#include "Warrior.h"
#include "Input.h"
#include "SDL.h"
#include "Timer.h"
#include "MapParser.h"
#include "Camera.h"

Engine* Engine::s_Instance = nullptr;
Warrior* player = nullptr;

bool Engine::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0){
        SDL_Log("Failed to initialize SDL : %s", SDL_GetError());
        return false;
    }

    m_Window = SDL_CreateWindow("2D ENGINE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (m_Window == nullptr){
        SDL_Log("SDL failed to create window : %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_Renderer == nullptr){
        SDL_Log("SDL failed to create renderer : %s", SDL_GetError());
        return false;
    }

    if (!MapParser::GetInstance()->Load()){
        SDL_Log("Failed to load map");
    }

    m_LevelMap = MapParser::GetInstance()->GetMaps("level1");

    // Loading fighter class animation sprit sheets
    TextureManager::GetInstance()->Load("player_walk", "assets/Fighter/Walk.png");
    TextureManager::GetInstance()->Load("player_idle", "assets/Fighter/Idle.png");
    TextureManager::GetInstance()->Load("player_run", "assets/Fighter/Run.png");
    TextureManager::GetInstance()->Load("player_jump", "assets/Fighter/Jump.png");
    TextureManager::GetInstance()->Load("player_shield", "assets/Fighter/Shield.png");
    TextureManager::GetInstance()->Load("player_hurt", "assets/Fighter/Hurt.png");
    TextureManager::GetInstance()->Load("player_dead", "assets/Fighter/Dead.png");
    TextureManager::GetInstance()->Load("player_attack3", "assets/Fighter/Attack_3.png");
    TextureManager::GetInstance()->Load("player_attack2", "assets/Fighter/Attack_2.png");
    TextureManager::GetInstance()->Load("player_attack1", "assets/Fighter/Attack_1.png");
    TextureManager::GetInstance()->Load("BG", "assets/Maps/BackGroundLayers/bg.png");
    player = new Warrior(new Properties("player_idel", 100, 200, 128, 128));

    Transform tf;
    tf.Log();

    Camera::GetInstance()->SetTarget(player->GetOrigin());

    return m_IsRunning = true;
}

bool Engine::Clean()
{
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
    return true;
}

void Engine::Quit()
{
    m_IsRunning = false;
}

void Engine::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    m_LevelMap->Update();
    Camera::GetInstance()->Update(dt);
    player->Update(dt);
}
void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);
    TextureManager::GetInstance()->Draw("BG", 0, 0, 2946, 880);
    m_LevelMap->Render();

    player->Draw();

    SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}
