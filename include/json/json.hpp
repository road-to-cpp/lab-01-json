//
// Created by mrmamongo on 14.01.23.
//

#ifndef JSON_JSON_HPP
#define JSON_JSON_HPP

#include <iostream>
#include <utility>
#include <variant>
#include <vector>
#include <map>
#include <filesystem>
#include <fstream>


class unexpected_token_error : public std::exception {
public:
    unexpected_token_error(std::string token) : token(std::move(token)) {}

    [[nodiscard]] const char *what() const noexcept override {
        return token.c_str();
    }

private:
    std::string token;
};

class unexpected_type_error : public std::exception {
public:
    unexpected_type_error(std::string type) : type(std::move(type)) {}

    [[nodiscard]] const char *what() const noexcept override {
        return type.c_str();
    }

private:
    std::string type;
};

class json_value {
public:
    using object_type = std::map<std::string, json_value>;
    using array_type = std::vector<json_value>;
    using string_type = std::string;
    using number_type = double;
    using boolean_type = bool;
    using null_type = std::nullptr_t;

    enum json_type {
        object,
        array,
        string,
        number,
        boolean,
        null
    };

    ~json_value() = default;

    // Правило пяти
    json_value();

    json_value(const json_value &other) = default;

    json_value(json_value &&other) noexcept = default;

    json_value &operator=(const json_value &other) = default;

    json_value &operator=(json_value &&other) noexcept = default;
    // Правило пяти


    // Конструкторы из объектов
    json_value(object_type object);

    json_value(array_type array);

    json_value(string_type string);

    json_value(number_type number);

    json_value(boolean_type boolean);

    json_value(null_type null);
    // Конструкторы из объектов


    // Получение типа значения
    [[nodiscard]] json_type get_type() const;


    // Получение объектов
    [[nodiscard]] object_type &get_object();

    [[nodiscard]]  array_type &get_array();

    [[nodiscard]]  string_type &get_string();

    [[nodiscard]] number_type get_number();

    [[nodiscard]] boolean_type get_boolean();

    [[nodiscard]] null_type get_null();

    [[nodiscard]] const object_type &get_object() const;

    [[nodiscard]] const array_type &get_array() const;

    [[nodiscard]] const string_type &get_string() const;

    [[nodiscard]] number_type get_number() const;

    [[nodiscard]] boolean_type get_boolean() const;

    [[nodiscard]] null_type get_null() const;
    // Получение объектов

    // Операторы для объектов и массивов
    json_value &operator[](const std::string &key);

    json_value &operator[](int index);

    json_value &operator[](size_t index);

    [[nodiscard]] const json_value &operator[](const std::string &key) const;

    [[nodiscard]] const json_value &operator[](int index) const;

    [[nodiscard]] const json_value &operator[](size_t index) const;
    // Операторы для объектов и массивов

    // Статические методы для парсинга и дампа
    static json_value parse_json(std::string json);

    static std::string dump_json(int indent = 0, const json_value &value = json_value());

    static json_value parse_json(const std::filesystem::path &path);
    // Статические методы для парсинга и дампа
private:
    std::variant<object_type, array_type, string_type, number_type, boolean_type, null_type> _value;
};


#endif //JSON_JSON_HPP
