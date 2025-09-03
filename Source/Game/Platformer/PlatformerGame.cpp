#include "PlatformerGame.h"
#include <Component.h>
#include <Engine.h>


bool PlatformerGame::Initialize() {
    OBSERVER_ADD(player_dead);
    OBSERVER_ADD(add_points);

    m_scene = std::make_unique<viper::Scene>(this);
    m_scene->Load("scenes/prototypes.json");
    m_scene->Load("scenes/level.json");

	return true;

}

void PlatformerGame::Shutdown() {
    //
}

void PlatformerGame::Update(float dt) {
    switch (m_gameState)
    {
    case PlatformerGame::GameState::Initialize:
        m_gameState = GameState::StartRound;
        break;
    case PlatformerGame::GameState::Title:
        break;
    case PlatformerGame::GameState::StartGame:
        break;
    case PlatformerGame::GameState::StartRound:
        SpawnPlayer();
        SpawnEnemy();
        m_gameState = GameState::Game;
        break;
    case PlatformerGame::GameState::Game:
        break;
    case PlatformerGame::GameState::PlayerDead:
        break;
    case PlatformerGame::GameState::GameOver:
        break;
    default:
        break;
    }
    m_scene->Update(viper::GetEngine().GetTime().GetDeltaTime());


}
void PlatformerGame::Draw(class viper::Renderer& renderer) {
    m_scene->Draw(renderer);
    viper::GetEngine().GetPS().Draw(renderer);
}

void PlatformerGame::OnPlayerDeath() {

}
void PlatformerGame::OnNotify(const viper::Event& event) {

}

void PlatformerGame::SpawnEnemy() {
    auto player = viper::Instantiate("platformenemy");
    //player->transform.position = viper::vec2{ viper::random::getReal(0.0f, 1080.0f), viper::random::getReal(0.0f, 100.0f) };
    m_scene->AddActor(std::move(player));
}

void PlatformerGame::SpawnPlayer() {
    auto player = viper::Instantiate("platformplayer");
    //player->transform.position = viper::vec2{ viper::random::getReal(0.0f, 1080.0f), viper::random::getReal(0.0f, 100.0f) };
    m_scene->AddActor(std::move(player));
}
