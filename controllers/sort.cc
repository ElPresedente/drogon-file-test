#include "sort.h"
#include <my_sort.hpp>
#include <regex>

// Add definition of your processing function here

void sort::get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string p1){
    std::vector<int> nums;

    std::regex regex{R"(\d+)"};
    
    for( auto iter = std::sregex_iterator{p1.begin(), p1.end(), regex}; 
        iter != std::sregex_iterator{}; ++iter )
    {
        std::smatch m = *iter;
        nums.emplace_back(stoi( m[0] ));
    }

    std::stringstream ss;

    if( !nums.empty() ){
        HeapSorter h{nums};
        h.sort();
        bool is_first = true;
        for( auto i : nums ){
            if( !is_first ){
                ss << ", ";
            }
            ss << i;
            is_first = false;
        }
    }

    HttpViewData data;
    data.insert("title", "some title");
    data.insert("result", ss.str());
    
    //auto resp = HttpResponse::newHttpJsonResponse( ret );
    auto resp = HttpResponse::newHttpViewResponse( "sort.csp", data );
    callback(resp);
}
