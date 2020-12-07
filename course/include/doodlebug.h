#ifndef DOODLEBUG_H
#define DOODLEBUG_H
#include <cstdint>
#include <memory>

#include "insect.h"

namespace ekumen {
namespace simulation {

class Doodlebug : public Insect {
    public:
        explicit Doodlebug();
        void RunRound();

    protected:
        InsectType GetInsectType();
        uint32_t GetRequiredRoundsToBreed();
        uint32_t GetRequiredRoundsUntilStarvation();
        // Creates a shared_ptr to a new instance of an ant.
        // Used by Breed().
        std::shared_ptr<Insect> GetNewborn(const std::shared_ptr<Cell>& cell);
        std::shared_ptr<Cell> WhereCanIEat();
        std::shared_ptr<Insect> GetThisPtr();
        bool Starved();
        int rounds_until_starved;
};
}  // namespace simulation
}  // namespace ekumen
#endif
