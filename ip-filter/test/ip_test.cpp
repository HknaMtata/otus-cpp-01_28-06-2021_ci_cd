#include <gtest/gtest.h>
#include <ipv4.h>

TEST(Ipv4, Comparison)
{
    ASSERT_TRUE(Ipv4("1.2.3.4") > Ipv4("1.1.3.4"));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}