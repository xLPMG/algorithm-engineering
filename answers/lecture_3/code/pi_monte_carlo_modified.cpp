#include <iostream>
#include <omp.h>
#include <random>

using namespace std;

double rnd (unsigned int *seed) {
  *seed = (1140671485 * (*seed) + 12820163) % (1 << 24);
  return ((double)(*seed)) / (1 << 24);
}

int main() {
  int n = 100000000; // number of points to generate
  double counter = 0.0; // counter for points lying in the first quadrant of a unit circle
  auto start_time = omp_get_wtime(); // omp_get_wtime() is an OpenMP library routine

  // compute n points and test if they lie within the first quadrant of a unit circle
#pragma omp parallel
  {
    // seed based on thread id for more randomness
    unsigned int seed = omp_get_thread_num();

    #pragma omp for reduction(+:counter)
    for (int i = 0; i < n; ++i) {
      auto x = rnd(&seed); // generate random number between 0.0 and 1.0
      auto y = rnd(&seed); // generate random number between 0.0 and 1.0
      if (x * x + y * y <= 1.0) { // if the point lies in the first quadrant of a unit circle
        ++counter;
      }
    }
  } // parallel region ends here

  auto run_time = omp_get_wtime() - start_time;
  auto pi = 4 * (counter / n);

  cout << "Modified Monte Carlo Simulation" << endl;
  cout << "pi: " << pi << endl;
  cout << "run_time: " << run_time << " s" << endl;
  cout << "n: " << n << endl;
}
