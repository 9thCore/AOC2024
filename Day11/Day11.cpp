#include <iostream>
#include <fstream>
#include <vector>
std::ifstream fin("input.txt");

typedef long long num;
typedef std::vector<num> data;

void part1(data);

int main()
{
	data input;

	num x;
	while (fin >> x) {
		input.push_back(x);
	}

	part1(input);
}

int digit_count(num value) {
	int count = (value == 0);
	while (value) {
		count++;
		value /= 10;
	}
	return count;
}

void simulate(data &pInput) {
	for (int i = 0; i < pInput.size(); i++) {
		num &value = pInput[i];
		int cnt = digit_count(value);
		if (value == 0) {
			value = 1;
		}
		else if (cnt % 2 == 0) {
			num pow10 = std::pow(10LL, cnt / 2);
			num first_half = value / pow10;
			num second_half = value % pow10;
			value = second_half;
			pInput.insert(pInput.begin() + i, first_half);
			i++;
		}
		else {
			value *= 2024;
		}
	}
}

void part1(data pInput) {
	for (int i = 0; i < 25; i++) {
		simulate(pInput);
	}

	std::cout << "part 1: " << pInput.size();
}