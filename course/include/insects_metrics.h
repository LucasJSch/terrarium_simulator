#ifndef INSECTS_METRICS_H
#define	INSECTS_METRICS_H
#include <cstdint>
#include <memory>

#include "insect.h"

namespace ekumen {
namespace simulation {

class Insect;
enum class InsectType {Ant, Doodlebug};

// Class that contains different metrics of a certain insect type.
// The metrics are only per round.
// This class will be used by the simulation runner to log the round statistics.
class InsectsRoundMetrics {
    public:
        void AddDead() {n_dead++;}
        void AddNewborn() {n_newborns++;}
        uint32_t GetDeadCount() const {return n_dead;}
        uint32_t GetNewbornCount() const {return n_newborns;}

    private:
        uint32_t n_dead{0};
        uint32_t n_newborns{0};
};

// This class will be used as the return type of the callback when an insect
// finishes simulating a round.
class InsectCallbackMetrics {
    public:
        void SetDead() {died = true;}
        void SetNewborn(const std::shared_ptr<Insect>& newborn) {this->newborn = newborn;}
        void SetInsectType(InsectType type) {this->type = type;}
        bool IsDead() const {return died;}
        bool HasBred() const {return newborn != nullptr;}
        InsectType GetInsectType() const {return type;}
        std::shared_ptr<Insect> GetNewborn() const {return newborn;}

    private:
        bool died{false};
        std::shared_ptr<Insect> newborn = nullptr;
        InsectType type;
};
}  // namespace simulation
}  // namespace ekumen
#endif