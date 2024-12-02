#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
std::ifstream fin("input.txt");

typedef std::vector<std::vector<int>> data;

void part1(const data &);

int main()
{
	data input;

	std::string line;
	int x;

	while (std::getline(fin, line)) {
		input.emplace_back();

		std::istringstream stream(line);
		while (stream >> x) {
			input.back().push_back(x);
		}
	}

	part1(input);
	std::cout << "\n";
}

bool increasing(int a, int b) {
	return a < b;
}

void part1(const data &pInput) {
	int count = 0;

	for (const auto &report : pInput) {
		if (report.size() < 2) {
			count++;
			continue;
		}

		bool shouldIncrease = increasing(report.at(0), report.at(1));
		bool safe = true;

		for (auto i = begin(report) + 1, e = end(report); i != e; i++) {
			int current = *i, previous = *(i - 1);

			if (increasing(previous, current) != shouldIncrease
				|| current == previous
				|| std::abs(current - previous) > 3) {
				safe = false;
				break;
			}
		}

		count += safe;
	}

	std::cout << "part 1: " << count;
}