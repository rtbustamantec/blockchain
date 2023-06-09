#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include "block.h"

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

constexpr inline unsigned int RotateRight(unsigned int value, unsigned int n) {
    return (value >> n) | (value << (32 - n));
}

std::string ToHex(unsigned int value) {
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


void generateHash(Block<TK>* bloque) {
   //Como añadir el bloque a la funcion :c
    std::string prev_block = bloque.getPreviousHashCode(); //Contiene el hash anterior
    std::string merkle_root = bloque.getHashCode(); //Contiene el hash actual
    
    int timestamp = 1622152949;
    std::string pattern = "10004"; //Patron inicial para todos los hash

    int nonce = 0;
    std::string block_hash;
    do {
        std::stringstream ss;
        ss << bloque.getNumeroBloque() << prev_block << merkle_root << timestamp << bloque.getnonce()<<bloque.getdatos(); // Contiene la data del bloque
        std::string data = ss.str();
        block_hash = sha256(data);
        nonce++;
    } while (block_hash.substr(0, pattern.length()) != pattern);

    std::cout << "Nonce encontrado: " << nonce << std::endl; //Se debe actualizar al bloque
    std::cout << "Hash del bloque: " << block_hash << std::endl; //Se debe actualizar al bloque
}


// int main() {
//     // Datos del bloque
//     int version = 1;
//     std::string prev_block = "0000000000000000000000000000000000000000000000000000000000000000";
//     std::string merkle_root = "6dcd83d15efad1c376cd9a42a1694c0dc3e7498c6634b7a0414f4a285b7b5c77";
//     int timestamp = 1622152949;
//     std::string pattern = "10000";  // Patrón inicial deseado

//     // Bucle de minería
//     int nonce = 0;
//     std::string block_hash;
//     do {
//         // Construir los datos del bloque con el nonce actualizado
//         std::stringstream ss;
//         ss << version << prev_block << merkle_root << timestamp << nonce;
//         std::string data = ss.str();

//         // Calcular el hash del bloque utilizando SHA-256
//         block_hash = sha256(data);
//         // Verificar si el hash del bloque cumple con el patrón inicial
//         if (block_hash.substr(0, pattern.length()) == pattern) {
//             break;
//         }
//         // Actualizar el nonce para el próximo intento
//         nonce++;
//     } while (true);
//     // Imprimir el resultado
//     std::cout << "Nonce encontrado: " << nonce << std::endl;
//     std::cout << "Hash del bloque: " << block_hash << std::endl;
//     return 0;
// }


