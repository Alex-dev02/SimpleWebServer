#include "HttpParser.hpp"

#include <Utils/Utils.hpp>

HttpParser::HttpParser(const std::string& request) {
}

void HttpParser::ExtractRequestLineFromRequest(const std::string& request) {
    std::vector<std::string> lines = Utils::Split(request, '\r\n'); // FIXME: _|_
    std::vector<std::string> firstLineTokens = Utils::Split(lines[0], ' ');
    std::vector<std::string> pathAndParams = Utils::Split(firstLineTokens[1], '?');
    std::vector<std::string> paramsAndValues = Utils::Split(pathAndParams[1], '&');

    m_requestType = firstLineTokens[0];
    m_path = pathAndParams[0];
    m_version = Utils::Split(firstLineTokens[2], '/')[1];
    m_queryParams = Utils::SeparateVectorOfKeysAndValues(paramsAndValues, '=');
}
