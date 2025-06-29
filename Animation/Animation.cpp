#include "Animation.h"
#include "TextureManager.h"

void Animation::Update()
{
    m_CurrentFrame = (SDL_GetTicks()/m_Speed) % m_FrameCount;
}

void Animation::Draw(float x, float y, int width, int height, SDL_RendererFlip flip)
{
    TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, width, height, m_SpriteRow, m_CurrentFrame, flip);
}

void Animation::SetProps(std::string textureID, int spritRow, int frameCount, int speed)
{
    m_Speed = speed;
    m_TextureID = textureID;
    m_SpriteRow = spritRow;
    m_FrameCount = frameCount;
}

