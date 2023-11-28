#include <iostream>
#include <string>
#include <random>
#include "Binary.h"
#include "BinInterface.h"
#include "Hash.h"
using namespace std;

template<typename T>
T random(T range_from, T range_to) {
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<T>    distr(range_from, range_to);
    return distr(generator);
}

//string printRandomString(int n)
//{
//    char* alphabet = new char[45] { 'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E', 'f', 'F', 'g', 'G',
//                                  'h', 'H', 'i', 'I', 'j', 'J', 'k', 'K', 'l', 'L', 'm', 'n',
//                                  'o', 'O', 'p', 'P', 'q', 'r', 's', 'S', 't', 'u',
//                                  'v', 'w', 'W', 'x', 'X', 'y', 'Z', 'z', ' '};
//
//    string res = "";
//    for (int i = 0; i < n; i++) {
//        res = res + alphabet[random(0, 44)];
//    }
//    return res;
//}

int main() {
    HashTable ht;
    ht.testHeshT();

    HashTable HT;
    BinInterface Interface(&HT, "pool.bin");
    Interface.testBin();
}