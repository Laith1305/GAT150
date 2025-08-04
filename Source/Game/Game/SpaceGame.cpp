#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"
#include "Input/InputSystem.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "GameData.h"

#include <vector>

bool SpaceGame::Initialize()
{
    m_scene = std::make_unique<viper::Scene>(this);

    m_titleFont = std::make_shared<viper::Font>();
    m_titleFont->Load("arcadeclassic.ttf", 128);

    m_uiFont = std::make_shared<viper::Font>();
    m_uiFont->Load("arcadeclassic.ttf", 48);

    m_titleText = std::make_unique<viper::Text>(m_titleFont);
    m_scoreText = std::make_unique<viper::Text>(m_uiFont);
    m_livesText = std::make_unique<viper::Text>(m_uiFont);
        
    return true;
}

void SpaceGame::Update(float dt)
{
    switch (m_gameState)
    {
    case SpaceGame::GameState::Initialize:
        m_gameState = GameState::Title;
        break;

    case SpaceGame::GameState::Title:
        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gameState = GameState::StartGame;
        }
        break;

    case SpaceGame::GameState::StartGame:
        m_score = 0;
        m_lives = 3;
        m_gameState = GameState::StartRound;
        break;

    case SpaceGame::GameState::StartRound:
    {
        m_scene->RemoveAllActors();

        // create player
        std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(GameData::shipPoints, viper::vec3{ 0.0f, 0.4f, 1.0f });
        viper::Transform transform{ viper::vec2{ viper::GetEngine().GetRenderer().GetWidth() * 0.5f, viper::GetEngine().GetRenderer().GetHeight() * 0.5f }, 0, 5 };
        auto player = std::make_unique<Player>(transform, model);
        player->speed = 1500.0f;
        player->rotationRate = 180.0f;
        player->damping = 1.5f;
        player->name = "player";
        player->tag = "player";

        m_scene->AddActor(std::move(player));
        m_gameState = GameState::Game;
    }
        break;
    case SpaceGame::GameState::Game:
        m_enemySpawnTimer -= dt;
        if (m_enemySpawnTimer <= 0) {
            m_enemySpawnTimer = 2;
            SpawnEnemy();
        }

        break;
    case SpaceGame::GameState::PlayerDead:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
            m_lives--;
            if (m_lives == 0) {
                m_gameState = GameState::GameOver;
                m_stateTimer = 3;
            }
            else {
                m_gameState = GameState::StartRound;
            }
        }
        break;
    case SpaceGame::GameState::GameOver:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
            m_gameState = GameState::Title;
        }
        break;
    default:
        break;
    }

    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_Q)) {
        viper::GetEngine().GetTime().SetTimeScale(0.15f);
    }
    else {
        viper::GetEngine().GetTime().SetTimeScale(1.0f);
    }

    m_scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw(viper::Renderer& renderer) {
    if (m_gameState == GameState::Title) {
        m_titleText->Create(renderer, "PIT VIPER", viper::vec3{ 1, 0, 0 });
        m_titleText->Draw(renderer, 400, 400);
    }
    if (m_gameState == GameState::GameOver) {
        m_titleText->Create(renderer, "GAME OVER", viper::vec3{ 1, 0, 0 });
        m_titleText->Draw(renderer, 400, 400);
    }

    m_scoreText->Create(renderer, "SCORE  " + std::to_string(m_score), { 1, 1, 1 });
    m_scoreText->Draw(renderer, 20, 20);

    m_livesText->Create(renderer, "LIVES  " + std::to_string(m_lives), {1, 1, 1});
    m_livesText->Draw(renderer, (float)(renderer.GetWidth() - 200), (float)20);

    m_scene->Draw(renderer);

    viper::GetEngine().GetPS().Draw(renderer);
}

void SpaceGame::OnPlayerDeath() {
    m_gameState = GameState::PlayerDead;
    m_stateTimer = 2;
}

void SpaceGame::SpawnEnemy() {
    Player* player = m_scene->GetActorByName<Player>("player");
    if (player) {
        std::shared_ptr<viper::Model> enemyModel = std::make_shared<viper::Model>(GameData::shipPoints, viper::vec3{ 1, 0, 0 });

        // spawn at random position away from player
        viper::vec2 position = player->transform.position + viper::random::onUnitCircle() * viper::random::getReal(200.0f, 500.0f);
        viper::Transform transform{ position, viper::random::getReal(0.0f, 360.0f), 10};

        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, enemyModel);
        enemy->damping = 0.5f;
        enemy->fireTime = 3;
        enemy->fireTimer = 5;
        enemy->speed = (viper::random::getReal() * 200) + 100;
        enemy->tag = "enemy";
        m_scene->AddActor(std::move(enemy));
    }

}

void SpaceGame::Shutdown() {
    //
}
