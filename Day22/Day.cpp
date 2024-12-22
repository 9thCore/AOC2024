#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
std::ifstream fin("input.txt");

typedef long long num;
typedef std::vector<num> data;

void part1(data);
void part2(data);

int main()
{
    data input;
    
    std::string line;
    while (std::getline(fin, line)) {
        input.push_back(std::stoll(line));
    }

    part1(input);
    std::cout << "\n";
    part2(input);
}

void mix(num &pSecretNumber, num pValue) {
    pSecretNumber ^= pValue;
}

void prune(num &pSecretNumber) {
    pSecretNumber &= (16777216 - 1);
}

void mix_and_prune(num &pSecretNumber, num pFactor, bool pDivide = false) {
    num value = pDivide ? (pSecretNumber >> pFactor) : (pSecretNumber << pFactor);
    prune(pSecretNumber);
    mix(pSecretNumber, value);
    prune(pSecretNumber);
}

void evolve_secret(num &pSecretNumber) {
    mix_and_prune(pSecretNumber, 6);
    mix_and_prune(pSecretNumber, 5, true);
    mix_and_prune(pSecretNumber, 11);
}

void part1(data pInput) {
    for (int step = 0; step < 2000; step++) {
        for (num &secretNumber : pInput) {
            evolve_secret(secretNumber);
        }
    }

    num sum = 0;
    for (num secretNumber : pInput) {
        sum += secretNumber;
    }

    std::cout << "part 1: " << sum;
}

void part2(data pInput) {
    // dummy
}