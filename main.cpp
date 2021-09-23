#include "circular_buffer_thread_safe.h"
#include "circular_buffer_list.h"
#include "sort.h"
#include "timer.h"
#include <thread>
#include <vector>
#include <algorithm>
#include <random>

void circular_buffer_test();
void circular_buffer_thread_test();
void circualr_buffer_list_test();
void sort_test();

int main()
{
	circular_buffer_test();
	circular_buffer_thread_test();
	circualr_buffer_list_test();
	sort_test();

	system("pause");
	return 0;
}

template<class T>
void test_buffer(T circle)
{
	printf("Size: %zu, Capacity: %zu\n", circle->size(), circle->capacity());

	int32_t x = 1;
	printf("Put 1, val: %d\n", x);
	circle->put(x);

	x = circle->pop();
	printf("Popped: %d\n", x);

	printf("Empty: %d\n", circle->empty());

	printf("Adding %zu values\n", circle->capacity() - 1);
	for (uint32_t i = 0; i < circle->capacity() - 1; i++)
	{
		circle->put(i);
	}

	circle->reset();

	printf("Full: %d\n", circle->full());

	printf("Adding %zu values\n", circle->capacity());
	for (uint32_t i = 0; i < circle->capacity(); i++)
	{
		circle->put(i);
	}

	printf("Full: %d\n", circle->full());

	printf("Reading back values: ");
	while (!circle->empty())
	{
		printf("%u ", circle->pop());
	}
	printf("\n");

	printf("Adding %zu values\n", circle->capacity() + 5);
	for (uint32_t i = 0; i < circle->capacity() + 5; i++)
	{
		circle->put(i);
	}

	printf("Full: %d\n", circle->full());

	printf("Reading back values: ");
	while (!circle->empty())
	{
		printf("%u ", circle->pop());
	}
	printf("\n");

	printf("Empty: %d\n", circle->empty());
	printf("Full: %d\n", circle->full());
}

void circular_buffer_test()
{
	const size_t size = 10;
	circular_buffer<int32_t> circle(size);

	printf("\n === CPP Circular buffer check ===\n");

	test_buffer<circular_buffer<int32_t>*>(&circle);
}

void circular_buffer_thread_test()
{
	const size_t size = 10;
	circular_buffer<int32_t> circle(size);

	printf("\n === CPP Circular buffer thread check ===\n");

	uint32_t concurrency = std::thread::hardware_concurrency();
	std::vector<std::thread> threads;

	for (uint32_t i = 1; i <= concurrency; i++)
	{
		if (i & 1)
		{
			threads.push_back(std::thread([&circle, i]() { circle.put(i); }));
		}
		else {
			threads.push_back(std::thread([&]() { printf("%u\n", circle.pop()); }));
		}
	}

	for (auto& thr : threads)
		if (thr.joinable())
			thr.join();
}

void circualr_buffer_list_test()
{
	const size_t size = 15;
	circular_buffer_list<int32_t, size> circle_list;

	printf("\n === CPP Circular buffer list check ===\n");

	test_buffer<circular_buffer_list<int32_t, size>*>(&circle_list);
}

void sort_test()
{
	const int size = 1000000;

	{
		std::vector<int> v;
		v.reserve(size);

		for (int i = 0; i < size; ++i)
			v.push_back(i);
		std::shuffle(v.begin(), v.end(), std::default_random_engine());

		printf("-------------------------------------------------\n");
		printf("---------- quick sort ---------------------------\n");
		auto quick_time_start = get_time();

		wg_test_sort::quick_sort(v.data(), 0, static_cast<int>(v.size()) - 1);

		auto quick_time_end = get_time();
		print_difference(quick_time_start, quick_time_end);
	}

	{
		std::vector<int> v;
		v.reserve(size);

		for (int i = 0; i < size; ++i)
			v.push_back(i);
		std::shuffle(v.begin(), v.end(), std::default_random_engine());

		printf("-------------------------------------------------\n");
		printf("---------- quick sort median ---------------------------\n");
		auto quick_time_start = get_time();

		wg_test_sort::better::quick_sort_median(v.data(), 0, static_cast<int>(v.size()) - 1);

		auto quick_time_end = get_time();
		print_difference(quick_time_start, quick_time_end);
	}

	{
		std::vector<int> v;
		v.reserve(size);

		for (int i = 0; i < size; ++i)
			v.push_back(i);
		std::shuffle(v.begin(), v.end(), std::default_random_engine());

		printf("-------------------------------------------------\n");
		printf("---------- heap sort ---------------------------\n");
		auto quick_time_start = get_time();

		wg_test_sort::heap_sort(v.data(), static_cast<int>(v.size()));

		auto quick_time_end = get_time();
		print_difference(quick_time_start, quick_time_end);
	}
}