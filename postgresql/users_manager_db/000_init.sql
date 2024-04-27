-- Database generated with pgModeler (PostgreSQL Database Modeler).
-- pgModeler version: 1.1.2
-- PostgreSQL version: 16.0
-- Project Site: pgmodeler.io
-- Model Author: ---

-- Database creation must be performed outside a multi lined SQL file. 
-- These commands were put in this file only as a convenience.
-- 
-- object: db | type: DATABASE --
-- DROP DATABASE IF EXISTS db;
-- CREATE DATABASE db;
-- ddl-end --

CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

-- object: svh_users_manager | type: SCHEMA --
DROP SCHEMA IF EXISTS svh_users_manager CASCADE;
CREATE SCHEMA svh_users_manager;
-- ddl-end --

SET search_path TO pg_catalog,public,svh_users_manager;
-- ddl-end --

-- object: svh_users_manager.users | type: TABLE --
DROP TABLE IF EXISTS svh_users_manager.users CASCADE;
CREATE TABLE svh_users_manager.users (
	id uuid NOT NULL DEFAULT uuid_generate_v4(),
	first_name text NOT NULL,
	last_name text NOT NULL,
	nickname text NOT NULL,
	age bigint NOT NULL,
	password_hash text NOT NULL,
	salt text NOT NULL,
	CONSTRAINT users_pk PRIMARY KEY (id),
	CONSTRAINT unique_nickname UNIQUE (nickname)
);
-- ddl-end --

-- object: svh_users_manager."UserCredentialsType" | type: TYPE --
DROP TYPE IF EXISTS svh_users_manager."UserCredentialsType" CASCADE;
CREATE TYPE svh_users_manager."UserCredentialsType" AS
(
 first_name text,
 last_name text,
 age bigint,
 nickname text,
 password_hash text
);
-- ddl-end --

-- object: svh_users_manager.permitions | type: TABLE --
DROP TABLE IF EXISTS svh_users_manager.permitions CASCADE;
CREATE TABLE svh_users_manager.permitions (
	id integer NOT NULL,
	title text NOT NULL,
	CONSTRAINT permitions_pk PRIMARY KEY (id)
);
-- ddl-end --

-- object: svh_users_manager.permitions_to_users | type: TABLE --
DROP TABLE IF EXISTS svh_users_manager.permitions_to_users CASCADE;
CREATE TABLE svh_users_manager.permitions_to_users (
	id_users uuid,
	id_permitions integer

);
-- ddl-end --

-- object: users_fk | type: CONSTRAINT --
ALTER TABLE svh_users_manager.permitions_to_users DROP CONSTRAINT IF EXISTS users_fk CASCADE;
ALTER TABLE svh_users_manager.permitions_to_users ADD CONSTRAINT users_fk FOREIGN KEY (id_users)
REFERENCES svh_users_manager.users (id) MATCH FULL
ON DELETE SET NULL ON UPDATE CASCADE;
-- ddl-end --

-- object: permitions_fk | type: CONSTRAINT --
ALTER TABLE svh_users_manager.permitions_to_users DROP CONSTRAINT IF EXISTS permitions_fk CASCADE;
ALTER TABLE svh_users_manager.permitions_to_users ADD CONSTRAINT permitions_fk FOREIGN KEY (id_permitions)
REFERENCES svh_users_manager.permitions (id) MATCH FULL
ON DELETE SET NULL ON UPDATE CASCADE;
-- ddl-end --


