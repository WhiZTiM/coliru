
#include <bitset>
#include <vector>

#include <algorithm>
#include <functional>
#include <numeric>
#include <climits>

#include <iostream>
#include <cstdlib>
#include <chrono>

uint64_t get_true_bits_count(uint32_t number)
{
    std::bitset<CHAR_BIT * sizeof(number)> bset(number);
    return bset.count();
}

uint64_t accumulate_true_bits_count(uint64_t acc, uint32_t number)
{
    return acc + get_true_bits_count(number);
}

uint64_t hamming_weight_bits_count(uint32_t i)
{
    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

uint64_t accumulate_true_bits_count2(uint64_t acc, uint32_t number)
{
    return acc + hamming_weight_bits_count(number);
}

uint64_t handmade_bits_count(uint32_t number)
{
    uint64_t count = 0;
    enum { BITS_IN_CELL = sizeof(uint32_t)*8 };
    for(int i = 0; i < BITS_IN_CELL; i++) {
        if (number & (1 >> i))
            count++;
    }
    return count;
}

uint64_t accumulate_true_bits_count3(uint64_t acc, uint32_t number)
{
    return acc + handmade_bits_count(number);
}

void burn_cpu(const std::vector<uint32_t>& vec) {
    uint32_t xored_value = 0xDEADBEAF;
    for (int i = 0; i < 4; i++) {
        auto first = vec.begin();
        auto last = vec.end();
        for (; first != last; ++first)
            xored_value = xored_value ^ *first;
    }
    printf("xored_value: %u \n", xored_value);
}

typedef uint64_t(*acc_func_t)(uint64_t, uint32_t);

struct test_result
{
    uint64_t bits_count;
    uint64_t time;
};

test_result test_accumulator(const std::vector<uint32_t>& input_vec, acc_func_t f, uint32_t rounds) {
    uint64_t time_total = 0;
    uint64_t bits_count = 0;
    for (uint32_t i = 0; i < rounds; i++) {
        auto start = std::chrono::high_resolution_clock::now();

        bits_count = std::accumulate(input_vec.begin(), input_vec.end(), 0, f);

        auto end = std::chrono::high_resolution_clock::now();
        time_total += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }
    return {bits_count, time_total/rounds};
}

test_result test_cycle(const std::vector<uint32_t>& input_vec, acc_func_t f, uint32_t rounds) {
    uint64_t time_total = 0;
    uint64_t bits_count = 0;
    for (uint32_t i = 0; i < rounds; i++) {
        auto start = std::chrono::high_resolution_clock::now();

        uint64_t local_bits_count = 0;
        auto size = input_vec.size();
        for (std::size_t i = 0; i < size; i++)
            local_bits_count = f(local_bits_count, input_vec[i]);
        bits_count = local_bits_count;

        auto end = std::chrono::high_resolution_clock::now();
        time_total += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }
    return {bits_count, time_total/rounds};
}

int main()
{
    std::srand(0);
    std::vector<uint32_t> input_vec;
    const uint32_t test_rounds = 15;
    input_vec.resize(5000000);
    std::generate(input_vec.begin(), input_vec.end(), std::rand);

    burn_cpu(input_vec);
    test_result r;

    r = test_accumulator(input_vec, accumulate_true_bits_count, test_rounds);
    printf("accum1 bits_count: %lu, took: %lu\n", r.bits_count, r.time);
    r = test_cycle(input_vec, accumulate_true_bits_count, test_rounds);
    printf("cycle1 bits_count: %lu, took: %lu\n", r.bits_count, r.time);

    r = test_accumulator(input_vec, accumulate_true_bits_count2, test_rounds);
    printf("accum2 bits_count: %lu, took: %lu\n", r.bits_count, r.time);
    r = test_cycle(input_vec, accumulate_true_bits_count2, test_rounds);
    printf("cycle2 bits_count: %lu, took: %lu\n", r.bits_count, r.time);

    r = test_accumulator(input_vec, accumulate_true_bits_count3, test_rounds);
    printf("accum3 bits_count: %lu, took: %lu\n", r.bits_count, r.time);
    r = test_cycle(input_vec, accumulate_true_bits_count3, test_rounds);
    printf("cycle3 bits_count: %lu, took: %lu\n", r.bits_count, r.time);
    return 0;
}
