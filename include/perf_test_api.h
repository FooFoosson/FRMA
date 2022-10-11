#pragma once
#include <chrono>
#include <fstream>
#include <mutex>
#include <string>
#include <vector>

#define profile(funcName, funcPointer, ...)                                    \
	measureFunc(                                                               \
		funcName,                                                              \
		(void (*)(void))                                                       \
			funcPointer /* dummy parameter i.e. trailing comma handler, this   \
						   works due to the way C++ does name lookup,          \
						   aggressively matching names in the current scope */ \
		,                                                                      \
		0)

namespace frma {

class Perf {
public:
	static Perf& getInstance();
	template <typename... Args>
	unsigned long long measureFunc(std::string funcName, void (*func)(void),
		Args... args);
	void deleteReport();
	~Perf();
	Perf(Perf&) = delete;
	Perf(Perf&&) = delete;
	Perf& operator=(const Perf&) = delete;
	Perf& operator=(Perf&&) = delete;

private:
	Perf();
	void serialize();
	std::vector<std::pair<std::string, unsigned long long>> measurements;
	std::ofstream file;
	const char* filePath = "../reports/perf_report.html";
	std::mutex m;
};

}

template <typename... Args>
unsigned long long frma::Perf::measureFunc(std::string funcName,
	void (*func)(void), Args... args)
{
	void (*trueFunc)(Args...) = (void (*)(Args...))func;

	auto start = std::chrono::high_resolution_clock::now();
	trueFunc(args...);
	auto end = std::chrono::high_resolution_clock::now();

	unsigned long long runTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
									 .count();
	m.lock();
	measurements.emplace_back(
		std::pair<std::string, unsigned long long>(funcName, runTime));
	m.unlock();
	return runTime;
}
