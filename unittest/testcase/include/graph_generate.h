#include <vector>
#include <string>

std::vector<std::vector<int>> generate_DAG(int n, float rate = 0.5);

std::vector<std::vector<int>> generate_cycle(int n, float rate = 0.5);

std::string generate_gate_input(int input_num, int gate_num, bool has_cycle, int max_gate_input = 8);

std::string generate_test_case(int input_num, int gate_num, int case_num, int unique_output_num, int output_each_num_min = 20, int output_each_num_max = 100);