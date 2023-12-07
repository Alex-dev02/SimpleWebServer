#include <gtest/gtest.h>

#include <Networking/TcpListener.hpp>

TEST(NetworkingTest, TcpListenerAcceptClient) {

    TcpListener listener(5000, 10);
    listener.Start();

    
}
