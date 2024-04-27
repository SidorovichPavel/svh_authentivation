#pragma once

#include "uopenapi/http/field_source.hpp"
#include "userver/storages/postgres/io/io_fwd.hpp"
#include "userver/storages/postgres/io/pg_types.hpp"
#include <cstdint>
#include <string>

#include "cors.hpp"

namespace model::identity {

struct UserCredentials {
  std::string first_name;
  std::string last_name;
  std::int64_t age;
  std::string nickname;
  std::string password_hash;
};

struct Request {
  UserCredentials body;
};

struct ResponseBody {
  std::string token;
};

struct Response {
  ResponseBody body;
  [[maybe_unused]] models::CORS cors;
};

} // namespace model::identity

UOPENAPI_SOURCE_TYPE(model::identity::Response, cors, header);

namespace userver::storages::postgres::io {

template <> struct CppToUserPg<model::identity::UserCredentials> {
  static constexpr DBTypeName postgres_name =
      "svh_users_manager.UserCredentialsType";
};

} // namespace userver::storages::postgres::io