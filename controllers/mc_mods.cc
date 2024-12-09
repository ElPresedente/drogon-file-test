#include "mc_mods.h"
#include "drogon/HttpResponse.h"

#include "json/value.h"
#include <filesystem>
#include <json_from_file.hpp>
#include <file_hash.hpp>

#include <constants.hpp>

namespace fs = std::filesystem;

void mc_mods::list(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback){
    auto value = read_json_from_file( constants::json_path );
 
    auto resp = HttpResponse::newHttpJsonResponse( value );
    callback( resp );
}

void mc_mods::update(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback){
    const fs::path mods{ constants::mods_folder };
    
    Json::Value res;

    auto&& mods_val = res["mods"] = Json::Value{};

    if( !fs::exists( mods ) || !fs::is_directory( mods )){
        auto resp = drogon::HttpResponse::newNotFoundResponse();
        resp->setBody("Folder not found");
        callback(resp);
        return;
    }

    for( Json::ArrayIndex i = 0; auto file : fs::directory_iterator( mods )){
        Json::Value item;
        item["name"] = file.path().filename().string();
        item["hash"] = calculate_string( file.path() );

        mods_val[i] = item;
        i++;
    }
    std::ofstream file( constants::json_path, std::ios::binary );
    file << mods_val.toStyledString();
    auto resp = HttpResponse::newHttpJsonResponse( mods_val );
    callback( resp );
}

void mc_mods::download(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string p1){

}