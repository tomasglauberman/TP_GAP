#ifndef GRASP_H
#define GRASP_H

#include <chrono>

#include "gap_instance.h"
#include "gap_solution.h"
#include "genAlg.h"
#include "lsSwap.h"
#include "lsRelocate.h"
#include "vnd.h"


GapSolution graspGen(GapInstance instance, int starts);


#endif