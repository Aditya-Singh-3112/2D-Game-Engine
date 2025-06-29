#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Engine.h"
#include "CollisionHandler.h"
#include "Camera.h"
#include "Collider.h"

Warrior::Warrior(Properties* props) : Character(props)
{
    m_IsAttacking = false;
    m_IsShielding = false;
    m_IsFalling = false;
    m_IsGrounded = false;
    m_IsJumping = false;
    m_IsRunning = false;
    m_IsWalking = false;

    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;
    m_AttackTime = ATTACK_TIME;

    m_Collider = new Collider();
    m_Collider->SetBuffer(25, 40, -30, -10);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(9.0f);

    m_Animation = new Animation();
    m_Animation->SetProps("player_idel", 0, 8, 80);
}

void Warrior::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Warrior::Update(float dt)
{
   m_IsRunning = false;
   m_IsShielding = false;
   m_RigidBody->UnsetForce();

   if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD && !m_IsAttacking){
        m_RigidBody->ApplyForceX(FORWARD * RUN_FORCE);
        m_Flip = SDL_FLIP_NONE;
        m_IsRunning = true;
   }

   if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD && !m_IsAttacking){
        m_RigidBody->ApplyForceX(BACKWARD * RUN_FORCE);
        m_Flip = SDL_FLIP_HORIZONTAL;
        m_IsRunning = true;
   }

   if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_I)){
        m_RigidBody->UnsetForce();
        m_IsShielding = true;
   }

   if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J)){
        m_RigidBody->UnsetForce();
        m_IsAttacking = true;
   }

   if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsGrounded){
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
   }

   if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsJumping && m_JumpTime > 0){
    m_JumpTime -= dt;
    m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
   }
   else{
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
   }

    if(m_IsAttacking && m_AttackTime > 0){
        m_AttackTime -= dt;
    }
    else{
        m_IsAttacking = false;
        m_AttackTime = ATTACK_TIME;
    }

    // move on x-axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 18, 50);

    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())){
        m_Transform->X = m_LastSafePosition.X;
    }

    // move on y-axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 18, 50);

    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())){
        m_IsGrounded = true;
        m_Transform->Y = m_LastSafePosition.Y;
    }
    else{
        m_IsGrounded = false;
    }

    m_Origin->X = m_Transform->X + m_Width/2;
    m_Origin->Y = m_Transform->Y + m_Height/2;

    AnimationState();
    m_Animation->Update();

}
void Warrior::AnimationState()
{
    m_Animation->SetProps("player_idel", 0, 6, 80);

    if (m_IsWalking){
        m_Animation->SetProps("player_walk", 0, 8, 80);
    }

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
