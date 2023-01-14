# Задание 1
Реализовать парсер данных в формате JSON.

JSON-текст представляет собой в закодированном виде одну из двух структур:
- Объект - это неупорядоченное множество пар ```ключ:значение```, разделяемых запятыми. Всё множество заключается в фигурные скобки ```{}```. Ключом может быть только регистрозависимая строка. Значением может быть объект, массив, число, литералы (```true, false, null```) или строка;
- Массив - это упорядоченное множество значений. Массив заключается в квадратные скобки ```[]```, а значения разделяются запятыми.

Пример входных данных в формате JSON:
```json
{
    "lastname" : "Ivanov",
    "firstname" : "Ivan",
    "age" : 25,
    "islegal" : false,
    "marks" : [
    	4,5,5,5,2,3
    ],
    "address" : {
    	"city" : "Moscow",
        "street" : "Vozdvijenka"
    }
}
```
Более подробное описание формата можно найти по ссылке [json.org](http://json.org/). Необходимо будет пояснить выбор одного из них.

За основу необходимо взять следующий интерфейс (файл ```include/json.hpp```):
```cpp
class json_value {
public:
    ...

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
    ...
};
```
Таким образом объект класса ```Json``` может являться либо Json-объектом, либо Json-массивом и может хранить в себе вложенные объекты класса ```Json```.

Класс ```Json``` должен проходить unit-тесты из файла ```tests/test.cpp``` на json-данных, приведённых выше:

```cpp
std::string json = <json-строка из примера выше>;

json_value object = json_value::parse_json(json);
EXPECT_EQ(object["lastname"].get_string(), "Ivanov");
EXPECT_EQ(object["islegal"].get_boolean(), false);
EXPECT_EQ(object["age"].get_integer(), 25);

auto marks = object["marks"].get_object();
EXPECT_EQ(marks[0].get_integer(), 4);
EXPECT_EQ(marks[1].get_integer(), 5);

auto address = object["address"].get_object();
EXPECT_EQ(address["city"].get_string(), "Moscow");
EXPECT_EQ(address["street"].get_string(), "Vozdvijenka");
```

# Задание 2
На вход программы поступает информация о биржевых инструментах (массив тикеров, массив идентификаторов и массив описаний) в формате JSON вида:
```json
[
    ["Si-9.15", "RTS-9.15", "GAZP-9.15"],
    [100024, 100027, 100050],
    ["Futures contract for USD/RUB", "Futures contract for index RTS", "Futures contract for Gazprom shares"]
]
```
Необходимо выполнить преобразование данных в более удобный для анализа формат:
```json
[
    {"ticker":"Si-9.15", "id": 100024, "description": "Futures contract for USD/RUB"},
    {"ticker":"RTS-9.15", "id": 100027, "description": "Futures contract for index RTS"},
    {"ticker":"GAZP-9.15", "id": 100050, "description": "Futures contract for GAZPROM shares"}
]
```

# Задание 3

В папке ```data``` находится файл ```users.json```. Данный файл представляет собой дамп из базы данных пользователей. Необходимо распределить пользователей по

```json
{
  "status": "OK",
  "code": 200,
  "total": 1000,
  "data": [
    {
      "uuid": "a0eebc99-9c0b-4ef8-bb6d-6bb9bd380a11",
      "first_name": "John",
      "last_name": "Doe",
      "birthday": "1990-11-15",
      "city": "Moscow",
      "country": "Russia"
    },
    ...
  ]
}
```
Для этого требуется использовать любую популярную библиотеку для работы с форматом данных JSON на C++ (например [JSON for Modern C++](https://docs.hunter.sh/en/latest/packages/pkg/nlohmann_json.html), [RapidJSON](https://github.com/Tencent/rapidjson)).
После чего необходимо воспользоваться собственной библиотекой и сравнить показатели скорости

Получать показатели скорости можно с помощью утилиты ```time```. Например, для сравнения скорости работы программы с использованием библиотеки ```nlohmann_json``` и ```rapidjson``` можно воспользоваться следующими командами:

```bash
time ./nlohmann_json
time ./rapidjson
time ./custom_json
```

После этого необходимо будет построить графики сравнения зависимости времени работы от размера файла ```users.json```. Для этого можно воспользоваться утилитой ```gnuplot```. Например, для построения графика зависимости времени работы от выбранного параметра ```nlohmann_json```, ```rapidjson``` или ```custom_json``` можно воспользоваться следующими командами:

```bash
gnuplot
gnuplot> set xlabel "Size of file"
gnuplot> set ylabel "Time"
gnuplot> plot "nlohmann_json.dat" with lines, "rapidjson.dat" with lines, "custom_json.dat" with lines
```
## Результаты

Сюда необходимо прикрепить результаты

### Дополнительное задание

Разобраться, почему один из парсеров настолько быстрее других. (Оба проекта - опенсорс)
