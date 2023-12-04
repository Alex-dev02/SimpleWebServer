#pragma once
#include <string>
#include <unordered_map>

class HttpParser {
public:
			
private:
	std::string m_requestType;
	std::string m_path;
	std::string m_version;
    std::unordered_map<std::string, std::string> m_queryParams;
};
