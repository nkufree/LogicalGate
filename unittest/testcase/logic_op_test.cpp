#include <gtest/gtest.h>
#include "logical_simulator.h"
#include <vector>

using namespace std;

// 测试逻辑门的非操作
TEST(LOGIC_OP_TEST, test_not)
{
    Wire wires[2] = {0};
    vector<int> inputs_one = {0};
    EXPECT_TRUE(LogicOp[NOT](inputs_one, wires));
    wires[0] = 1;
    EXPECT_FALSE(LogicOp[NOT](inputs_one, wires));
    vector<int> inputs_two = {0, 1};
    vector<int> inputs_three = {0, 1, 2};
    vector<int> inputs_four = {0, 1, 2, 3};
}

// 测试逻辑门的与操作
TEST(LOGIC_OP_TEST, test_and)
{
    Wire wires[5] = {0};
    vector<int> inputs_two = {0, 1};
    EXPECT_FALSE(LogicOp[AND](inputs_two, wires));
    wires[0] = 1;
    EXPECT_FALSE(LogicOp[AND](inputs_two, wires));
    wires[1] = 1;
    EXPECT_TRUE(LogicOp[AND](inputs_two, wires));
    vector<int> inputs_three = {0, 1, 2};
    vector<int> inputs_four = {0, 1, 2, 3};
    EXPECT_FALSE(LogicOp[AND](inputs_three, wires));
    EXPECT_FALSE(LogicOp[AND](inputs_four, wires));
    wires[2] = 1;
    EXPECT_TRUE(LogicOp[AND](inputs_three, wires));
    EXPECT_FALSE(LogicOp[AND](inputs_four, wires));
    wires[3] = 1;
    EXPECT_TRUE(LogicOp[AND](inputs_four, wires));
}

// 测试逻辑门的或操作
TEST(LOGIC_OP_TEST, test_or)
{
    Wire wires[5] = {0};
    vector<int> inputs_two = {0, 1};
    EXPECT_FALSE(LogicOp[OR](inputs_two, wires));
    wires[0] = 1;
    EXPECT_TRUE(LogicOp[OR](inputs_two, wires));
    wires[1] = 1;
    EXPECT_TRUE(LogicOp[OR](inputs_two, wires));
    vector<int> inputs_three = {0, 1, 2};
    vector<int> inputs_four = {0, 1, 2, 3};
    EXPECT_TRUE(LogicOp[OR](inputs_three, wires));
    EXPECT_TRUE(LogicOp[OR](inputs_four, wires));
    wires[2] = 1;
    EXPECT_TRUE(LogicOp[OR](inputs_three, wires));
    EXPECT_TRUE(LogicOp[OR](inputs_four, wires));
    wires[3] = 1;
    EXPECT_TRUE(LogicOp[OR](inputs_four, wires));
}

// 测试逻辑门的异或操作
TEST(LOGIC_OP_TEST, test_xor)
{
    Wire wires[5] = {0};
    vector<int> inputs_two = {0, 1};
    EXPECT_FALSE(LogicOp[XOR](inputs_two, wires));
    wires[0] = 1;
    EXPECT_TRUE(LogicOp[XOR](inputs_two, wires));
    wires[1] = 1;
    EXPECT_FALSE(LogicOp[XOR](inputs_two, wires));
    vector<int> inputs_three = {0, 1, 2};
    vector<int> inputs_four = {0, 1, 2, 3};
    EXPECT_FALSE(LogicOp[XOR](inputs_three, wires));
    EXPECT_FALSE(LogicOp[XOR](inputs_four, wires));
    wires[2] = 1;
    EXPECT_TRUE(LogicOp[XOR](inputs_three, wires));
    EXPECT_TRUE(LogicOp[XOR](inputs_four, wires));
    wires[3] = 1;
    EXPECT_FALSE(LogicOp[XOR](inputs_four, wires));
}

// 测试逻辑门的与非操作
TEST(LOGIC_OP_TEST, test_nand)
{
    Wire wires[5] = {0};
    vector<int> inputs_two = {0, 1};
    EXPECT_TRUE(LogicOp[NAND](inputs_two, wires));
    wires[0] = 1;
    EXPECT_TRUE(LogicOp[NAND](inputs_two, wires));
    wires[1] = 1;
    EXPECT_FALSE(LogicOp[NAND](inputs_two, wires));
    vector<int> inputs_three = {0, 1, 2};
    vector<int> inputs_four = {0, 1, 2, 3};
    EXPECT_TRUE(LogicOp[NAND](inputs_three, wires));
    EXPECT_TRUE(LogicOp[NAND](inputs_four, wires));
    wires[2] = 1;
    EXPECT_FALSE(LogicOp[NAND](inputs_three, wires));
    EXPECT_TRUE(LogicOp[NAND](inputs_four, wires));
    wires[3] = 1;
    EXPECT_FALSE(LogicOp[NAND](inputs_four, wires));
}

// 测试逻辑门的或非操作
TEST(LOGIC_OP_TEST, test_nor)
{
    Wire wires[5] = {0};
    vector<int> inputs_two = {0, 1};
    EXPECT_TRUE(LogicOp[NOR](inputs_two, wires));
    wires[0] = 1;
    EXPECT_FALSE(LogicOp[NOR](inputs_two, wires));
    wires[1] = 1;
    EXPECT_FALSE(LogicOp[NOR](inputs_two, wires));
    vector<int> inputs_three = {0, 1, 2};
    vector<int> inputs_four = {0, 1, 2, 3};
    EXPECT_FALSE(LogicOp[NOR](inputs_three, wires));
    EXPECT_FALSE(LogicOp[NOR](inputs_four, wires));
    wires[2] = 1;
    EXPECT_FALSE(LogicOp[NOR](inputs_three, wires));
    EXPECT_FALSE(LogicOp[NOR](inputs_four, wires));
    wires[3] = 1;
    EXPECT_FALSE(LogicOp[NOR](inputs_four, wires));
}