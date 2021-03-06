#include <iostream>
#include "insect.h"
#include "doodlebug.h"

namespace ekumen {
namespace simulation {
namespace {
    constexpr int kRequiredRoundsUntilBreed = 7;
    constexpr int kRequiredRoundsUntilStarvation = 3;
}  // namespace

Doodlebug::Doodlebug() {
    metrics.SetInsectType(Doodlebug::GetInsectType());
    rounds_until_breeding = GetRequiredRoundsToBreed();
    rounds_until_starved = GetRequiredRoundsUntilStarvation();
}

InsectType Doodlebug::GetInsectType() {
    return InsectType::Doodlebug;
}

void Doodlebug::RunRound() {
    if (IsDead()) {
        metrics.SetDead();
    }
    else {
        has_bred_current_round = false;
        if (Eat()){
            // This means the Doodlebug found an Ant to eat.
            rounds_until_starved = GetRequiredRoundsUntilStarvation();
        } else {
            rounds_until_starved--;
        }
        Breed();
        Move();
        // If the Doodlebug wasn't able to breed before moving, it should
        // check if it can after moving.
        // This boosts the overall survival rate of the Doodlebugs.
        Breed();
        UpdateBreedingState();
    }
    if (Starved()) {
        Die();
    }
    if(round_finished_callback) {
        round_finished_callback(metrics);
    }
}

uint32_t Doodlebug::GetRequiredRoundsToBreed() {
    return kRequiredRoundsUntilBreed;
}

uint32_t Doodlebug::GetRequiredRoundsUntilStarvation() {
    return kRequiredRoundsUntilStarvation;
}

std::shared_ptr<Insect> Doodlebug::GetNewborn(const std::shared_ptr<Cell>& cell) {
    auto newborn = std::make_shared<Doodlebug>();
    newborn->SetCell(cell);
    return newborn;
}

std::shared_ptr<Cell> Doodlebug::WhereCanIEat() {
    auto ocuppied_cells = cell->GetSurroundingCells().GetOccupiedCells();
    for (const std::shared_ptr<Cell>& cell : ocuppied_cells) {
        if (cell->GetInsect()->GetInsectType() == InsectType::Ant) {
            return cell;
        }
    }
    return nullptr;
}

std::shared_ptr<Insect> Doodlebug::GetThisPtr() {
    return shared_from_this();
}

bool Doodlebug::Starved() {
    return !rounds_until_starved;
}
}  // namespace simulation
}  // namespace ekumen
