#include "perf_test_api.h"
#include "perf_test_api_unix.cpp"
#include "perf_test_api_win.cpp"
#include <bits/stdc++.h>
#include <chrono>
#include <stdio.h>

static bool fileExists(const char* path)
{
	std::ifstream dummyFile(path);
	if (dummyFile.is_open())
		return true;
	return false;
}

frma::Perf::Perf()
{
	if (!fileExists(filePath))
		createDirectory("../reports");
	file.open(filePath, std::ios_base::app);
}

void frma::Perf::serialize()
{
	unsigned long long perfSum = 0;

	file << "<head><link rel=\"stylesheet\" "
			"type=\"text/css\"href=\"../src/perf_test_api.css\" /></head>\n";
	file << "<body>\n";

	file << "<table>\n";
	file << "<tr>\n";

	for (int i = 0; i < measurements.size(); ++i)
		file << "<td class=\"name\"><b>" << measurements[i].first.data() << "</b></td\n>\n";
	file << "<td class=\"name\"><b>Total time</b></td>\n";

	file << "</tr>\n";
	file << "<tr>\n";

	for (int i = 0; i < measurements.size(); ++i) {
		file << "<td class=\"data\"><b>" << measurements[i].second << "ms</b></td>\n",
			perfSum += measurements[i].second;
	}
	file << "<td class=\"data\"><b>" << perfSum << "ms</b></td>\n";

	file << "</tr>\n";
	file << "</table>\n";

	std::time_t currentChronoTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	char* currentDateTime = std::ctime(&currentChronoTime);
	file << "<h3>" << currentDateTime << "</h3>\n";
}

void frma::Perf::deleteReport()
{
	if (fileExists(filePath))
		std::remove(filePath);
}

frma::Perf& frma::Perf::getInstance()
{
	static Perf instance;
	return instance;
}

frma::Perf::~Perf() { serialize(); }
