#pragma once

#include <drogon/drogon.h>
#include <json/json.h>
#include <fstream>
#include <iostream>

Json::Value read_json_from_file(const std::string &filePath);
