#include <iostream>
#include <fstream>
#include <string>
#include <vector>
std::ifstream fin("input.txt");

typedef std::vector<std::vector<bool>> grid;

struct point {
	int i, j;
};

void part1(const grid &, point);

int main()
{
	grid input;
	point guardPos = { 0, 0 };
	std::string line;

	int i = 0;
	while (std::getline(fin, line)) {
		input.emplace_back();

		for (int j = 0; j < line.size(); j++) {
			// '.', '^' -> free
			// '#' -> wall
			input.back().push_back((line[j] == '#'));

			if (line[j] == '^') {
				guardPos = { i, j };
			}
		}

		i++;
	}

	part1(input, guardPos);
	std::cout << "\n";
}

enum dir {
	NONE = 0,
	LEFT = 1,
	UP = 2,
	RIGHT = 3,
	DOWN = 4
};

dir rotate(const dir &pDir) {
	switch (pDir) {
	case LEFT:
		return UP;
	case UP:
		return RIGHT;
	case RIGHT:
		return DOWN;
	case DOWN:
		return LEFT;
	}
	return NONE;
}

bool move(const grid &pGrid, dir pDir, point &pPos, bool &pWall) {
	pWall = false;

	bool horizontal = pDir & 1;
	bool decrease = pDir < 3;
	int delta = decrease ? -1 : 1;
	point newPoint = {
		!horizontal ? (pPos.i + delta) : pPos.i,
		horizontal ? (pPos.j + delta) : pPos.j
	};

	if (newPoint.i < 0 || newPoint.i >= pGrid.size()
		|| newPoint.j < 0 || newPoint.j >= pGrid[0].size()) {
		return false;
	}

	if (pGrid[newPoint.i][newPoint.j]) {
		pWall = true;
		return true;
	}

	pPos = newPoint;
	return true;
}

void part1(const grid &pGrid, point pGuardPos) {
	dir guardDir = UP;
	grid explored(pGrid.size(), std::vector<bool>(pGrid[0].size()));
	int count = 0;
	bool lookingAtWall = false;

	do {
		if (lookingAtWall) {
			guardDir = rotate(guardDir);
		}
		else {
			count += !explored[pGuardPos.i][pGuardPos.j];
			explored[pGuardPos.i][pGuardPos.j] = 1;
		}
	} while (move(pGrid, guardDir, pGuardPos, lookingAtWall));

	std::cout << "part 1: " << count;
}