#include <iostream>
#include <fstream>
#include <vector>
#include <string>
std::ifstream fin("input.txt");

const char WORD[] = "XMAS";
const int WORD_LEN = sizeof(WORD) / sizeof(char);
const int DEFAULT_DISTANCE = -1;

struct cell {
	char ch = 0;
	int originDistance = DEFAULT_DISTANCE;
	int participatingWords = 0;

	cell(char ch) {
		this->ch = ch;
	}
};

typedef std::vector<std::vector<cell>> data;

void part1(data);

int main()
{
	data input;
	std::string line;

	while (fin >> line) {
		input.emplace_back();

		for (const char ch : line) {
			input.back().push_back({ ch });
		}
	}

	part1(input);
	std::cout << "\n";
}

void propagate_xmas_word(data &pData, int pI, int pJ, int pDeltaI, int pDeltaJ) {
	int i = pI + pDeltaI, j = pJ + pDeltaJ;
	if (i < 0 || i >= pData.size()) {
		return;
	}

	if (j < 0 || j >= pData[i].size()) {
		return;
	}

	int dist = pData[pI][pJ].originDistance + 1;

	if (pData[i][j].ch != WORD[dist]) {
		return;
	}

	pData[i][j].participatingWords++;
	pData[i][j].originDistance = dist;
	propagate_xmas_word(pData, i, j, pDeltaI, pDeltaJ);

	if (pData[i][j].originDistance >= WORD_LEN) {
		return;
	}
}

void propagate_xmas_word(data &pData, int pI, int pJ) {
	pData[pI][pJ].originDistance = 0;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i || j) {
				propagate_xmas_word(pData, pI, pJ, i, j);
			}
		}
	}
}

void part1(data pData) {
	int count = 0;

	for (int i = 0; i < pData.size(); i++) {
		for (int j = 0; j < pData[i].size(); j++) {
			if (pData[i][j].ch == 'X') {
				propagate_xmas_word(pData, i, j);
			}
		}
	}

	for (int i = 0; i < pData.size(); i++) {
		for (int j = 0; j < pData[i].size(); j++) {
			if (pData[i][j].ch == 'S' && pData[i][j].originDistance != DEFAULT_DISTANCE) {
				count += pData[i][j].participatingWords;
			}
		}
	}

	std::cout << "part 1: " << count;
}