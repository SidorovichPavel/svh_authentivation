#include "handler.hpp"

#include <userver/components/component_list.hpp>

namespace views::login {
void Append(userver::components::ComponentList &componentList) {
  componentList.Append<handler>();
}

handler::response handler::handle(views::login::Request req) const {

  std::optional<std::string> token;
  if (!token) {
    Response400 resp400;
    resp400().body.message = "Invalid login or password";
    resp400().body.error_code = model::ErrorCode::invalid_credentials;
    return resp400;
  }
  Response200 response200;
  response200().body.token = *token;
  return response200;
}
} // namespace views::login
