#include "game_phase.h"

void Game::CPhase::OnEnter()
{
    OnInternEnter();
}

Game::CPhase::EType Game::CPhase::OnRun()
{
    return OnInternRun();  
}

void Game::CPhase::OnLeave()
{
    OnInternLeave();
}

void Game::CPhase::OnInternEnter()
{
    // Optional: Default-Implementierung (leer)
}

Game::CPhase::EType Game::CPhase::OnInternRun()
{
    return CPhase::Undefined;  // Oder beliebiger Default
}

void Game::CPhase::OnInternLeave()
{
    // Optional: Default-Implementierung (leer)
}
