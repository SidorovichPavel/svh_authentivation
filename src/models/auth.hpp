#pragma once
#include <boost/uuid/uuid.hpp>
#include <string>

namespace model::auth {

struct RequestBody {
  std::string login;
  std::string password;
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

} // namespace models::auth
