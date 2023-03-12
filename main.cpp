#include <bitset>
#include <functional>
#include <iostream>
#include <fstream>

int numTests = 1000000;
int numFalsePositives = 0;

class BloomFilter {
public:
    BloomFilter(int size, int numHashes) :
            m(size),
            k(numHashes) {}

    void add(const std::string &str) {
        for (int i = 0; i < k; i++) {
            int index = hash(str, i) % m.size();
            m.set(index);
        }
    }

    bool contains(const std::string &str) const {
        for (int i = 0; i < k; i++) {
            int index = hash(str, i) % m.size();
            if (!m.test(index)) {
                return false;
            }
        }
        return true;
    }

private:
    std::bitset<10000000> m;
    int k;

    std::size_t hash(const std::string &str, int seed) const {
        std::hash<std::string> hashFunction;
        return hashFunction(str + std::to_string(seed));
    }
};
//test : m : 1000000, m/n : 2, numHashes : 5 0.000508

int main() {
    std::ofstream fout("ans.txt");
    BloomFilter bloomFilter(1000000, 1);
    int q = 2;
    while(q <= 8){//
        for (int i = 0; i < numTests / q; i++) {
            std::string add_str = std::to_string(i) + "tset";
            bloomFilter.add(add_str);
        }


        for (int i = 0; i < numTests; i++) {
            std::string ctn_str = "test" + std::to_string(i);
            if (bloomFilter.contains(ctn_str)) {
                numFalsePositives++;
            }
        }

        double falsePositiveRate = (double) numFalsePositives / numTests;
        fout << "False positive rate: " << falsePositiveRate << std::endl;
        q++;
    }
    return 0;
}
