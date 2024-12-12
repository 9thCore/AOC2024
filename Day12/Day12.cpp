#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <tuple>
#include <string>
std::ifstream fin("input.txt");

const int DELTA[][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

struct region {
	long long area, perimeter;
};

typedef std::vector<region> data;
typedef std::vector<std::vector<char>> map;

void part1(const data &);
void process(const map &, data &);

int main()
{
	data input;
	map unprocessedMap;

	std::string line;

	while (std::getline(fin, line)) {
		unprocessedMap.emplace_back();

		for (const char ch : line) {
			unprocessedMap.back().push_back(ch);
		}
	}

	process(unprocessedMap, input);

	part1(input);
	std::cout << "\n";
}

void part1(const data &pInput) {
	long long sum = 0;

	for (const auto &region : pInput) {
		sum += region.area * region.perimeter;
	}

	std::cout << "part 1: " << sum;
}

void bfs(const map &pMap, map &pExplored, data &pInput, int pOriginI, int pOriginJ) {
	char match = pMap[pOriginI][pOriginJ];

	pInput.emplace_back();
	pInput.back().area = 1;

	std::queue<std::tuple<int, int>> queue;
	queue.emplace(pOriginI, pOriginJ);
	pExplored[pOriginI][pOriginJ] = 1;

	while (!queue.empty()) {
		int i = std::get<0>(queue.front()), j = std::get<1>(queue.front());
		queue.pop();

		pInput.back().perimeter += 4;

		for (int dir = 0; dir < 4; dir++) {
			int newI = i + DELTA[dir][0], newJ = j + DELTA[dir][1];
			
			if (newI < 0 || newI >= pMap.size()
				|| newJ < 0 || newJ >= pMap[newI].size()
				|| pMap[newI][newJ] != match) {
				continue;
			}

			// count neighbouring region cells,
			// even if they were already marked
			if (pExplored[newI][newJ]) {
				pInput.back().perimeter--;
				continue;
			}

			queue.emplace(newI, newJ);
			pExplored[newI][newJ] = 1;
			pInput.back().area++;
			pInput.back().perimeter--;
		}
	}


}

void process(const map &pMap, data &pInput) {
	map explored;
	explored.resize(pMap.size());

	for (int i = 0; i < pMap.size(); i++) {
		explored[i].resize(pMap[i].size());
	}

	for (int i = 0; i < pMap.size(); i++) {
		for (int j = 0; j < pMap[i].size(); j++) {
			if (!explored[i][j]) {
				bfs(pMap, explored, pInput, i, j);
			}
		}
	}
}