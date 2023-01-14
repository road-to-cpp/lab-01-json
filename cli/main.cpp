#include <json/json.hpp>
#include <cstdlib>
#include <filesystem>

int main() {
    std::string json = R"(
{
    "name": "John Doe",
    "age": 43,
    "address": {
        "street": "10 Downing Street",
        "city": "London"
    },
    "phone_numbers": [
        "+44 1234567",
        "+44 2345678"
    ]
}
)";
    auto value = json_value::parse_json(json);
    std::cout << value.get_object().at("name").get_string() << std::endl;

    std::cout << json_value::dump_json(4, value) << std::endl;

    auto data_path = std::getenv("DATA_PATH");
    if (data_path == nullptr) {
        throw std::runtime_error("DATA_PATH environment variable is not set");
    }
    auto value2 = json_value::parse_json(std::filesystem::path(data_path) / "json_test.json");
    std::cout << json_value::dump_json(4, value2) << std::endl;
}
