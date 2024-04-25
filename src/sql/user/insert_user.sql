INSERT INTO svh_users_manager.users (first_name, last_name, nickname, password_hash, age)
VALUES ($1.first_name, $1.last_name, $1.nickname, $1.password_hash, $1.age)
RETURNING id