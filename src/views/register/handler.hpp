#pragma once

#include "io.hpp"
#include <boost/uuid/uuid.hpp>
#include <codegen/sql.hpp>
#include <models/identity.hpp>
#include <uopenapi/all.hpp>
#include <userver/formats/parse/boost_uuid.hpp>
#include <userver/formats/parse/common.hpp>
#include <userver/formats/serialize/boost_uuid.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/storages/postgres/postgres.hpp>

namespace views::Register {

struct handler
    : uopenapi::components::openapi_handler<Request, Response200, Response400> {
  static constexpr std::string_view kName = "register_handler";

  handler(const userver::components::ComponentConfig &cfg,
          const userver::components::ComponentContext &ctx);

  response handle(views::Register::Request req) const override;

private:
  std::optional<boost::uuids::uuid>
  TryInsertUser(const model::identity::UserRegisterCredentials &ucreds) const;
  std::string MakeToken(const boost::uuids::uuid &uuid,
                        const model::identity::UserRegisterCredentials) const;

  userver::storages::postgres::ClusterPtr pg_cluster_;
};
} // namespace views::Register
