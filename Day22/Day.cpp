#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <deque>
#include <unordered_map>
#include <unordered_set>
std::ifstream fin("input.txt");

typedef long long num;
typedef std::vector<num> data;
typedef std::deque<num> window;
typedef uint64_t window_hash;

constexpr num MAGIC_NUMBER = 16777216 - 1;

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
    pSecretNumber &= MAGIC_NUMBER;
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

num calculate_change(num pLast, num pCurrent) {
    return pCurrent % 10 - pLast % 10;
}

window_hash get_value(window &pDeque) {
    // Assume the change will always fit in 8 bits,
    //  due to it being in the range [-9, 9].
    uint8_t val = pDeque.back();
    pDeque.pop_back();
    return val;
}

window_hash hash_window(window pWindow) {
    return get_value(pWindow)
        | (get_value(pWindow) << 8)
        | (get_value(pWindow) << 16)
        | (get_value(pWindow) << 24);
}

void part2(data pInput) {
    constexpr int SUCCESSIVE_CHANGE_COUNT = 4;
    
    // Maps a sequence of changes to
    //  the final sum, from which we grab
    //  the highest value.
    std::unordered_map<window_hash, num> buyer_map;

    int idx = 0;
    for (num &secretNumber : pInput) {
        // Map used to denote if we have added
        //  a given hash to the global sum
        std::unordered_set<window_hash> added;

        // A sliding window of the current sequence
        //  of changes, using a deque to leverage
        //  the fast popping from the front.
        window sliding_window;

        // Prepare the change sliding windows
        //  by simulating the first changes
        for (int step = 0; step < SUCCESSIVE_CHANGE_COUNT; step++) {
            num last = secretNumber;
            evolve_secret(secretNumber);
            sliding_window.push_back(calculate_change(last, secretNumber));
        }

        // Slide window along and map values accordingly
        for (int step = SUCCESSIVE_CHANGE_COUNT; step < 2000; step++) {
            window_hash hash = hash_window(sliding_window);
            if (added.find(hash) == added.end()) {
                buyer_map[hash] += secretNumber % 10;
                added.insert(hash);
            }

            num last = secretNumber;
            evolve_secret(secretNumber);

            sliding_window.pop_front();
            sliding_window.push_back(calculate_change(last, secretNumber));
        }
    }

    num result = 0;
    for (const auto &iter : buyer_map) {
        result = std::max(result, iter.second);
    }

    std::cout << "part 2: " << result;
}