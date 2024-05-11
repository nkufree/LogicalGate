#include <gtest/gtest.h>
#include "./include/graph_generate.h"
#include "logical_simulator.h"
#include <sstream>
#include <fstream>

using namespace std;

// 测试简单的任务
TEST(TASK_TEST, test_simple_DAG)
{
    string input_str = "3 5\n"
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
    Task(task_input, task_output);
    ASSERT_TRUE(task_output.str().find("LOOP") == string::npos);
    for (int i = 0; i < 8; i++)
    {
        int tmp;
        task_output >> tmp;
        ASSERT_EQ(tmp, output[i]);
    }
}

// 测试简单的有环任务
TEST(TASK_TEST, test_simple_cycle)
{
    string input_str = "2 6\n"
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
    Task(task_input, task_output);
    ASSERT_TRUE(task_output.str().find("LOOP") != string::npos);
}

// 测试较大的无环任务
TEST(TASK_TEST, test_big_DAG)
{
    stringstream task_input;
    stringstream task_output;
    int input_num = 100;
    int gate_num = 1000;
    int case_num = 1000;
    int unique_output_num = 100;
    task_input << generate_gate_input(input_num, gate_num, false);
    task_input << generate_test_case(input_num, gate_num, case_num, unique_output_num);
    // ofstream out("task_input.txt");
    // out << task_input.str();
    // out.close();
    Task(task_input, task_output);
    ASSERT_TRUE(task_output.str().find("LOOP") == string::npos);
}

// 测试较大的有环任务
TEST(TASK_TEST, test_big_cycle)
{
    stringstream task_input;
    stringstream task_output;
    int input_num = 100;
    int gate_num = 1000;
    int case_num = 1000;
    int unique_output_num = 100;
    task_input << generate_gate_input(input_num, gate_num, true);
    task_input << generate_test_case(input_num, gate_num, case_num, unique_output_num);
    Task(task_input, task_output);
    ASSERT_TRUE(task_output.str().find("LOOP") != string::npos);
}