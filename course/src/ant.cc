#include "insect.h"
#include "ant.h"

namespace ekumen {
namespace simulation {

Ant::Ant() {
    metrics.SetInsectType(Ant::GetInsectType());
    rounds_until_breeding = GetRequiredRoundsToBreed();
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
    if(round_finished_callback) {
        round_finished_callback(metrics);
    }
}

uint32_t Ant::GetRequiredRoundsToBreed() {
    return kRequiredRoundsUntilBreed;
}

std::shared_ptr<Insect> Ant::GetNewborn(const std::shared_ptr<Cell>& cell) {
    auto newborn = std::make_shared<Ant>();
    newborn->SetCell(cell);
    return newborn;
}

std::shared_ptr<Cell> Ant::WhereCanIEat() {
    return nullptr;
}

std::shared_ptr<Insect> Ant::GetThisPtr() {
    return shared_from_this();
}
}  // namespace simulation
}  // namespace ekumen
