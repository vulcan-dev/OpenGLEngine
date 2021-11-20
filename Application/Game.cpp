#include "Game.h"

Game::Game() {

}

void Game::OnAttach() {
    APP_INFO("Attached");
}

void Game::OnUpdate(const float &dt) {

}

void Game::OnRender(const float &dt) {

}

void Game::OnDetach() {
    APP_INFO("Detatched");
}

Game::~Game() {

}
