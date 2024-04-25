#pragma once

#include <uopenapi/http/schema_response.hpp>
#include <uopenapi/http/response_serializator/serializator.hpp>
#include <uopenapi/http/response_info.hpp>
#include <uopenapi/utils/formatted_exception.hpp>

namespace models {
    struct CORS{};
}

namespace uopenapi::http::details{
    template <typename T, utils::ce::string name>
    requires (std::is_same_v<uopenapi::pfr_extension::tuple_element_name_t<T, name>, models::CORS>)
    void append_response_field(reflective::schema_view){
        //do nothing
    }
}

namespace uopenapi::http{
    template <>
    struct response_serializator<models::CORS, source_type::header>{
        static void serialize(const models::CORS&, response_info& r_info, std::string_view){
            auto add_header = [&](std::string_view name_header, std::string_view value){
                auto [it, emplaced] = r_info.headers.emplace(name_header, value);
                if (!emplaced){
                    throw utils::formatted_exception("Detected multiply value of header [{}], first value: [{}], second value: [{}]", name_header, it->second, value);
                }
            };
            add_header("Access-Control-Allow-Methods", "GET, POST");
            add_header("Access-Control-Allow-Origin", "*");
            add_header("Access-Control-Allow-Credentials", "true");
            add_header("Access-Control-Allow-Headers", "GET, POST");
            add_header("Access-Control-Expose-Headers", "*");
        }
    };
}
