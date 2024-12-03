#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
std::ifstream fin("input.txt");

typedef std::vector<std::string> data;

void part1(data);

int main()
{
	data input;

	std::string line;
	while (fin >> line) {
		input.push_back(line);
	}

	part1(input);
	std::cout << "\n";
}

int multiply(const std::smatch &pMatch) {
	return std::stoi(pMatch[1].str()) * std::stoi(pMatch[2].str());
}

void part1(data pInput) {
	int sum = 0;

	std::regex matcher("mul\\(([0-9]+), ?([0-9]+)\\)");
	std::smatch match;

	for (std::string line : pInput) {
		while (std::regex_search(line, match, matcher)) {
			sum += multiply(match);
			line = match.suffix().str();
		}
	}

	std::cout << "part 1: " << sum;
}