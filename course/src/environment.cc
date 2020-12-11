#include <algorithm>
#include <functional>
#include <iostream>
#include <ctime>

#include "environment.h"
#include "cellmap.h"
#include "ant.h"
#include "doodlebug.h"

namespace ekumen {
namespace simulation {
namespace {
    constexpr int kInitialDefaultDoodlebugs = 5;
    constexpr int kInitialDefaultAnts = 100;
    constexpr int kDefaultCols = 20;
    constexpr int kDefaultRows = 20;
}  // namespace

using insect_ptr = std::shared_ptr<Insect>;
using cell_ptr = std::shared_ptr<Cell>;

int GetRandomIntFromZeroTo(int max_limit) {
    return (rand() % max_limit);
}

void RoundResultsCallback(InsectCallbackMetrics& metrics,
                          InsectsRoundMetrics& ant_metrics,
                          InsectsRoundMetrics& doodlebug_metrics,
                          std::vector<insect_ptr> newborns) {
    // First we check which insect type is calling this funciton.
    InsectsRoundMetrics* env_metrics;
    if (metrics.GetInsectType() == InsectType::Ant) {
        env_metrics = &ant_metrics;
    }
    else if (metrics.GetInsectType() == InsectType::Doodlebug) {
        env_metrics = &doodlebug_metrics;
    } else {
        throw  std::runtime_error("Uninitialized metrics.");
    }

    if (metrics.IsDead()) {
        env_metrics->AddDead();
    }
    if (metrics.HasBred()) {
        env_metrics->AddNewborn();
        newborns.push_back(metrics.GetNewborn());
    }
}

Environment::Environment(int rows = kDefaultRows, int cols = kDefaultCols,
                         int ants = kInitialDefaultAnts,
                         int doodlebugs = kInitialDefaultDoodlebugs) {
    if (rows * cols < ants + doodlebugs) {
        throw std::invalid_argument("There are more insects than cells.");
    }
    cell_map = CellMap(rows, cols);
    // TODO: This way of assigning is not so good.
    // If we assign n bugs to n cells, the time until
    // we randomly get every cellmap index is going to take eternity approximately.
    srand((unsigned) time(0));
    for (int i = 0; i < ants; i++) {
        int randomCol = GetRandomIntFromZeroTo(cols);
        int randomRow = GetRandomIntFromZeroTo(rows);
        cell_ptr cell = cell_map.GetCell(randomRow, randomCol);
        while (!cell->IsFree()) {
            randomCol = GetRandomIntFromZeroTo(cols);
            randomRow = GetRandomIntFromZeroTo(rows);
            cell = cell_map.GetCell(randomRow, randomCol);
        }
        insect_ptr new_ant(new Ant());
        new_ant->SetCell(cell);
        insects.push_back(new_ant);
    }
    for (int i = 0; i < doodlebugs; i++) {
        int randomCol = GetRandomIntFromZeroTo(cols);
        int randomRow = GetRandomIntFromZeroTo(rows);
        cell_ptr cell = cell_map.GetCell(randomRow, randomCol);
        while (!cell->IsFree()) {
            randomCol = GetRandomIntFromZeroTo(cols);
            randomRow = GetRandomIntFromZeroTo(rows);
            cell = cell_map.GetCell(randomRow, randomCol);
        }
        insect_ptr new_doodlebug(new Doodlebug());
        new_doodlebug->SetCell(cell);
        insects.push_back(new_doodlebug);
    }
}

std::vector<InsectsRoundMetrics> Environment::RunRound() {
    RandomizeInsectsOrder();

    std::vector<insect_ptr> newborns;
    InsectsRoundMetrics ant_metrics;
    ant_metrics.SetInsectType(InsectType::Ant);
    InsectsRoundMetrics doodlebug_metrics;
    doodlebug_metrics.SetInsectType(InsectType::Doodlebug);
    for (const insect_ptr& insect : insects) {
        insect->SetRoundResultsCallback(std::bind(RoundResultsCallback,
                                                  std::placeholders::_1,
                                                  ant_metrics,
                                                  doodlebug_metrics,
                                                  newborns));
    }
    for (const insect_ptr& insect : insects) {
        insect->RunRound();
    }
    // Delete the dead insects from the list.
    insects.erase(std::remove_if(insects.begin(), insects.end(),
                                 [](insect_ptr& insect){
                                     return insect->IsDead();
                                    }),
                                 insects.end());
    // After simulating the original insects we add the newborns to the list.
    for (const insect_ptr& insect : newborns) {
        insects.push_back(insect);
    }

    std::vector<InsectsRoundMetrics> metrics;
    metrics.push_back(ant_metrics);
    metrics.push_back(doodlebug_metrics);
    return metrics;
}

bool Environment::SimulationFinished() {
    // In order to finish, one of the insects must be completely eliminated
    // from the simulation.
    if (!insects.size()) {
        return true;
    }
    InsectType type = insects[0]->GetInsectType();
    for (const insect_ptr& insect : insects) {
        if (type != insect->GetInsectType()) {
            return false;
        }
    }
    return true;
}

void Environment::RandomizeInsectsOrder() {
    std::random_shuffle(insects.begin(), insects.end());
}
}  // namespace simulation
}  // namespace ekumen
