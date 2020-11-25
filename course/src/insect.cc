#include <iostream>
#include <functional>
#include <memory>

#include "cell_mock.h"
#include "insect.h"
#include "insects_metrics.h"

namespace ekumen {
namespace simulation {

void Insect::SetCell(const std::shared_ptr<Cell>& cell) {
    if (!cell) {
        throw std::invalid_argument("Null pointer passed to SetCell().");
    }
    // This method only should be called once upon construction.
    if (this->cell) {
        throw std::invalid_argument("Cell already set up before calling SetCell().");
    }
    this->cell = cell;
    cell->Occupy(GetThisPtr());
}

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
    if (!free_cell) {
        return;
    }
    std::shared_ptr<Insect> newborn = GetNewborn(free_cell);
    free_cell->Occupy(newborn);
    has_bred_current_round = true;
    metrics.SetNewborn(newborn);
}

void Insect::Move() {
    std::shared_ptr<Cell> free_cell = WhereCanIMove();
    if (!free_cell) {
        return;
    }
    free_cell->Occupy(cell->GetInsect());
    cell->Free();
    cell = free_cell;
}

void Insect::Eat() {
    std::shared_ptr<Cell> free_cell = WhereCanIEat();
    if (!free_cell) {
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
    return is_dead;
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

std::shared_ptr<Cell> Insect::GetCell() {
    return cell;
}


}  // namespace simulation
}  // namespace ekumen
