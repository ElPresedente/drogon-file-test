#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class test_root : public drogon::HttpController<test_root>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(test_root::get, "/{2}/{1}", Get); // path is /test_root/{arg2}/{arg1}
    // METHOD_ADD(test_root::your_method_name, "/{1}/{2}/list", Get); // path is /test_root/{arg1}/{arg2}/list
    // ADD_METHOD_TO(test_root::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list
    ADD_METHOD_VIA_REGEX(test_root::handler,"/test_root/(.*)",Get);
    ADD_METHOD_VIA_REGEX(test_root::file_handler,"/test_root/(.*)",Post);
    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    void handler(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string p1) const;
    void file_handler(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback);
};
