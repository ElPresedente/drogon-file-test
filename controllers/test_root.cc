#include "test_root.h"
#include <file_hash.hpp>
#include <filesystem>

// Add definition of your processing function here

void test_root::handler(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string p1) const{
   
    HttpViewData data;
    data.insert("title", "some title");
    data.insert("path", p1);

    auto resp=HttpResponse::newHttpViewResponse("root.csp",data);

    callback(resp);
}

void test_root::file_handler(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback){
    MultiPartParser fileParser;
    fileParser.parse(req);
    auto file = fileParser.getFiles()[0];
    std::cout << file.getFileName() << std::endl;

    auto path = fileParser.getParameter<std::string>("path");

    file.save(path);

    Json::Value json;
    json["res"] = true;
    auto resp = HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}

void test_root::send_file(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string p1) const{
    std::string filePath = "./uploads/" + p1;
    std::cout << calculate_string( fs::path( filePath )) << std::endl;
    if (!std::filesystem::exists(filePath)) {
        // Возвращаем 404, если файл не найден
        auto resp = drogon::HttpResponse::newNotFoundResponse();
        resp->setBody("File not found");
        callback(resp);
        return;
    }
    auto resp = drogon::HttpResponse::newFileResponse(filePath);

    // Устанавливаем заголовки
    resp->setContentTypeString( "application/octet-stream" );
    resp->addHeader("Content-Disposition", "attachment; filename=\"" + filePath + "\"");

    // Отправляем ответ
    callback(resp);
}
