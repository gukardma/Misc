-- create database
CREATE DATABASE funtimes;

CREATE TABLE users (
    `id` INT NOT NULL AUTO_INCREMENT,
    `username` VARCHAR(255) NOT NULL,
    `pwd` VARCHAR(255) NOT NULL,
    `email` VARCHAR(255) NOT NULL UNIQUE,
    `created_at` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (`id`)
);

{
-- INSERT INTO users (username, pwd, email) VALUES ('Gucci','password', 'fake@gmail.com');
}