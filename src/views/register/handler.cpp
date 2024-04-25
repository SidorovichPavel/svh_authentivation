#include "handler.hpp"

#include "../../codegen/sql.hpp"

#include <userver/components/component_list.hpp>

namespace views::Register {

handler::handler(const userver::components::ComponentConfig &cfg,
                 const userver::components::ComponentContext &ctx)
    : uopenapi::components::openapi_handler<Request, Response200, Response400>(
          cfg, ctx),
      pg_cluster_(ctx.FindComponent<userver::components::Postgres>("users_manager_db")
                      .GetCluster()) {}

handler::response handler::handle(views::Register::Request req) const {

  auto uuid = TryInsertUser(req.body);
  if (uuid) {
    Response200 response200;
    response200().body.token = "test string";
    return response200;
  } else {
    Response400 resp400;
    resp400().body.message = "Username is busy. Use another";
    resp400().body.error_code = model::ErrorCode::username_busy;
    return resp400;
  }
}

std::optional<boost::uuids::uuid> handler::TryInsertUser(const model::identity::UserCredentials &ucreds) const {
  auto pg_result = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, sql::insert_user, ucreds);
  return pg_result.AsOptionalSingleRow<boost::uuids::uuid>();
}

void Append(userver::components::ComponentList &componentList) {
  componentList.Append<handler>();
}
} // namespace views::Register
