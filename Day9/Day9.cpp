#include <iostream>
#include <fstream>
#include <vector>
#include <string>
std::ifstream fin("input.txt");

struct memblock {
	int id;
	int start = 0;
	int length = 0;

	memblock(int pId, int pStart, int pLength) : id(pId), start(pStart), length(pLength) {	}

	memblock &operator =(const memblock &pOther) {
		id = pOther.id;
		start = pOther.start;
		length = pOther.length;
		return *this;
	}
};

typedef std::vector<memblock> data;

void print(const data &);
void part1(data);

int main()
{
	data input;
	std::string line;

	std::getline(fin, line);

	int iterator = 0, globalIndex = 0;
	bool usedSpace = true;

	for (const char ch : line) {
		int repeats = ch - '0';
		if (usedSpace) {
			input.push_back({ globalIndex++, iterator, repeats });
		}

		usedSpace = !usedSpace;
		iterator += repeats;
	}

	part1(input);
	std::cout << "\n";
}

void print(const data &pInput) {
	for (auto iterator = pInput.cbegin(), end = pInput.cend(); iterator != end; iterator++) {
		const memblock &block = *iterator;
		for (int i = 0; i < block.length; i++) {
			std::cout << block.id;
		}

		if (iterator != end - 1) {
			const memblock &next = *(iterator + 1);
			for (int i = 0; i < next.start - block.start - block.length; i++) {
				std::cout << '.';
			}
		}
	}
}

bool find_free_space(const data &pInput, int &pFreeSpacePos, int &pIndex) {
	int guess = 0;
	for (int i = 0; i < pInput.size(); i++) {
		const memblock &block = pInput[i];
		if (guess < block.start) {
			pFreeSpacePos = guess;
			pIndex = i;
			return true;
		}else if (guess >= block.start && guess < block.start + block.length) {
			guess += block.length;
		}
	}
	return false;
}

void part1(data pInput) {
	// preprocessing
	int freeSpace, insertIndex;
	while (find_free_space(pInput, freeSpace, insertIndex)) {
		memblock &last = pInput.back();
		last.length--;

		if (last.length < 1) {
			pInput.pop_back();
		}

		bool inserted = false;
		if (insertIndex > 0) {
			memblock &match = pInput[insertIndex - 1];
			if (match.id == last.id) {
				match.length++;
				inserted = true;
			}
		}

		if (!inserted) {
			pInput.emplace(pInput.begin() + insertIndex, last.id, freeSpace, 1);
		}
	}

	long long sum = 0;
	for (const auto &block : pInput) {
		// the memory blocks are contiguous, so
		// the arithmetic progression sum can
		// be used to quickly calculate its local checksum
		sum += (long long)(block.start * 2 + block.length - 1) * block.length * block.id / 2;
	}

	std::cout << "part 1: " << sum;
}