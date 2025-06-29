#include "CollisionHandler.h"
#include "Engine.h"

CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler()
{
    m_CollisionLayer = (TileLayer*)Engine::GetInstance()->GetMap()->GetMapLayers().front();
    m_CollisionTilemap  = m_CollisionLayer->GetTileMap();
}

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b)
{
    bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);

    return (x_overlaps && y_overlaps);
}

bool CollisionHandler::MapCollision(SDL_Rect a)
{
    const int tilesize = 32;
    const int RowCount = 20;
    const int ColCount = 60;

    int left_tile   = a.x / tilesize;
    int right_tile  = (a.x + a.w) / tilesize;
    int top_tile    = a.y / tilesize;
    int bottom_tile = (a.y + a.h) / tilesize;

    left_tile   = std::max(0,           left_tile);
    top_tile    = std::max(0,           top_tile);
    right_tile  = std::min(ColCount-1,  right_tile);
    bottom_tile = std::min(RowCount-1,  bottom_tile);

    for (int ty = top_tile; ty <= bottom_tile; ++ty) {
        for (int tx = left_tile; tx <= right_tile; ++tx) {
            if (m_CollisionTilemap[ty][tx] > 0)
                return true;
        }
    }
    return false;
}
