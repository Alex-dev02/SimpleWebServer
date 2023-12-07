#include <gtest/gtest.h>
#include <Http/HttpParser.hpp>

TEST(HttpParserTest, ExtractHttpVerbFromRequest) {
	HttpParser parser("GET /index.html?param1=value1&param2=value2 HTTP/1.1\r\n");

	EXPECT_EQ("GET", parser.GetRequestType());
}
