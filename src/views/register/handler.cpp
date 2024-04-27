#include "handler.hpp"

#include "../../codegen/sql.hpp"

#include <jwt-cpp/jwt.h>
#include <userver/components/component_list.hpp>
#include <userver/crypto/base64.hpp>

namespace views::Register {

handler::handler(const userver::components::ComponentConfig &cfg,
                 const userver::components::ComponentContext &ctx)
    : uopenapi::components::openapi_handler<Request, Response200, Response400>(
          cfg, ctx),
      pg_cluster_(
          ctx.FindComponent<userver::components::Postgres>("users_manager_db")
              .GetCluster()) {}

handler::response handler::handle(views::Register::Request req) const {

  auto uuid = TryInsertUser(req.body);
  if (uuid) {
    Response200 response200;
    response200().body.token = MakeToken(*uuid, req.body);
    return response200;
  } else {
    Response400 resp400;
    resp400().body.message = "Username is busy. Use another";
    resp400().body.error_code = model::ErrorCode::username_busy;
    return resp400;
  }
}

std::optional<boost::uuids::uuid>
handler::TryInsertUser(const model::identity::UserCredentials &ucreds) const {
  constexpr size_t salt_size = 10u;
  auto salt = userver::crypto::base64::Base64Encode(
                  ucreds.nickname, userver::crypto::base64::Pad::kWith)
                  .substr(0, salt_size);

  auto salt_pass_hash = ucreds.password_hash + salt;
  auto double_hashed_pass = userver::crypto::base64::Base64Encode(
      salt_pass_hash, userver::crypto::base64::Pad::kWithout);

  auto pg_result = pg_cluster_->Execute(
      userver::storages::postgres::ClusterHostType::kMaster, sql::insert_user,
      ucreds, double_hashed_pass, salt);
  return pg_result.AsOptionalSingleRow<boost::uuids::uuid>();
}

std::string
handler::MakeToken(const boost::uuids::uuid &uuid,
                   const model::identity::UserCredentials uc) const {
  auto token =
      jwt::create()
          .set_type("JWS")
          .set_issuer("svh_auth0")
          .set_payload_claim("id", jwt::claim(boost::uuids::to_string(uuid)))
          .set_payload_claim("nickname", jwt::claim(uc.nickname))
          .set_payload_claim("age", jwt::claim(std::to_string(uc.age)))
          .sign(jwt::algorithm::hs256{"secret"});
  return std::string(token.c_str());
}

void Append(userver::components::ComponentList &componentList) {
  componentList.Append<handler>();
}
} // namespace views::Register
