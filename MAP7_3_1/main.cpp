#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <future>

using namespace std::chrono_literals;

void findMin(int begin, std::vector<int>& v, std::promise<int> prom);
void choiceSort(std::vector<int>& v);
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
	choiceSort(v);
	printVector(v);
}

void findMin(int begin, std::vector<int>& v, std::promise<int> prom)
{
	int Imin = begin;
	for (int j = begin; j < v.size(); ++j)
	{
		if (v.at(j) < v.at(Imin))
		{
			Imin = j;
		}
	}
	prom.set_value(Imin);
}

void choiceSort(std::vector<int>& v)
{
	int temp;
	int Itemp;
	for (int i = 0; i < v.size(); ++i)
	{
		std::promise<int> prom;
		std::future<int> ftRest = prom.get_future();
		std::future<void> ft = std::async(std::launch::async, findMin, i, std::ref(v), std::move(prom));
		ft.wait();
		Itemp = ftRest.get();
		temp = v.at(Itemp);
		v.at(Itemp) = v.at(i);
		v.at(i) = temp;
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
