#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <future>

template<typename It>
void findMin(It begin, It end, std::promise<It> prom);
template<typename It>
void choiceSort(It begin, It end);
void printVector(std::vector<int>& v);

int main()
{
	int N = 10;
	std::vector<int> v;
	for (int i = 0; i < N; ++i)
	{
		v.push_back(std::rand() % 100);
	}
	printVector(v);
	choiceSort(v.begin(), v.end());
	printVector(v);
}

template<typename It>
void findMin(It begin, It end, std::promise<It> prom)
{
	It Itmin = begin;
	for (It j = begin; j < end; ++j)
	{
		if (*j < *Itmin)
		{
			Itmin = j;
		}
	}
	prom.set_value(Itmin);
}

template <typename It>
void choiceSort(It begin, It end)
{
	int temp;
		std::promise<It> prom;
		std::future<It> ftRest = prom.get_future();
	for (It i = begin; i < end; ++i)
	{
		std::future<void> ft = std::async(findMin<It>, i, end, std::move(prom));
		ft.wait();
		temp = *i;
		*i = *ftRest.get();
		std::cout << *ftRest.get();
		*ftRest.get() = temp;
	}
}

void printVector(std::vector<int>& v)
{
	std::cout << "Vector: { ";
	for (const auto& el : v)
	{
		std::cout << el << " ";
	}
	std::cout << "};" << std::endl;
}
