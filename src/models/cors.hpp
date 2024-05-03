#pragma once

#include <uopenapi/http/response_info.hpp>
#include <uopenapi/http/response_serializator/serializator.hpp>
#include <uopenapi/http/schema/response/appender.hpp>
#include <uopenapi/http/schema_response.hpp>
#include <uopenapi/http/source_type.hpp>
#include <uopenapi/reflective/requirements/none_requirements.hpp>
#include <uopenapi/utils/formatted_exception.hpp>

namespace models {
struct CORS {};
} // namespace models
namespace uopenapi::http {
template <>
struct schema_appender_response<models::CORS, reflective::none_requirements,
                                source_type::header> {
  static void append(reflective::schema_view, std::string_view,
                     reflective::none_requirements) {
    // do nothing
  }
};
} // namespace uopenapi::http

namespace uopenapi::http {
template <> struct response_serializator<models::CORS, source_type::header> {
  static void serialize(const models::CORS &, response_info &r_info,
                        std::string_view) {
    auto add_header = [&](std::string_view name_header,
                          std::string_view value) {
      auto [it, emplaced] = r_info.headers.emplace(name_header, value);
      if (!emplaced) {
        throw utils::formatted_exception(
            "Detected multiply value of header [{}], first value: [{}], second "
            "value: [{}]",
            name_header, it->second, value);
      }
    };
    add_header("Access-Control-Allow-Methods", "GET, POST");
    add_header("Access-Control-Allow-Origin", "*");
    add_header("Access-Control-Allow-Credentials", "true");
    add_header("Access-Control-Allow-Headers", "GET, POST");
    add_header("Access-Control-Expose-Headers", "*");
  }
};
} // namespace uopenapi::http
