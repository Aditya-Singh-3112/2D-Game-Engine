#include "TextureManager.h"
#include "Engine.h"
#include "Camera.h"

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(std::string id, std::string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr){
        SDL_Log("Failed to load texture : %s, %s", filename.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if (texture == nullptr){
        SDL_Log("Failed to load texture from surface: %s", SDL_GetError());
        return false;
    }

    m_TextureMap[id] = texture;

    return true;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, width, height};
    Vector2D cam = Camera::GetInstance()->GetPosition()*0.5;
    SDL_Rect dstRect = {x - cam.X, y - cam.Y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {width*frame, height*row, width, height};
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = {x - cam.X, y - cam.Y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {tileSize * frame, tileSize * row, tileSize, tileSize};
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = {x - cam.X, y - cam.Y, tileSize, tileSize};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tilesetID], &srcRect, &dstRect, 0, 0, flip);
}

void TextureManager::Drop(std::string id)
{
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}

void TextureManager::Clean()
{
    std::map<std::string, SDL_Texture*>::iterator it;
    for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++){
        SDL_DestroyTexture(it->second);
    }

    m_TextureMap.clear();

    SDL_Log("texture map cleaned");
}
