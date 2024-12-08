#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <tuple>
std::ifstream fin("input.txt");

typedef std::tuple<int, int> position;
typedef std::vector<position> positions;
typedef std::array<positions, 100> data;
typedef std::array<std::array<bool, 51>, 51> grid;
typedef std::vector<std::string> lines;

int hash(char);

void part1(const data &, const lines &);

int main()
{
	data input;
	lines storage;
	std::string line;

	int j = 0;
	while (std::getline(fin, line)) {
		for (int i = 0; i < line.size(); i++) {
			int hashed = hash(line[i]);
			if (hashed != -1) {
				input[hashed].push_back({ j, i });
			}
		}
		j++;

		storage.push_back(line);
	}

	part1(input, storage);
	std::cout << "\n";
}

bool set(grid &pGrid, bool value, int n, int m, int i, int j) {
	if (i < 0 || i >= n
		|| j < 0 || j >= m) {
		return false;
	}

	bool old = pGrid[i][j];
	pGrid[i][j] = value;
	return old != value;
}

void part1(const data &pInput, const lines &pLines) {
	int count = 0;
	grid unique = { {0} };
	int n = pLines.size(), m = pLines[0].size();

	for (const positions &pos : pInput) {
		for (int i = 0; i < pos.size(); i++) {
			for (int j = i + 1; j < pos.size(); j++) {
				int firstI = std::get<0>(pos[i]), secondI = std::get<0>(pos[j]);
				int firstJ = std::get<1>(pos[i]), secondJ = std::get<1>(pos[j]);

				int iDiff = firstI - secondI;
				int jDiff = firstJ - secondJ;

				int minI = std::min(firstI, secondI), maxI = std::max(firstI, secondI);
				int minJ = std::min(firstJ, secondJ), maxJ = std::max(firstJ, secondJ);

				// |1 |           |1|
				// | 2|, |1 2| or |2|
				if (iDiff * jDiff >= 0) {
					count += set(unique, 1, n, m, minI - std::abs(iDiff), minJ - std::abs(jDiff));
					count += set(unique, 1, n, m, maxI + std::abs(iDiff), maxJ + std::abs(jDiff));
				}
				else {
					// | 1|
					// |2 |
					count += set(unique, 1, n, m, minI - std::abs(iDiff), maxJ + std::abs(jDiff));
					count += set(unique, 1, n, m, maxI + std::abs(iDiff), minJ - std::abs(jDiff));
				}
			}
		}
	}

	std::cout << "part 1: " << count;
}

int hash(char pCh) {
	if (pCh >= 'a' && pCh <= 'z') {
		return pCh - 'a';
	}
	else if (pCh >= 'A' && pCh <= 'Z') {
		return pCh - 'A' + 'z' - 'a' + 1;
	}
	else if (pCh >= '0' && pCh <= '9') {
		return pCh - '0' + ('z' - 'a' + 1) * 2;
	}

	return -1;
}