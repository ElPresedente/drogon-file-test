#include "test_root.h"

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
