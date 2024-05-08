//
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution> // for parallel execution policies
#include <chrono>

int main() {
    const size_t N = 1000000; // Taulukon koko
    std::vector<int> numbers(N);

    // Alusta taulukko arvoilla 0...(N-1)
    for (size_t i = 0; i < N; ++i) {
        numbers[i] = i;
    }

    // Käy läpi taulukko ja kasvata jokaisen alkion arvoa yhdellä
    auto startTime = std::chrono::steady_clock::now();
    // Sequential execution
    std::for_each(std::execution::seq, numbers.begin(), numbers.end(), [](int& x) {
        ++x;
    });
    auto endTime = std::chrono::steady_clock::now();
    auto seqTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "Sequential execution time: " << seqTime << " ms" << std::endl;

    // Parallel execution
    startTime = std::chrono::steady_clock::now();
    std::for_each(std::execution::par, numbers.begin(), numbers.end(), [](int& x) {
        ++x;
    });
    endTime = std::chrono::steady_clock::now();
    auto parTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "Parallel execution time: " << parTime << " ms" << std::endl;

    // Unsequenced (vectorized) execution
    startTime = std::chrono::steady_clock::now();
    std::for_each(std::execution::par_unseq, numbers.begin(), numbers.end(), [](int& x) {
        ++x;
    });
    endTime = std::chrono::steady_clock::now();
    auto parUnseqTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "Unsequenced (vectorized) execution time: " << parUnseqTime << " ms" << std::endl;

    return 0;
}
