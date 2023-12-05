#include "Utils.hpp"

std::vector<std::string> Utils::split(const std::string& text, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;

    for (const auto& elem : text) {
        if (elem == delimiter) {
            tokens.emplace_back(token);
            token.clear();
        } else {
            token += elem;
        }
    }
    tokens.emplace_back(token);
    
    return tokens;
}

std::unordered_map<std::string, std::string> Utils::separateVectorOfKeysAndValues(const std::vector<std::string>& keyAndValues, char delimiter) {
	std::unordered_map<std::string, std::string> keyAndValuesSeparated;

	for (const auto& keyAndValue : keyAndValues) {
		std::vector<std::string> tokens = Utils::split(keyAndValue, delimiter);
		keyAndValuesSeparated[tokens[0]] = tokens[1];
	}

	return keyAndValuesSeparated;
}
