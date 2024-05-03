#pragma once

#include <boost/uuid/uuid.hpp>
#include <models/auth.hpp>
#include <models/error_response.hpp>
#include <uopenapi/http/response.hpp>

namespace views::login {

using Request = model::auth::Request;

using Response200 = uopenapi::http::response<model::auth::Response, 200>;
using Response400 = uopenapi::http::response<model::ErrorResponse, 400>;

} // namespace views::login
