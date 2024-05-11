#include <gtest/gtest.h>
#include "logical_simulator.h"

using namespace std;

// 测试一个简单的用例
TEST(EACH_CASE_TEST, test_simple)
{
    int input_num = 3;
    int gate_num = 5;
    int case_num = 4;
    vector<LogicalGate> gates = {
        {XOR, {0, 1}, 3},
        {XOR, {3, 2}, 4},
        {AND, {3, 2}, 5},
        {AND, {0, 1}, 6},
        {OR, {5, 6}, 7}};
    vector<vector<int>> input_cases = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 1},
        {0, 0, 0}};
    vector<vector<int>> show_cases = {
        {4, 1},
        {4, 1},
        {4, 1},
        {4, 1}};
    vector<vector<int>> output_cases = {
        {1, 0},
        {1, 0},
        {1, 1},
        {0, 0}};
    vector<int> search_sequence = {0, 1, 2, 3, 4};
    unordered_map<int, int> search_sequence_map = {
        {0, 0},
        {1, 1},
        {2, 2},
        {3, 3},
        {4, 4}};
    map<vector<int>, int> seq_max_map;
    stringstream task_output;
    EachCase(gates, input_cases[0], show_cases[0], input_num, gate_num, search_sequence, search_sequence_map, seq_max_map, task_output);
    ASSERT_EQ(seq_max_map.size(), 1);
    EachCase(gates, input_cases[1], show_cases[1], input_num, gate_num, search_sequence, search_sequence_map, seq_max_map, task_output);
    ASSERT_EQ(seq_max_map.size(), 1);
    EachCase(gates, input_cases[2], show_cases[2], input_num, gate_num, search_sequence, search_sequence_map, seq_max_map, task_output);
    ASSERT_EQ(seq_max_map.size(), 1);
    EachCase(gates, input_cases[3], show_cases[3], input_num, gate_num, search_sequence, search_sequence_map, seq_max_map, task_output);
    ASSERT_EQ(seq_max_map.size(), 1);
    for (int i = 0; i < case_num; i++)
    {
        int a, b;
        task_output >> a >> b;
        ASSERT_EQ(a, output_cases[i][0]);
        ASSERT_EQ(b, output_cases[i][1]);
    }
}