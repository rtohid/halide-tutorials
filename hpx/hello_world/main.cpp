#include <hpx/hpx_main.hpp>
#include <hpx/iostream.hpp>

#include <hpx/include/parallel_for_loop.hpp>
#include <hpx/runtime.hpp>

int main() {
  // Say hello to the world!
  std::vector<double> vec(16000000, 0);
  hpx::chrono::high_resolution_timer t;
  hpx::for_loop(hpx::execution::par, 0, vec.size(),
                [&](int i) { vec[i] += i; });
  std::cout << "ELAPSED: " << t.elapsed() << std::endl;

  return 0;
}
