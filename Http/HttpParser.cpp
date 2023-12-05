#include "HttpParser.hpp"

#include <Utils/Utils.hpp>

HttpParser::HttpParser(const std::string& request) {
}

void HttpParser::extractRequestLineFromRequest(const std::string& request) {
    std::vector<std::string> tokens = Utils::split(request, '\r\n');
    std::vector<std::string> firstLineTokens = Utils::split(tokens[0], ' ');
    std::vector<std::string> pathAndParams = Utils::split(firstLineTokens[1], '?');
    std::vector<std::string> paramsAndValues = Utils::split(pathAndParams[1], '&');

    m_requestType = firstLineTokens[0];
    m_path = pathAndParams[0];
    m_version = Utils::split(firstLineTokens[2], '/')[1];
    m_queryParams = Utils::separateVectorOfKeysAndValues(paramsAndValues, '=');
}