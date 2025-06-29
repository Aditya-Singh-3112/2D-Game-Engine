#ifndef ANIMATION_H
#define ANIMATION_H

#include "SDL.h"
#include <string>

class Animation
{
    public:
        Animation() {}

        void Update();
        void Draw(float x, float y, int spritWidth, int spritHeight, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void SetProps(std::string textureID, int spritRow, int frameCount, int speed);

    private:
        int m_Speed;
        int m_SpriteRow;
        int m_FrameCount;
        int m_CurrentFrame;
        std::string m_TextureID;

};

#endif // ANIMATION_H
