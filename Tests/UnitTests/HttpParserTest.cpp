#include <gtest/gtest.h>
#include <Http/HttpParser.hpp>

TEST(HttpParserTest, ExtractRequestLineFromRequest) {
	HttpParser parser("GET /index.html?param1=value1&param2=value2 HTTP/1.1\r\n");

	// // Test case 1: Valid request string
	// parser.ExtractRequestLineFromRequest(request1);
	// ASSERT_EQ(parser.GetRequestType(), "GET");
	// ASSERT_EQ(parser.GetPath(), "/index.html");
	// ASSERT_EQ(parser.GetVersion(), "HTTP/1.1");
	// ASSERT_EQ(parser.GetQueryParams().size(), 2);
	// ASSERT_EQ(parser.GetQueryParams()["param1"], "value1");
	// ASSERT_EQ(parser.GetQueryParams()["param2"], "value2");

	// // Test case 2: Request string with no query parameters
	// std::string request2 = "POST /login HTTP/1.1\r\n";
	// parser.ExtractRequestLineFromRequest(request2);
	// ASSERT_EQ(parser.GetRequestType(), "POST");
	// ASSERT_EQ(parser.GetPath(), "/login");
	// ASSERT_EQ(parser.GetVersion(), "HTTP/1.1");
	// ASSERT_TRUE(parser.GetQueryParams().empty());

	// // Test case 3: Request string with no version
	// std::string request3 = "PUT /user?id=123\r\n";
	// parser.ExtractRequestLineFromRequest(request3);
	// ASSERT_EQ(parser.GetRequestType(), "PUT");
	// ASSERT_EQ(parser.GetPath(), "/user");
	// ASSERT_TRUE(parser.GetVersion().empty());
	// ASSERT_EQ(parser.GetQueryParams().size(), 1);
	// ASSERT_EQ(parser.GetQueryParams()["id"], "123");
}
