#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
std::ifstream fin("input.txt");

const int DELTA[][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

typedef long long num;

struct point {
    num i = 0, j = 0;
};

typedef std::vector<std::string> map;
typedef std::vector<point> moves;

struct data {
    map mapData;
    point player = { 0, 0 };
    moves moveData;
};

void part1(data);
void part2(data);

int main()
{
    data input;
    
    std::string line;
    num i = 0;

    while (std::getline(fin, line)) {
        num j = 0;
    
        bool moveData = false;
        for (char &ch : line) {
            switch (ch) {
                case '@':
                    input.player = { i, j };
                    ch = '.';
                    break;
                case '<':
                    moveData = true;
                    input.moveData.push_back({ 0, -1 });
                    break;
                case 'v':
                    moveData = true;
                    input.moveData.push_back({ 1, 0 });
                    break;
                case '^':
                    moveData = true;
                    input.moveData.push_back({ -1, 0 });
                    break;
                case '>':
                    moveData = true;
                    input.moveData.push_back({ 0, 1 });
                    break;
            }
            j++;
        }

        if (!moveData) {
            input.mapData.push_back(line);
        }

        i++;
    }

    part1(input);
    std::cout << "\n";
    part2(input);
}

bool resolve_movement(map &pMap, point &pMover, const point &pDelta) {
    point nextPos = { pMover.i + pDelta.i, pMover.j + pDelta.j };
    point box = nextPos;
    char &ch = pMap[nextPos.i][nextPos.j];
    if (ch == '.') {
        pMover = nextPos;
        return true;
    }
    else if (ch == 'O' && resolve_movement(pMap, box, pDelta)) {
        ch = '.';
        pMap[box.i][box.j] = 'O';
        pMover = nextPos;
        return true;
    }
    return false;
}

bool resolve_player_movement(data &pInput, const point &pDelta) {
    return resolve_movement(pInput.mapData, pInput.player, pDelta);
}

void part1(data pInput) {
    for (const auto &move : pInput.moveData) {
        resolve_player_movement(pInput, move);
    }

    num score = 0;
    num i = 0;
    for (const auto &line : pInput.mapData) {
        num j = 0;
        for (const char &ch : line) {
            if (ch == 'O') {
                score += i * 100 + j;
            }
            j++;
        }
        i++;
    }

    std::cout << "part 1: " << score;
}

void part2(data pInput) {
    // dummy
}