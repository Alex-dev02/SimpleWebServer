#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class Utils {
   public:
    static std::vector<std::string> Split(const std::string& string, char delimiter);
    static std::unordered_map<std::string, std::string> SeparateVectorOfKeysAndValues(const std::vector<std::string>& keyAndValues, char delimiter);
};
