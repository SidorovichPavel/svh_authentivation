-- Database generated with pgModeler (PostgreSQL Database Modeler).
-- pgModeler version: 1.1.2
-- PostgreSQL version: 12.0
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
	password_hash text NOT NULL,
	age bigint NOT NULL,
	CONSTRAINT users_pk PRIMARY KEY (id)
);
-- ddl-end --

-- object: svh_users_manager."UserCredentialsType" | type: TYPE --
DROP TYPE IF EXISTS svh_users_manager."UserCredentialsType" CASCADE;
CREATE TYPE svh_users_manager."UserCredentialsType" AS
(
 first_name text,
 last_name text,
 nickname text,
 password_hash text,
 age bigint
);
-- ddl-end --