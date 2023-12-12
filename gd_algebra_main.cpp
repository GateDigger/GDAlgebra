#include <iostream>
#include <random>
#include <chrono>

#include "gd_poly/univariate_polynomial.hpp"
#include "gd_poly/test_templates.hpp"

#pragma region PERFTEST

using LLP = gda::uvp<long long, int>;

std::default_random_engine gen(103);
std::uniform_real_distribution<double> urd(0.0, 2.0);
std::uniform_int_distribution<int> uid(0, 4);

auto rcg()
{
	return static_cast<long long>(uid(gen));
}
auto make_rcg()
{
	return rcg;
}

void mul_perftest_loop(int left_len, int right_len, int loop_count)
{
	auto _rcg = make_rcg();

	long long clock;
	int current_count;

	while (true)
	{
		current_count = loop_count;
		clock = 0ULL;
		while (current_count)
		{
			LLP left = LLP::make_random(left_len, rcg),
				right = LLP::make_random(right_len, rcg);

			auto start_1 = std::chrono::high_resolution_clock::now();

			LLP mul = left * right;

			auto stop_1 = std::chrono::high_resolution_clock::now();

			clock += std::chrono::duration_cast<std::chrono::milliseconds>(stop_1 - start_1).count();

			std::cout << "dummy result : " << mul.sum_coefs() << std::endl;

			--current_count;

			//std::cin.ignore();
		}
		std::cout << "elapsed ms   : " << clock << std::endl;
		std::cin.ignore();
	}
}

void kara3_perftest_loop(int left_len, int right_len, int loop_count)
{
	auto _rcg = make_rcg();

	long long clock;
	int current_count;

	while (true)
	{
		current_count = loop_count;
		clock = 0ULL;
		while (current_count)
		{
			LLP left = LLP::make_random(left_len, rcg),
				right = LLP::make_random(right_len, rcg);

			auto start_1 = std::chrono::high_resolution_clock::now();

			LLP mul = gda::karatsuba(left, right);

			auto stop_1 = std::chrono::high_resolution_clock::now();

			clock += std::chrono::duration_cast<std::chrono::milliseconds>(stop_1 - start_1).count();

			std::cout << "dummy result : " << mul.sum_coefs() << std::endl;

			--current_count;

			//std::cin.ignore();
		}
		std::cout << "elapsed ms   : " << clock << std::endl;
		std::cin.ignore();
	}
}

#pragma endregion

void unit_test_battery()
{
	//gda_uvp_ctor_unit_test<int, double, int>();
	gda_uvp_assignment_unit_test<int, double, int>();
}

int main()
{
	LLP one = 1;
	LLP left = (one << 5) + (one << 2) + (one << 1) + 5LL;
	LLP right = (one << 17) + (one << 14) + (one << 10) + (one << 9) + (one << 4) + (one << 3) + 5LL;

	left = left * left * left * left * left;
	right = right * right * right * right * right;

	std::cout << left << std::endl;
	std::cout << right << std::endl;
}