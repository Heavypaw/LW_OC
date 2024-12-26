#include <gtest/gtest.h>
#include "ControlNode.h"

class DistributedSystemTest : public ::testing::Test {
protected:
    ControlNode* control;

    void SetUp() override {
        control = new ControlNode();
        control->create_node(10, -1);
    }

    void TearDown() override {
        delete control;
    }
};

TEST_F(DistributedSystemTest, CreateNode) {
    testing::internal::CaptureStdout();
    control->create_node(20, 10);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(output.find("Ok: 20 created") != std::string::npos);
}

TEST_F(DistributedSystemTest, ExecCommand) {
    control->exec_command(10, "start");
    testing::internal::CaptureStdout();
    control->exec_command(10, "time");
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(output.find("Ok:10 Time:") != std::string::npos);
}

TEST_F(DistributedSystemTest, Heartbit) {
    testing::internal::CaptureStdout();
    control->heartbit(1000);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(output.find("Heartbit: Ok") != std::string::npos);
}
