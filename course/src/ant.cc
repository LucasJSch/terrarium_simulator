#include <iostream>
#include "insect.h"
#include "ant.h"

namespace ekumen {
namespace simulation {
namespace {
    constexpr int kRequiredRoundsUntilBreed = 2;
}

Ant::Ant(const std::shared_ptr<Cell>& cell) {
    if (!cell) {
        throw std::invalid_argument("Null pointer passed to Ant constructor.");
    }
    this->cell = cell;
    cell->Occupy(GetThisPtr());
    metrics.SetInsectType(Ant::GetInsectType());
    rounds_until_breeding = GetRequiredRoundsToBreed();
}

InsectType Ant::GetInsectType() {
    return InsectType::Ant;
}

void Ant::RunRound() {
    if (IsDead()) {
        std::cout << "ant is dead !!! \n";
        metrics.SetDead();
        // If the ant died we don't want to execute the callback again.
        // The callback was executed when called Die().
        return;
    }
    else {
        std::cout << "ant is not dead !!! \n";
        has_bred_current_round = false;
        Breed();
        Move();
        // If the ant wasn't able to breed before moving, it should
        // check if it can after moving.
        // This boosts the overall survival rate of the ants.
        Breed();
        UpdateBreedingState();
    }
    if (round_finished_callback) {
        std::cout << "running metrics !!! \n";
        round_finished_callback(metrics);
    }
}

uint32_t Ant::GetRequiredRoundsToBreed() {
    return kRequiredRoundsUntilBreed;
}

std::shared_ptr<Insect> Ant::GetNewborn(const std::shared_ptr<Cell>& cell) {
    return std::make_shared<Ant>(cell);
}

std::shared_ptr<Cell> Ant::WhereCanIEat() {
    // Ants don't eat.
    return nullptr;
}

std::shared_ptr<Insect> Ant::GetThisPtr() {
    auto aux = std::make_shared<Ant>(*this);
    std::cout << "aux: " << aux.get() << "\n";
    return aux;
}
}  // namespace simulation
}  // namespace ekumen
