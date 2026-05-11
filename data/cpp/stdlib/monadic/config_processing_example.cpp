#include <iostream>
#include <expected>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

struct Config {
    int port;
    std::string host;
};

std::expected<Config, std::string> parse_config(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return std::unexpected("Не удалось открыть файл конфигурации");
    }

    std::map<std::string, std::string> config_map;
    std::string line;
    while (std::getline(file, line)) {
        size_t delimiter_pos = line.find('=');
        if (delimiter_pos != std::string::npos) {
            std::string key = line.substr(0, delimiter_pos);
            std::string value = line.substr(delimiter_pos + 1);
            config_map[key] = value;
        }
    }

    if (!config_map.contains("port") || !config_map.contains("host")) {
        return std::unexpected("Отсутствуют обязательные параметры в конфигурации");
    }

    try {
        int port = std::stoi(config_map["port"]);
        return Config{port, config_map["host"]};
    } catch (...) {
        return std::unexpected("Некорректное значение порта");
    }
}

std::expected<std::string, std::string> validate_config(const Config& config) {
    if (config.port < 0 || config.port > 65535) {
        return std::unexpected("Некорректный порт");
    }
    if (config.host.empty()) {
        return std::unexpected("Пустой хост");
    }
    return "Конфигурация корректна";
}

int main() {
    auto result = parse_config("config.txt")
        .and_then(validate_config)
        .transform_error([](const std::string& error) {
            return "Ошибка конфигурации: " + error;
        });

    if (result) {
        std::cout << *result << std::endl;
    } else {
        std::cerr << result.error() << std::endl;
    }

    return 0;
}
