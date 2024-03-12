#include "benchmark.h"

#include "encryption/Key.h"

#include <iostream>

static void benchmark_three_d_one_fabian_ist_voll_knorke(benchmark::State& state) {
	const auto number_threads = state.range(0);

	const auto& keys = Holder::get_keys();

	for (auto _ : state) {
		const auto val = Key::get_smallest_hash_parallel(keys, number_threads);
		benchmark::DoNotOptimize(val);
	}

	const auto serial_answer = std::uint64_t{ 1'169'893'733'064ULL };
	const auto parallel_answer = Key::get_smallest_hash_parallel(keys, number_threads);

	if (serial_answer != parallel_answer) {
		std::cerr << "Serial and parallel answers don't match!\n";
	}
}

static void benchmark_three_f_one_fabian_ist_voll_knorke(benchmark::State& state) {
	const auto number_threads = state.range(0);

	const auto& keys = Holder::get_keys();

	const auto hash_to_find = std::uint64_t{ 30'403'176'973'399'313ULL };

	for (auto _ : state) {
		const auto val = Key::find_key_parallel(keys, hash_to_find, number_threads);
		benchmark::DoNotOptimize(val);
	}

	const auto parallel_answer = Key::find_key_parallel(keys, hash_to_find, number_threads);
	const auto hashed = Key::hash(parallel_answer);

	if (hashed != hash_to_find) {
		std::cerr << "Serial and parallel answers don't match!\n";
	}
}

BENCHMARK(benchmark_three_d_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(1);
BENCHMARK(benchmark_three_d_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(2);
BENCHMARK(benchmark_three_d_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(4);

BENCHMARK(benchmark_three_f_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(1);
BENCHMARK(benchmark_three_f_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(2);
BENCHMARK(benchmark_three_f_one_fabian_ist_voll_knorke)->Unit(benchmark::kMillisecond)->Arg(4);
