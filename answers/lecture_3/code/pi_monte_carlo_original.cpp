#include <iostream>
#include <omp.h>
#include <random>

using namespace std;

int main() {
  int n = 100000000; // number of points to generate
  double counter = 0.0; // counter for points lying in the first quadrant of a unit circle
  auto start_time = omp_get_wtime(); // omp_get_wtime() is an OpenMP library routine

  // compute n points and test if they lie within the first quadrant of a unit circle
#pragma omp parallel
  {
    int num_threads = omp_get_num_threads();
    int thread_id = omp_get_thread_num();

    // each thread should have its own random number generator
    // seed based on thread id for more randomness
    unsigned int seed = thread_id;
    default_random_engine re{seed};
    uniform_real_distribution<double> zero_to_one{0.0, 1.0};

    // Calculate number of points for each thread
    int base_points_per_thread = n / num_threads;
    int remainder_points = n % num_threads;
    // the first #remainder_points threads process one extra point
    int num_points_per_thread = base_points_per_thread + (thread_id < remainder_points ? 1 : 0);

    double counter_local = 0.0;
    for (int i = 0; i < num_points_per_thread; ++i) {
      auto x = zero_to_one(re); // generate random number between 0.0 and 1.0
      auto y = zero_to_one(re); // generate random number between 0.0 and 1.0
      if (x * x + y * y <= 1.0) { // if the point lies in the first quadrant of a unit circle
        ++counter_local;
      }
    }

#pragma omp atomic
    counter += counter_local;
  } // parallel region ends here

  auto run_time = omp_get_wtime() - start_time;
  auto pi = 4 * (counter / n);

  cout << "Original Monte Carlo Simulation" << endl;
  cout << "pi: " << pi << endl;
  cout << "run_time: " << run_time << " s" << endl;
  cout << "n: " << n << endl;
}
