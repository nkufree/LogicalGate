#include <gtest/gtest.h>
#include "logical_simulator.h"
#include <vector>

using namespace std;

// 测试正常情况
TEST(GENERATE_GATE_TEST, test_usual)
{
    int input_num = 2;
    int gate_num = 8;
    vector<vector<int>> graph(8);
    vector<LogicalGate> gates;
    string inputs[] = {
        "AND 2 I1 I2",
        "OR 3 I1 I2 O1",
        "NOT 1 O2",
        "NAND 3 O1 O2 O3",
        "XOR 3 O1 O2 O4",
        "NOR 4 O3 O4 O5 O1",
        "AND 3 O5 I1 O6",
        "OR 3 O6 I2 O7"};
    vector<LogicalGate> gates_standard = {
        {AND, {0, 1}, 2},
        {OR, {0, 1, 2}, 3},
        {NOT, {3}, 4},
        {NAND, {2, 3, 4}, 5},
        {XOR, {2, 3, 5}, 6},
        {NOR, {4, 5, 6, 2}, 7},
        {AND, {6, 0, 7}, 8},
        {OR, {7, 1, 8}, 9}};
    vector<vector<int>> graph_standard = {
        {1, 3, 4, 5},
        {2, 3, 4},
        {3, 5},
        {4, 5},
        {5, 6},
        {6, 7},
        {7},
        {}};
    for (int i = 0; i < gate_num; i++)
    {
        LogicalGate gate = GenerateGate(inputs[i], i, input_num, gate_num, graph);
        gates.push_back(gate);
    }
    for (int i = 0; i < gate_num; i++)
    {
        EXPECT_EQ(gates[i].type, gates_standard[i].type);
        EXPECT_EQ(gates[i].inputs, gates_standard[i].inputs);
        EXPECT_EQ(gates[i].output, gates_standard[i].output);
    }
    for (int i = 0; i < gate_num; i++)
    {
        EXPECT_EQ(graph[i], graph_standard[i]);
    }
}

// 测试错误的逻辑门类型
TEST(GENERATE_GATE_TEST, test_error_gate_type)
{
    int input_num = 2;
    int gate_num = 1;
    vector<vector<int>> graph(1);
    string inputs[] = {
        "ADD 2 I1 I2"};
    EXPECT_THROW(GenerateGate(inputs[0], 0, input_num, gate_num, graph), invalid_argument);
}

// 测试错误的输入编号
TEST(GENERATE_GATE_TEST, test_error_input_index)
{
    int input_num = 2;
    int gate_num = 1;
    vector<vector<int>> graph(1);
    string inputs[] = {
        "AND 3 I1 I3"};
    EXPECT_THROW(GenerateGate(inputs[0], 0, input_num, gate_num, graph), invalid_argument);
}

// 测试错误的输出编号
TEST(GENERATE_GATE_TEST, test_error_output_index)
{
    int input_num = 2;
    int gate_num = 1;
    vector<vector<int>> graph(1);
    string inputs[] = {
        "AND 3 I1 O2"};
    EXPECT_THROW(GenerateGate(inputs[0], 0, input_num, gate_num, graph), invalid_argument);
}

// 测试与门错误的输入个数
TEST(GENERATE_GATE_TEST, test_error_input_num_and)
{
    int input_num = 2;
    int gate_num = 1;
    vector<vector<int>> graph(1);
    string inputs[] = {
        "AND 1 I1"};
    EXPECT_THROW(GenerateGate(inputs[0], 0, input_num, gate_num, graph), invalid_argument);
}

// 测试或门错误的输入个数
TEST(GENERATE_GATE_TEST, test_error_input_num_or)
{
    int input_num = 2;
    int gate_num = 1;
    vector<vector<int>> graph(1);
    string inputs[] = {
        "OR 1 I1"};
    EXPECT_THROW(GenerateGate(inputs[0], 0, input_num, gate_num, graph), invalid_argument);
}

// 测试非门错误的输入个数
TEST(GENERATE_GATE_TEST, test_error_input_num_not)
{
    int input_num = 2;
    int gate_num = 1;
    vector<vector<int>> graph(1);
    string inputs[] = {
        "NOT 2 I1 I2"};
    EXPECT_THROW(GenerateGate(inputs[0], 0, input_num, gate_num, graph), invalid_argument);
}

// 测试与非门错误的输入个数
TEST(GENERATE_GATE_TEST, test_error_input_num_nand)
{
    int input_num = 2;
    int gate_num = 1;
    vector<vector<int>> graph(1);
    string inputs[] = {
        "NAND 1 I1"};
    EXPECT_THROW(GenerateGate(inputs[0], 0, input_num, gate_num, graph), invalid_argument);
}

// 测试或非门错误的输入个数
TEST(GENERATE_GATE_TEST, test_error_input_num_nor)
{
    int input_num = 2;
    int gate_num = 1;
    vector<vector<int>> graph(1);
    string inputs[] = {
        "NOR 1 I1"};
    EXPECT_THROW(GenerateGate(inputs[0], 0, input_num, gate_num, graph), invalid_argument);
}

// 测试异或门错误的输入个数
TEST(GENERATE_GATE_TEST, test_error_input_num_xor)
{
    int input_num = 2;
    int gate_num = 1;
    vector<vector<int>> graph(1);
    string inputs[] = {
        "XOR 1 I1"};
    EXPECT_THROW(GenerateGate(inputs[0], 0, input_num, gate_num, graph), invalid_argument);
}

// 测试错误的输入格式
TEST(GENERATE_GATE_TEST, test_error_input_format)
{
    int input_num = 2;
    int gate_num = 1;
    vector<vector<int>> graph(1);
    string inputs[] = {
        "XOR 1 M1"};
    EXPECT_THROW(GenerateGate(inputs[0], 0, input_num, gate_num, graph), invalid_argument);
}