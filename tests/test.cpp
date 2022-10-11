#include "perf_test_api.h"
#include <thread>
#include <iostream>

class Test {
public:
	int a;
	void foo(int c)
	{
		a = c;
	}
	static void bar(){
		
	}
};

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
		perf.profile("func1", func1, 1);
	perf.profile("func2", func2);
	Test t;
	perf.profile("foo", &Test::foo, &t, 5);
	perf.profile("bar", &Test::bar);
	if (t.a != 5)
		std::cout<<"Test failed\n";
	else
		std::cout<<"Test succeeded\n";
	return 0;
}
