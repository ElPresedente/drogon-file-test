#pragma once

#include <openssl/sha.h>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <array>

namespace fs = std::filesystem;

std::string calculate_string( fs::path p );
