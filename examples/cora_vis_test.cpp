//
// Created by tim on 11/13/23.
//
#include <CORA/CORA.h>

#ifdef ENABLE_VISUALIZATION
#include <CORA/CORA_vis.h>
#endif

#include <thread> // NOLINT [build/c++11]

#ifdef GPERFTOOLS
#include <gperftools/profiler.h>
#endif

int main() {
  CORA::Problem problem =
      CORA::parsePyfgTextToProblem("./bin/data/plaza2.pyfg");
  problem.updateProblemData();

  CORA::Matrix x0 = problem.getRandomInitialGuess();

  int max_rank = 10;
  bool verbose = false;
  bool log_iterates = true;
  CORA::CoraResult res;
  #ifdef GPERFTOOLS
    ProfilerStart("cora_plaza2_arm.prof");
  #endif
  res = solveCORA(problem, x0, max_rank, verbose, log_iterates);

  #ifdef GPERFTOOLS
    ProfilerStop();
  #endif

  std::cout << "Testing with Random initialization" << std::endl;

#ifdef ENABLE_VISUALIZATION
  // Visualize the result
  CORA::CORAVis viz{};
  double viz_hz = 10.0;
  // double viz_hz = 2.0;
  viz.run(problem, {res.second}, viz_hz, true);
#endif

  return 0;
}
