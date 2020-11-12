#ifndef ANT_H
#define ANT_H
#include <cstdint>
#include <memory>

#include "insect.h"

namespace ekumen {
namespace simulation {
namespace {
    constexpr int kRequiredRoundsUntilBreed = 2;
}  // namespace

class Ant : public Insect {
    public:
        Ant(const std::shared_ptr<Cell>& cell);
        void RunRound();

    protected:
        InsectType GetInsectType();
        uint32_t GetRequiredRoundsToBreed();
        // Creates a shared_ptr to a new instance of an ant.
        // Used by Breed().
        std::shared_ptr<Insect> GetNewborn(const std::shared_ptr<Cell>& cell);
        std::shared_ptr<Cell> WhereCanIEat();
        std::shared_ptr<Insect> GetThisPtr();
};
}  // namespace simulation
}  // namespace ekumen
#endif
