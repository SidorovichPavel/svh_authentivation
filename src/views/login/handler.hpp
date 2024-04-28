#pragma once

#include "io.hpp"
#include <uopenapi/all.hpp>
#include <userver/formats/parse/boost_uuid.hpp>
#include <userver/formats/serialize/boost_uuid.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/storages/postgres/postgres.hpp>

namespace views::login {

using base =
    uopenapi::components::openapi_handler<Request, Response200, Response400>;
struct handler : base {
  static constexpr std::string_view kName = "login_handler";
  handler(const userver::components::ComponentConfig &cfg,
          const userver::components::ComponentContext &ctx);

  response handle(views::login::Request req) const;

private:
  std::optional<model::auth::UserAuthCredentials>
  SelectAuthData(std::string username) const;

  std::string MakeToken(const model::auth::UserAuthCredentials &uac) const;

  userver::storages::postgres::ClusterPtr pg_cluster_;
};

} // namespace views::login
