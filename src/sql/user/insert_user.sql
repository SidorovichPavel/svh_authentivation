INSERT INTO SVH_USERS_MANAGER.USERS (
    FIRST_NAME,
    LAST_NAME,
    AGE,
    NICKNAME,
    PASSWORD_HASH,
    SALT
) VALUES (
    $1.FIRST_NAME,
    $1.LAST_NAME,
    $1.AGE,
    $1.NICKNAME,
    $2,
    $3
) RETURNING ID
