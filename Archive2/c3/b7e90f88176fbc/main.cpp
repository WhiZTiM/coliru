#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/random.hpp>
#include <chrono>
#include <iostream>
#include <omp.h>
#include <random>

static std::mt19937 prng { std::random_device{}() };

struct MyVertex {
    uintmax_t volume = [] { static std::uniform_int_distribution<int> pick(0, 1024); return pick(prng); }();
};

using namespace boost;
using G = adjacency_list<vecS, vecS, directedS, MyVertex>;

G generate() {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    G g;
    generate_random_graph(g, 5000/*0000 scaled down for coliru*/, 0, prng);

    auto end = high_resolution_clock::now();
    std::cerr << "Generated " << num_vertices(g) << " vertices " << "in " << duration_cast<milliseconds>(end-start).count() << "ms\n";

    return g;
}

int main() {

    auto const g = generate();

    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    double sum = 0;
#pragma omp parallel
    {
#pragma omp single
        std::cerr << "Using " << omp_get_num_threads() << " threads.\n";

#pragma omp for reduction(+:sum)
        for (G::vertex_descriptor u = 0; u < num_vertices(g); ++u) {
            sum += g[vertex(u, g)].volume;
        }
    }

    auto end = high_resolution_clock::now();
    std::cerr << "Sum of volumes for " << num_vertices(g)                                << " vertices "
              << "in "                 << duration_cast<milliseconds>(end-start).count() << "ms: " << sum << "\n";
}
