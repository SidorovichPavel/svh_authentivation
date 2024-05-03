#pragma once

#include <boost/uuid/uuid.hpp>
#include <models/auth.hpp>
#include <models/error_response.hpp>
#include <models/identity.hpp>
#include <uopenapi/http/response.hpp>

namespace views::Register {

using Request = model::identity::Request;

using Response200 = uopenapi::http::response<model::identity::Response, 200>;
using Response400 = uopenapi::http::response<model::ErrorResponse, 400>;
} // namespace views::Register
