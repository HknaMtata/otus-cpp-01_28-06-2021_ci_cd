#include <gtest/gtest.h>
#include <ipv4.h>

TEST(Ipv4Test, Parse)
{
    ASSERT_NO_THROW(Ipv4("1.2.3.4"));
    ASSERT_NO_THROW(Ipv4("0.0.0.0"));
    ASSERT_NO_THROW(Ipv4("255.255.255.255"));
    ASSERT_NO_THROW(Ipv4("001.002.003.004"));

    const Ipv4 ip("1.2.3.4");
    ASSERT_EQ(ip.ip, 16909060);

    ASSERT_THROW(Ipv4("ddd"), std::runtime_error);
    ASSERT_THROW(Ipv4("256.256.256.256"), std::runtime_error);
    ASSERT_THROW(Ipv4("1111.1111.1111.1111"), std::runtime_error);
}

TEST(Ipv4Test, Serialize)
{
    const std::string ip_str = "11.111.22.222";

    const Ipv4 ip(ip_str);

    std::stringstream ss;
    ss << ip;

    ASSERT_EQ(ss.str(), ip_str);
}

TEST(Ipv4Test, Comparison)
{
    ASSERT_TRUE(Ipv4("1.2.2.2") < Ipv4("2.2.2.2"));
    ASSERT_TRUE(Ipv4("1.1.1.2") < Ipv4("1.1.2.2"));
    ASSERT_TRUE(Ipv4("2.2.2.2") > Ipv4("1.1.1.1"));
    ASSERT_TRUE(Ipv4("1.1.1.2") > Ipv4("1.1.1.1"));
    ASSERT_FALSE(Ipv4("1.2.3.4") > Ipv4("1.2.3.4"));
    ASSERT_FALSE(Ipv4("1.2.3.4") < Ipv4("1.2.3.4"));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}