#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class mc_mods : public drogon::HttpController<mc_mods>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(mc_mods::get, "/{2}/{1}", Get); // path is /mc_mods/{arg2}/{arg1}
    // METHOD_ADD(mc_mods::your_method_name, "/{1}/{2}/list", Get); // path is /mc_mods/{arg1}/{arg2}/list
    // ADD_METHOD_TO(mc_mods::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list

    METHOD_ADD(mc_mods::list, "/list", Get);
    METHOD_ADD(mc_mods::update, "/update", Get);
    METHOD_ADD(mc_mods::download, "/download?name={1}", Get);

    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;
    void list(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback);
    void update(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback);
    void download(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string p1);
};
