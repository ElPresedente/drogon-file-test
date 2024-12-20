#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class sort : public drogon::HttpController<sort>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    ADD_METHOD_TO(sort::get, "/sort?text={1}", Get); // path is /sort/{arg2}/{arg1}
    // METHOD_ADD(sort::your_method_name, "/{1}/{2}/list", Get); // path is /sort/{arg1}/{arg2}/list
    // ADD_METHOD_TO(sort::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list

    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string p1);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;
};
