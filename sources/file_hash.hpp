#pragma once

#include <filesystem>
#include <openssl/sha.h>
#include <string>
#include <fstream>
#include <sstream>
#include "filesystem.hpp"


inline std::string calculate_string( fs::path p ){
    std::ifstream file(p, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Unable to open file: " + p.string());
    }

    // Инициализируем объект для вычисления SHA-256
    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    // Читаем файл блоками
    const size_t bufferSize = 4096; // Размер буфера (4 KB)
    char buffer[bufferSize];
    while (file.read(buffer, bufferSize)) {
        SHA256_Update(&sha256, buffer, file.gcount());
    }
    // Обрабатываем остаток файла (если есть)
    SHA256_Update(&sha256, buffer, file.gcount());

    // Завершаем вычисление хеша
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256);

    // Преобразуем хеш в строку (в формате HEX)
    std::stringstream hexHash;
    for (unsigned char byte : hash) {
        hexHash<< std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return hexHash.str();
}