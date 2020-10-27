#include "insect.h"
#include "ant.h"

namespace ekumen {
namespace simulation {

Ant::Ant(std::shared_ptr<Cell>& cell) {
    this->cell = cell;
    cell->Occupy(std::move(GetThisPtr()));
    metrics.SetInsectType(Ant::GetInsectType());
}

InsectType Ant::GetInsectType() {
    return InsectType::Ant;
}

void Ant::RunRound() {
    if (IsDead()) {
        metrics.SetDead();
    }
    else {
        has_bred_current_round = false;
        Breed();
        Move();
        // If the ant wasn't able to breed before moving, it should
        // check if it can after moving.
        // This boosts the overall survival rate of the ants.
        Breed();
        UpdateBreedingState();
    }
    if(round_finished_callback != nullptr) {
        round_finished_callback(metrics);
    }
}

uint32_t Ant::GetRequiredRoundsToBreed() {
    return kRequiredRoundsUntilBreed;
}

std::shared_ptr<Insect> Ant::GetNewborn(std::shared_ptr<Cell>& cell) {
    std::shared_ptr<Ant> newborn(new Ant(cell));
    return std::move(newborn);
}

std::shared_ptr<Cell> Ant::WhereCanIEat() {
    return nullptr;
}

std::shared_ptr<Insect> Ant::GetThisPtr() {
    return std::make_shared<Ant>(*this);
}
}  // namespace simulation
}  // namespace ekumen
