#include "file_hash.hpp"
#include "json_from_file.hpp"


std::string calculate_string( fs::path p ){
    std::ifstream file( p, std::ios::binary );
    if ( !file ) {
        throw std::runtime_error( "Unable to open file: " + p.string() );
    }

    // Инициализируем объект для вычисления SHA-256
    SHA256_CTX sha256;
    SHA256_Init( &sha256 );

    // Читаем файл блоками
    const size_t bufferSize = 4096; // Размер буфера (4 KB)
    char buffer[ bufferSize ];
    while( file.read( buffer, bufferSize )) {
        SHA256_Update( &sha256, buffer, file.gcount() );
    }
    // Обрабатываем остаток файла (если есть)
    SHA256_Update( &sha256, buffer, file.gcount() );

    // Завершаем вычисление хеша
    std::array<unsigned char, SHA256_DIGEST_LENGTH> hash;
    SHA256_Final( hash.data(), &sha256 );

    // Преобразуем хеш в строку (в формате HEX)
    std::stringstream hexHash;
    for (unsigned char byte : hash) {
        hexHash << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return hexHash.str();
}

Json::Value read_json_from_file(const std::string &filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open JSON file: " + filePath);
    }

    Json::Value jsonData;
    file >> jsonData; // Загружаем JSON в объект Json::Value
    return jsonData;
}