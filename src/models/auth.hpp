#pragma once
#include <boost/uuid/uuid.hpp>
#include <string>

#include <userver/storages/postgres/io/io_fwd.hpp>
#include <userver/storages/postgres/io/pg_types.hpp>

namespace model::auth {

struct UserAuthCredentials {
  boost::uuids::uuid id;
  std::string first_name;
  std::int64_t age;
  std::string nickname;
  std::string dhashed_password;
  std::string salt;
};

struct RequestBody {
  std::string nickname;
  std::string password_hash;
};

struct Request {
  RequestBody body;
};

struct ResponseBody {
  std::string token;
};

struct Response {
  ResponseBody body;
};

} // namespace model::auth

namespace userver::storages::postgres::io {

template <> struct CppToUserPg<model::auth::UserAuthCredentials> {
  static constexpr DBTypeName postgres_name =
      "svh_users_manager.UserAuthCredentialsType";
};

} // namespace userver::storages::postgres::io
