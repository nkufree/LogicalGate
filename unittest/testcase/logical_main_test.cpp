#include <gtest/gtest.h>
#include "logical_simulator.h"
#include "./include/graph_generate.h"
#include <vector>

using namespace std;

// 测试简单的任务
TEST(LOGICAL_MAIN_TEST, test_simple_DAG)
{
    string input_str = "1\n"
                       "3 5\n"
                       "XOR 2 I1 I2\n"
                       "XOR 2 O1 I3\n"
                       "AND 2 O1 I3\n"
                       "AND 2 I1 I2\n"
                       "OR 2 O3 O4\n"
                       "4\n"
                       "0 1 1\n"
                       "1 0 1\n"
                       "1 1 1\n"
                       "0 0 0\n"
                       "2 5 2\n"
                       "2 5 2\n"
                       "2 5 2\n"
                       "2 5 2\n";
    int output[] = {1, 0, 1, 0, 1, 1, 0, 0};
    stringstream task_input(input_str);
    stringstream task_output;
    LogicalMain(task_input, task_output);
    ASSERT_TRUE(task_output.str().find("LOOP") == string::npos);
    for (int i = 0; i < 8; i++)
    {
        int tmp;
        task_output >> tmp;
        ASSERT_EQ(tmp, output[i]);
    }
}

// 测试简单的有环任务
TEST(LOGICAL_MAIN_TEST, test_simple_cycle)
{
    string input_str = "1\n"
                       "2 6\n"
                       "NOR 2 O4 I2\n"
                       "AND 2 O4 O6\n"
                       "XOR 2 O5 O1\n"
                       "NOT 1 O6\n"
                       "NAND 2 O2 O2\n"
                       "AND 2 I1 O3\n"
                       "2\n"
                       "0 0\n"
                       "1 0\n"
                       "3 2 3 4\n"
                       "6 1 2 3 4 5 6\n";
    stringstream task_input(input_str);
    stringstream task_output;
    LogicalMain(task_input, task_output);
    ASSERT_TRUE(task_output.str().find("LOOP") != string::npos);
}

// 测试只有无环的多个任务
TEST(LOGICAL_MAIN_TEST, test_only_DAG)
{
    stringstream input;
    srand(time(0));
    int task_num = 3;
    input << task_num << endl;
    for (int i = 0; i < task_num; i++)
    {
        int input_num = rand() % 100 + 50;
        int gate_num = rand() % 100 + 50;
        int case_num = rand() % 100 + 50;
        int unique_output_num = rand() % 10 + 50;
        input << generate_gate_input(input_num, gate_num, false);
        input << generate_test_case(input_num, gate_num, case_num, unique_output_num);
    }
    stringstream output;
    LogicalMain(input, output);
    ASSERT_TRUE(output.str().find("LOOP") == string::npos);
}

// 测试只有有环的多个任务
TEST(LOGICAL_MAIN_TEST, test_only_cycle)
{
    stringstream input;
    srand(time(0));
    int task_num = 3;
    input << task_num << endl;
    for (int i = 0; i < task_num; i++)
    {
        int input_num = rand() % 100 + 50;
        int gate_num = rand() % 100 + 50;
        int case_num = rand() % 100 + 50;
        int unique_output_num = rand() % 10 + 50;
        input << generate_gate_input(input_num, gate_num, true);
        input << generate_test_case(input_num, gate_num, case_num, unique_output_num);
    }
    stringstream output;
    LogicalMain(input, output);
    for (int i = 0; i < task_num; i++)
    {
        string result;
        output >> result;
        EXPECT_TRUE(result.find("LOOP") != string::npos);
    }
}

// 测试混合的多个任务
TEST(LOGICAL_MAIN_TEST, test_mixed_graph)
{
    stringstream input;
    srand(time(0));
    int task_num = 5;
    input << task_num << endl;
    for (int i = 0; i < task_num; i++)
    {
        int input_num = rand() % 100 + 50;
        int gate_num = rand() % 100 + 50;
        int case_num = rand() % 100 + 50;
        int unique_output_num = rand() % 10 + 50;
        input << generate_gate_input(input_num, gate_num, rand() % 2);
        input << generate_test_case(input_num, gate_num, case_num, unique_output_num);
    }
    stringstream output;
    LogicalMain(input, output);
}