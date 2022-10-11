#pragma once
#include <chrono>
#include <fstream>
#include <mutex>
#include <string>
#include <type_traits>
#include <vector>

namespace frma {

class Perf {
public:
	static Perf& getInstance();

	void deleteReport();

	template <typename T>
	using enableIfMethod = typename std::enable_if<std::is_member_function_pointer<T>::value, bool>::type;

	template <typename T>
	using enableIfNotMethod = typename std::enable_if<!std::is_member_function_pointer<T>::value, bool>::type;

	template <typename Function, enableIfNotMethod<Function> = true, typename... Args>
	unsigned long long profile(std::string funcName, Function&& func, Args... args)
	{
		auto start = std::chrono::high_resolution_clock::now();
		func(args...);
		auto end = std::chrono::high_resolution_clock::now();

		unsigned long long runTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
										 .count();
		m.lock();
		measurements.emplace_back(
			std::pair<std::string, unsigned long long>(funcName, runTime));
		m.unlock();
		return runTime;
	}

	template <typename Function, enableIfMethod<Function> = true, typename Class, typename... Args>
	unsigned long long profile(std::string funcName,
		Function&& func, Class objPointer, Args... args)
	{
		auto start = std::chrono::high_resolution_clock::now();
		(objPointer->*func)(args...);
		auto end = std::chrono::high_resolution_clock::now();

		unsigned long long runTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
										 .count();
		m.lock();
		measurements.emplace_back(
			std::pair<std::string, unsigned long long>(funcName, runTime));
		m.unlock();
		return runTime;
	}

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
