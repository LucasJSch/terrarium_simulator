#include <iostream>
#include <functional>
#include <memory>

#include "cell_mock.h"
#include "insect.h"
#include "insects_metrics.h"

namespace ekumen {
namespace simulation {

void Insect::Die() {
    cell->Free();
    is_dead = true;
    metrics.SetDead();
}

void Insect::SetRoundResultsCallback(std::function<void(InsectCallbackMetrics&)> callback) {
    round_finished_callback = callback;
}

void Insect::Breed() {
    if (!CanBreed()) {
        return;
    }
    std::shared_ptr<Cell> free_cell = WhereCanIBreed();
    if (free_cell == nullptr) {
        return;
    }
    std::shared_ptr<Insect> newborn = GetNewborn(free_cell);
    free_cell->Occupy(newborn);
    has_bred_current_round = true;
    metrics.SetNewborn(newborn);
}

void Insect::Move() {
    std::shared_ptr<Cell> free_cell = WhereCanIMove();
    if (free_cell == nullptr) {
        return;
    }
    cell->Free();
    free_cell->Occupy(GetThisPtr());
    cell = free_cell;
}

void Insect::Eat() {
    std::shared_ptr<Cell> free_cell = WhereCanIEat();
    if (free_cell == nullptr) {
        return;
    }
    // TODO: implement.
}

bool Insect::CanBreed() {
    if (has_bred_current_round) {
        // Has already spent its breeding quota this round.
        return false;
    }
    else if (rounds_until_breeding == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool Insect::IsDead() {
    return is_dead == true;
}

void Insect::UpdateBreedingState() {
    if (CanBreed()) {
        return;
    }
    if (has_bred_current_round) {
        rounds_until_breeding = GetRequiredRoundsToBreed();
    }
    else {
        rounds_until_breeding--;
    }
}


std::shared_ptr<Cell> Insect::WhereCanIMove() {
    return cell->GetRandomFreeCell();
}

std::shared_ptr<Cell> Insect::WhereCanIBreed() {
    return cell->GetRandomFreeCell();
}

std::shared_ptr<Cell> Insect::WhereCanIEat() {
    return nullptr;
}

}  // namespace simulation
}  // namespace ekumen
