#include "Player.h"
#include "Rocket.h"
#include "Engine.h"
#include "SpaceGame.h"
#include "GameData.h"
#include "Math/Vector3.h"
#include "Core/Random.h"
#include "Framework/Scene.h"

#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include <Components/SpriteRenderer.h>
#include <Components/RigidBody.h>
#include <Components/CircleCollider2D.h>
#include <AudioClip.h>

void Player::Update(float dt)
{
    viper::Particle particle;
    particle.position = transform.position;
    particle.velocity = viper::vec2{ viper::random::getReal(-200.0f, 200.0f), viper::random::getReal(-200.0f, 200.0f) };
    particle.color = viper::vec3{ 1, 1, 1 };
    particle.lifespan = 2;
    //viper::GetEngine().GetPS().AddParticle(particle);

    // rotation
    float rotate = 0;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;

    transform.rotation += (rotate * rotationRate) * dt;

    // thrust
    float thrust = 0;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +1;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

    viper::vec2 direction{ 1, 0 };
    viper::vec2 force = direction.Rotate(viper::math::degToRad(transform.rotation)) * thrust * speed;
    //velocity += force * dt;


    auto* rb = GetComponent<viper::RigidBody>();
    if (rb) {
        rb->velocity += force * dt;
    }


    transform.position.x = viper::math::wrap(transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    transform.position.y = viper::math::wrap(transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

    // check fire key pressed
    fireTimer -= dt;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && fireTimer <= 0) {
        fireTimer = fireTime;

        //viper::GetEngine().GetAudio().PlaySound("clap");


        auto sound = viper::Resources().Get<viper::AudioClip>("bass.wav", viper::GetEngine().GetAudio()).get();
        if (sound) {
            viper::GetEngine().GetAudio().PlaySound(*sound);
        }

        


        //viper::GetEngine().GetAudio().PlaySound(*viper::Resources().Get<viper::AudioClip>("bass.wav", viper::GetEngine().GetAudio()).get());
        //std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(GameData::shipPoints, viper::vec3{ 1.0f, 1.0f, 1.0f });
        // spawn rocket at player position and rotation
        viper::Transform transform{ this->transform.position, this->transform.rotation, 2.0f };
        auto rocket = std::make_unique<Rocket>(transform);
        rocket->speed = 1500.0f;
        rocket->lifespan = 1.5f;
        rocket->name = "rocket";
        rocket->tag = "player";


        auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
        spriteRenderer->textureName = "textures/missile-2.png";

        rocket->AddComponent(std::move(spriteRenderer));


        auto rb = std::make_unique<viper::RigidBody>();
        rocket->AddComponent(std::move(rb));

        auto collider = std::make_unique<viper::CircleCollider2D>();
        collider->radius = 10;
        rocket->AddComponent(std::move(collider));

        scene->AddActor(std::move(rocket));
    }

    Actor::Update(dt);
}

void Player::OnCollision(Actor* other)
{
    if (tag != other->tag) {
        destroyed = true;
        dynamic_cast<SpaceGame*>(scene->GetGame())->OnPlayerDeath();
    }
}

