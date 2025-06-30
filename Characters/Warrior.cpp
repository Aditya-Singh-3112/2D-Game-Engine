#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Engine.h"
#include "CollisionHandler.h"
#include "Camera.h"
#include "Collider.h"
#include <iostream>

Warrior::Warrior(Properties* props) : Character(props)
{
    m_Flip = SDL_FLIP_NONE;
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;
    m_AttackTime = ATTACK_TIME;

    m_Collider = new Collider();
    m_Collider->SetBuffer(25, 40, -30, -10);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(9.0f);

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 0, 8, 80);

    if (m_Collider == nullptr){
        SDL_Log("no collider");
    }

    if (m_RigidBody == nullptr){
        SDL_Log("no rb");
    }

    if (m_Animation == nullptr){
        SDL_Log("no animation");
    }

}

void Warrior::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

    /*Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);*/
}

void Warrior::Update(float dt)
{
    std::cout << "=== Warrior::Update start ===\n";

    // Reset state
    m_IsRunning = false;
    m_IsShielding = false;
    m_RigidBody->UnsetForce();
    std::cout << "  [1] after resetting force and states\n";

    // Horizontal input
    if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD && !m_IsAttacking) {
        m_RigidBody->ApplyForceX(FORWARD * RUN_FORCE);
        m_Flip = SDL_FLIP_NONE;
        m_IsRunning = true;
    }
    if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD && !m_IsAttacking) {
        m_RigidBody->ApplyForceX(BACKWARD * RUN_FORCE);
        m_Flip = SDL_FLIP_HORIZONTAL;
        m_IsRunning = true;
    }
    std::cout << "  [2] after horizontal input (running=" << m_IsRunning << ")\n";

    // Shield / Attack / Jump input
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_I)) {
        m_RigidBody->UnsetForce();
        m_IsShielding = true;
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J)) {
        m_RigidBody->UnsetForce();
        m_IsAttacking = true;
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsGrounded) {
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
    }
    // Continued jump while holding space
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsJumping && m_JumpTime > 0) {
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
    } else {
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }
    std::cout << "  [3] after shield/attack/jump input (jumping=" << m_IsJumping << ")\n";

    // Attack timer
    if (m_IsAttacking && m_AttackTime > 0) {
        m_AttackTime -= dt;
    } else {
        m_IsAttacking = false;
        m_AttackTime = ATTACK_TIME;
    }
    std::cout << "  [4] after attack timer (attacking=" << m_IsAttacking << ")\n";

    // --- X-axis movement ---
    std::cout << "  [5] before first RigidBody->Update\n";
    m_RigidBody->Update(dt);
    std::cout << "  [6] after first RigidBody->Update\n";

    m_LastSafePosition.X = m_Transform->X;
    std::cout << "    saved last safe X = " << m_LastSafePosition.X << "\n";

    m_Transform->X += m_RigidBody->Position().X;
    std::cout << "    moved X to " << m_Transform->X << "\n";

    m_Collider->Set(m_Transform->X, m_Transform->Y, 18, 50);
    std::cout << "  [7] after collider->Set on X\n";

    std::cout << "  [8] before MapCollision on X\n";
    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
        std::cout << "    MapCollision detected on X!\n";
        m_Transform->X = m_LastSafePosition.X;
        std::cout << "    restored X to " << m_Transform->X << "\n";
    }

    // --- Y-axis movement ---
    std::cout << "  [9] before second RigidBody->Update\n";
    m_RigidBody->Update(dt);
    std::cout << "  [10] after second RigidBody->Update\n";

    m_LastSafePosition.Y = m_Transform->Y;
    std::cout << "    saved last safe Y = " << m_LastSafePosition.Y << "\n";

    m_Transform->Y += m_RigidBody->Position().Y;
    std::cout << "    moved Y to " << m_Transform->Y << "\n";

    m_Collider->Set(m_Transform->X, m_Transform->Y, 18, 50);
    std::cout << "  [11] after collider->Set on Y\n";

    std::cout << "  [12] before MapCollision on Y\n";
    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
        std::cout << "    MapCollision detected on Y! Setting grounded=true\n";
        m_IsGrounded = true;
        m_Transform->Y = m_LastSafePosition.Y;
        std::cout << "    restored Y to " << m_Transform->Y << "\n";
    } else {
        m_IsGrounded = false;
    }

    std::cout << "  [13] after Y-axis collision (grounded=" << m_IsGrounded << ")\n";

    // Update origin
    m_Origin->X = m_Transform->X + m_Width / 2;
    m_Origin->Y = m_Transform->Y + m_Height / 2;
    std::cout << "  [14] origin updated to ("
              << m_Origin->X << ", " << m_Origin->Y << ")\n";

    // Animation
    AnimationState();
    m_Animation->Update();
    std::cout << "  [15] animation updated\n";

    std::cout << "=== Warrior::Update end ===\n";
}

void Warrior::AnimationState()
{
    m_Animation->SetProps("player_idle", 0, 6, 80);

    if (m_IsRunning){
        m_Animation->SetProps("player_run", 0, 8, 80);
    }

    if (m_IsShielding){
        m_Animation->SetProps("player_shield", 0, 2, 80);
    }

    if (m_IsAttacking){
        m_Animation->SetProps("player_attack1", 0, 4, 80);
    }

    if (m_IsJumping){
        m_Animation->SetProps("player_jump", 0, 10, 80);
    }

}

void Warrior::Clean()
{
    TextureManager::GetInstance()->Clean();
}
