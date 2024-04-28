#include "handler.hpp"
#include <codegen/sql.hpp>
#include <jwt-cpp/jwt.h>
#include <userver/components/component_list.hpp>
#include <userver/crypto/base64.hpp>

namespace views::login {
void Append(userver::components::ComponentList &componentList) {
  componentList.Append<handler>();
}

handler::handler(const userver::components::ComponentConfig &cfg,
                 const userver::components::ComponentContext &ctx)
    : base(cfg, ctx),
      pg_cluster_(
          ctx.FindComponent<userver::components::Postgres>("users_manager_db")
              .GetCluster()) {}

handler::response handler::handle(views::login::Request req) const {
  auto auth_data = SelectAuthData(req.body.nickname);
  if (!auth_data) {
    Response400 r400;
    r400().body.message = "User not found";
    r400().body.error_code = model::ErrorCode::invalid_credentials;
    return r400;
  }

  auto salt_hashed_pass = req.body.password_hash + auth_data->salt;
  auto dhashed_pass = userver::crypto::base64::Base64Encode(
      salt_hashed_pass, userver::crypto::base64::Pad::kWithout);
  if (dhashed_pass != auth_data->dhashed_password) {
    Response400 r400;
    r400().body.message = "Invalid password";
    r400().body.error_code = model::ErrorCode::invalid_credentials;
    return r400;
  }

  Response200 response200;
  response200().body.token = MakeToken(*auth_data);
  return response200;
}

std::optional<model::auth::UserAuthCredentials>
handler::SelectAuthData(std::string username) const {
  auto pg_result = pg_cluster_->Execute(
      userver::storages::postgres::ClusterHostType::kMaster, sql::select_auth,
      username);

  return pg_result.AsOptionalSingleRow<model::auth::UserAuthCredentials>(userver::storages::postgres::kRowTag);
}

std::string
handler::MakeToken(const model::auth::UserAuthCredentials &uac) const {
  auto secret = "json+web+" + uac.first_name;
  std::shuffle(secret.begin(), secret.end(), std::random_device{});

  auto token =
      jwt::create()
          .set_type("JWS")
          .set_issuer("svh_auth0")
          .set_payload_claim("id", jwt::claim(boost::uuids::to_string(uac.id)))
          .set_payload_claim("nickname", jwt::claim(uac.nickname))
          .set_payload_claim("age", jwt::claim(std::to_string(uac.age)))
          .sign(jwt::algorithm::hs256{"secret"});

  return std::string(token.c_str());
}

} // namespace views::login
