#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Transform.h"
#include "IObject.h" // Assuming the correct header name for IObject
#include <string>    // Correct header for std::string
#include <SDL.h>
#include <SDL_image.h>
#include "Point.h"

struct Properties {
    Properties(std::string textureID, float x, float y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE) {
        X = x;
        Y = y;
        Flip = flip;
        Width = width;
        Height = height;
        TextureID = textureID;
    }

    std::string TextureID;
    int Width, Height;
    float X, Y;
    SDL_RendererFlip Flip;
};

class GameObject : public IObject {
public:
    GameObject(Properties* props) : m_TextureID(props->TextureID), m_Width(props->Width), m_Height(props->Height), m_Flip(props->Flip) {
        m_Transform = new Transform(props->X, props->Y);

        float px = props->X + props->Width / 2;
        float py = props->Y + props->Height / 2;
        m_Origin = new Point(px, py);
    }

    virtual ~GameObject() { delete m_Transform; }

    inline Point* GetOrigin() {return m_Origin;}

    virtual void Draw() = 0;
    virtual void Update(float dt) = 0;
    virtual void Clean() = 0;

protected:
    Point* m_Origin;
    std::string m_TextureID;
    Transform* m_Transform;
    int m_Width, m_Height;
    SDL_RendererFlip m_Flip;
};

#endif // GAMEOBJECT_H
