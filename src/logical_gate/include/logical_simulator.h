#ifndef LOGICAL_SIMULATOR_H
#define LOGICAL_SIMULATOR_H

#include <vector>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <map>
#include "logical_gate.h"

typedef std::vector<std::vector<int>> Graph;

void EachCase(std::vector<LogicalGate> &gates, std::vector<int> &case_input, std::vector<int> &show_list, int input_num, int gate_num, std::vector<int> &search_sequence, std::unordered_map<int, int> &search_sequence_map, std::map<std::vector<int>, int> &seq_max_map, std::ostream &out_stream = std::cout);
LogicalGate GenerateGate(std::string str, int index, int input_num, int gate_num, Graph &graph);
std::vector<int> TopologicalSort(Graph &graph);
void Task(std::istream &in_stream = std::cin, std::ostream &out_stream = std::cout);
void LogicalMain(std::istream &in_stream = std::cin, std::ostream &out_stream = std::cout);

#endif // LOGICAL_SIMULATOR_H

