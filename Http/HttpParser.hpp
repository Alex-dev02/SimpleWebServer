#pragma once
#include <string>
#include <unordered_map>
#include <iostream>

class HttpParser {
public:
	HttpParser(const std::string& request);

private:
	std::string m_requestType;
	std::string m_path;
	std::string m_version;
    std::unordered_map<std::string, std::string> m_queryParams;

	void ExtractRequestLineFromRequest(const std::string& request);
};
