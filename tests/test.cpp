#include "perf_test_api.h"
#include <thread>

int func1(int dummy)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(12));
	return 0;
}

void func2()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(43));
}

int main()
{
	frma::Perf& perf = frma::Perf::getInstance();
	for (int i = 0; i < 10; ++i)
		perf.profile("func1", &func1, 1, 2, 3, 4, 5);
	perf.profile("func2", &func2);
}
