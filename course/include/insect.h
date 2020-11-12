#ifndef INSECT_H
#define	INSECT_H
#include <cstdint>
#include <functional>

#include "cell_mock.h"
#include "insects_metrics.h"

namespace ekumen {
namespace simulation {

class Cell;

// Abstract class that implements the common behaviour of every simulated insect,
// and defines the methods that must be implemented by every insect.
// We need the enable_shared_from_this ineritance to pass the instance's reference when moving
// to a new cell.
class Insect {
    public:
        // Simulates a round.
        virtual void RunRound() = 0;
        void Die();
        void SetRoundResultsCallback(std::function<void(InsectCallbackMetrics&)> callback);
        std::shared_ptr<Cell> GetCell();

    protected:
        // Making these virtual allows to easily change the insect behaviour if
        // needed, or have additional functionalities besides the basic ones.
        virtual void Breed();
        virtual void Move();
        virtual void Eat();
        virtual InsectType GetInsectType() = 0;
        virtual uint32_t GetRequiredRoundsToBreed() = 0;
        bool CanBreed();
        bool IsDead();
        void UpdateBreedingState();
        // Delegates the breeding and moving behaviour to the derived class.
        virtual std::shared_ptr<Cell> WhereCanIMove();
        virtual std::shared_ptr<Cell> WhereCanIBreed();
        virtual std::shared_ptr<Cell> WhereCanIEat();
        virtual std::shared_ptr<Insect> GetNewborn(const std::shared_ptr<Cell>& cell) = 0;
        virtual std::shared_ptr<Insect> GetThisPtr() = 0;

        std::shared_ptr<Cell> cell;
        bool is_dead{false};
        bool has_bred_current_round{false};
        int rounds_until_breeding;
        //std::shared_ptr<InsectCallbackMetrics> metrics;
        InsectCallbackMetrics metrics;
        // Callback when round finishes.
        std::function<void(InsectCallbackMetrics&)> round_finished_callback;
};
}  // namespace simulation
}  // namespace ekumen
#endif
