#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <functional>
#include <sstream>
#include <map>
#include "stl/chainhash.h"
#include "record.h"

using namespace std;

constexpr unsigned int SHA256_BLOCK_SIZE = 64;
constexpr unsigned int SHA256_DIGEST_SIZE = 32;
constexpr unsigned int k[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

template<typename T>
class Block {
private:
    int index;
    double nonce;
    ChainHash<int, Record*> records;
    string string_records;
    string current_hash_code;
    string previous_hash_code;
    int record_index;
    int capacity;

public:
    Block(){
        index = 0;
        nonce = 0;
        string_records = "";
        current_hash_code = "";
        previous_hash_code = "";
        record_index = 0;
        capacity = 10;
    }

    void setIndex(int index) {
      this->index = index;
    }

    void setPreviousHashCode(string previous_hash_code) {
      this->previous_hash_code = previous_hash_code;
    }

    int getIndex(){
        return index;
    }

    double getNonce(){
        return nonce;
    }

    string getDatos(){
        return "";
    }

    string getHashCode(){
        return current_hash_code;
    }

    string getPreviousHashCode(){
        return previous_hash_code;
    }

    int getSize() {
      return record_index + 1;
    }

    int getCapacity() {
      return capacity;
    }

    void insert(Record* new_record) {
        records.insert(make_pair(record_index, new_record));
        string_records.append(new_record->full_data());

        record_index += 1;
    }

  Record* getRecord(int record_index) {
      int count = 0;
      for (int i = 0; i < capacity; i++) {
          auto it = records.begin(i);
          auto end = records.end(i);
          while (it != end) {
              if (count == record_index) {
                  return it->second;
              }
              ++it;
              ++count;
          }
      }
      return nullptr;
  }
    // HASH CODE

    constexpr inline unsigned int RotateRight(unsigned int value,     unsigned int n) {
        return (value >> n) | (value << (32 - n));
    }

    string ToHex(unsigned int value) {
        std::stringstream ss;
        ss << std::hex << std::setw(8) << std::setfill('0') << value;
        return ss.str();
    }

    std::string sha256(const std::string& input) {
        unsigned int hash[SHA256_DIGEST_SIZE] = {
                0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
        };

        std::string message = input;
        message.push_back(0x80);

        unsigned int messageLength = message.length();
        unsigned int numBlocks = ((messageLength + 8) / SHA256_BLOCK_SIZE) + 1;
        unsigned int paddedLength = numBlocks * SHA256_BLOCK_SIZE;
        std::vector<unsigned char> paddedMessage(paddedLength, 0);
        std::copy(message.begin(), message.end(), paddedMessage.begin());

        unsigned long long bitLength = (static_cast<unsigned long long>(messageLength)) * 8;
        for (int i = 0; i < 8; ++i) {
            paddedMessage[paddedLength - 8 + i] = (bitLength >> (56 - i * 8)) & 0xFF;
        }

        for (unsigned int block = 0; block < numBlocks; ++block) {
            const unsigned char* currentBlock = &paddedMessage[block * SHA256_BLOCK_SIZE];

            unsigned int words[64];
            for (int i = 0; i < 16; ++i) {
                words[i] = (currentBlock[i * 4] << 24) | (currentBlock[i * 4 + 1] << 16) |
                           (currentBlock[i * 4 + 2] << 8) | currentBlock[i * 4 + 3];
            }

            for (int i = 16; i < 64; ++i) {
                unsigned int s0 = RotateRight(words[i - 15], 7) ^ RotateRight(words[i - 15], 18) ^ (words[i - 15] >> 3);
                unsigned int s1 = RotateRight(words[i - 2], 17) ^ RotateRight(words[i - 2], 19) ^ (words[i - 2] >> 10);
                words[i] = words[i - 16] + s0 + words[i - 7] + s1;
            }

            unsigned int a = hash[0];
            unsigned int b = hash[1];
            unsigned int c = hash[2];
            unsigned int d = hash[3];
            unsigned int e = hash[4];
            unsigned int f = hash[5];
            unsigned int g = hash[6];
            unsigned int h = hash[7];

            for (int i = 0; i < 64; ++i) {
                unsigned int S1 = RotateRight(e, 6) ^ RotateRight(e, 11) ^ RotateRight(e, 25);
                unsigned int ch = (e & f) ^ (~e & g);
                unsigned int temp1 = h + S1 + ch + k[i] + words[i];
                unsigned int S0 = RotateRight(a, 2) ^ RotateRight(a, 13) ^ RotateRight(a, 22);
                unsigned int maj = (a & b) ^ (a & c) ^ (b & c);
                unsigned int temp2 = S0 + maj;

                h = g;
                g = f;
                f = e;
                e = d + temp1;
                d = c;
                c = b;
                b = a;
                a = temp1 + temp2;
            }

            hash[0] += a;
            hash[1] += b;
            hash[2] += c;
            hash[3] += d;
            hash[4] += e;
            hash[5] += f;
            hash[6] += g;
            hash[7] += h;
        }

        std::stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_SIZE; ++i) {
            ss << ToHex(hash[i]);
        }
        return ss.str();
    }

    void proofOfWork() {
        std::string pattern = "00"; //Patron inicial para todos los hash

        int nonce = 0;
        std::string computed_hash;
        do {
            std::string data = string_records.append(to_string(nonce));
            computed_hash = sha256(data);
            nonce++;
        } while (computed_hash.find(pattern));

        // std::cout << "Nonce encontrado: " << nonce << std::endl; //Se debe actualizar al bloque
        // std::cout << "Hash del bloque: " << block_hash << std::endl; //Se debe actualizar al bloque
        this->nonce = nonce;
        this->current_hash_code = computed_hash;
    }
};
