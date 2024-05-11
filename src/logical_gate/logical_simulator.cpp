#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string.h>
#include <algorithm>
#include <map>
#include <stdio.h>
#include "./include/logical_simulator.h"
#include <sstream>

using namespace std;

// 计算并打印每个样例的输出
// 输入：
// gates，逻辑门的列表
// case_input，输入的值
// show_list，需要输出的值的编号
// input_num，输入的个数
// gate_num，逻辑门的个数
// search_sequence，拓扑排序后的逻辑门序列
// search_sequence_map，逻辑门到拓扑排序中的位置映射
// seq_max_map，每个输出序列中在拓扑排序最后的逻辑门位置
// out_sream，输出流
void EachCase(vector<LogicalGate> &gates, vector<int> &case_input, vector<int> &show_list, int input_num, int gate_num, vector<int> &search_sequence, unordered_map<int, int> &search_sequence_map, map<vector<int>, int> &seq_max_map, ostream &out_stream)
{
    int max_pos = search_sequence.size() - 1;
    // 每次查询输出序列的最后一个逻辑门的位置，如果已经查询过，直接使用，否则查找最大的位置
    if (seq_max_map.find(show_list) != seq_max_map.end())
    {
        max_pos = seq_max_map[show_list];
    }
    else
    {
        auto item = max_element(show_list.begin(), show_list.end(), [&search_sequence_map](int a, int b)
                                { return search_sequence_map[a] < search_sequence_map[b]; });
        seq_max_map[show_list] = search_sequence_map[*item];
    }
    Wire *wires = new Wire[input_num + gate_num];
    bool input;
    for (int i = 0; i < input_num; i++)
    {
        wires[i] = case_input[i];
    }
    for (int i = 0; i <= max_pos; i++)
    {
        LogicalGate &gate = gates[search_sequence[i]];
        wires[gate.output] = LogicOp[gate.type](gate.inputs, wires);
        // for(int i = 0; i < input_num + gate_num; i++) {
        //     out_stream << wires[i].ready<< " " << wires[i] << " | ";
        // }
        // out_stream << endl;
    }
    for (auto &i : show_list)
    {
        out_stream << wires[i + input_num] << " ";
    }
    out_stream << endl;
    delete[] wires;
}

// 对图进行拓扑排序，返回排序后的序列
// 输入：图graph
// 这里输入的图中存储的是每个节点的出边，例如[[1, 2], [3], [3], []]表示0->1, 0->2, 1->3, 2->3
// 输出：排序后的序列
vector<int> TopologicalSort(Graph &graph)
{
    int m = graph.size(); // 逻辑门的个数，也就是图的节点个数
    vector<int> result;
    vector<int> in_degree(m, 0);
    for (int i = 0; i < m; i++)
    {
        for (auto &j : graph[i])
        {
            if (j > m)
                continue;
            in_degree[j]++;
        }
    }
    // for(int i = 0; i < m; i++) {
    //     out_stream << in_degree[i] << " ";
    // }
    queue<int> q;
    for (int i = 0; i < m; i++)
    {
        if (in_degree[i] == 0)
        {
            q.push(i);
        }
    }
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        result.push_back(node);
        for (auto &i : graph[node])
        {
            if (i > m)
                continue;
            in_degree[i]--;
            if (in_degree[i] == 0)
            {
                q.push(i);
            }
        }
    }
    return result;
}

// 解析字符串为LogicalGate
// 输入：
// str，逻辑门的字符串表示，例如"AND 3 I1 I2 O1"
// index，逻辑门的编号
// input_num，输入的个数
// gate_num，逻辑门的个数
// graph，逻辑门的图
// 输出：LogicalGate
LogicalGate GenerateGate(string str, int index, int input_num, int gate_num, Graph &graph)
{
    stringstream ss(str);
    LogicalGate gate;
    string type;
    ss >> type;
    if (GateTypeMap.find(type) == GateTypeMap.end())
    {
        throw invalid_argument("invalid gate type");
    }
    gate.type = GateTypeMap[type];
    int gate_input_num;
    ss >> gate_input_num;
    if (!(gate_input_num >= GateInputNum[gate.type][0] && gate_input_num <= GateInputNum[gate.type][1]))
    {
        throw invalid_argument("invalid input number");
    }
    for (int j = 0; j < gate_input_num; j++)
    {
        string input;
        ss >> input;
        // 输入的格式为I1, I2, O1, O2等，I表示输入，O表示输出
        // 将输入的I映射到0 ~ input_num-1，O映射到input_num ~ input_num+gate_num-1
        if (input[0] == 'I')
        {
            int input_index;
            sscanf(input.c_str(), "I%d", &input_index);
            if (!(input_index <= input_num && input_index > 0))
            {
                throw invalid_argument("invalid input");
            }
            gate.inputs.push_back(input_index - 1);
        }
        else if (input[0] == 'O')
        {
            int out_index;
            sscanf(input.c_str(), "O%d", &out_index);
            if (!(out_index <= gate_num && out_index > 0))
            {
                throw invalid_argument("invalid input");
            }
            gate.inputs.push_back(out_index + input_num - 1);
            graph[out_index - 1].push_back(index);
        }
        else
        {
            throw invalid_argument("invalid input");
        }
    }
    gate.output = input_num + index;
    return gate;
}

// 执行每一个逻辑电路操作
void Task(istream &in_stream, ostream &out_stream)
{
    vector<LogicalGate> gates;
    int input_num, gate_num;
    in_stream >> input_num >> gate_num;
    Graph graph(gate_num, vector<int>());
    in_stream.get();
    for (int i = 0; i < gate_num; i++)
    {
        string str;
        getline(in_stream, str);
        LogicalGate gate = GenerateGate(str, i, input_num, gate_num, graph);
        gates.push_back(gate);
        // out_stream << gate << endl;
    }
    vector<int> search_sequence = TopologicalSort(graph);
    // 如果拓扑排序后的序列长度不等于m，说明有环
    if (search_sequence.size() != gate_num)
    {
        out_stream << "LOOP" << endl;
        int case_num;
        in_stream >> case_num;
        string tmp;
        for (int i = 0; i <= case_num * 2; i++)
        {
            getline(in_stream, tmp);
        }
        return;
    }
    // 将拓扑排序后的序列映射到一个map中，方便查找
    unordered_map<int, int> search_sequence_map;
    for (int i = 0; i < gate_num; i++)
    {
        search_sequence_map[search_sequence[i]] = i;
    }
    int case_num;
    in_stream >> case_num;
    vector<vector<int>> cases(case_num, vector<int>());
    for (int i = 0; i < case_num; i++)
    {
        for (int j = 0; j < input_num; j++)
        {
            int input;
            in_stream >> input;
            cases[i].push_back(input);
        }
    }
    map<vector<int>, int> seq_max_map; // 用于缓存查找过的序列的最大位置
    for (int i = 0; i < case_num; i++)
    {
        int show_num;
        in_stream >> show_num;
        int show;
        vector<int> show_list;
        for (int i = 0; i < show_num; i++)
        {
            in_stream >> show;
            show_list.push_back(show - 1);
        }
        EachCase(gates, cases[i], show_list, input_num, gate_num, search_sequence, search_sequence_map, seq_max_map, out_stream);
    }
}

void LogicalMain(istream &in_stream, ostream &out_stream)
{
    int task_num;
    in_stream >> task_num;
    for (int i = 0; i < task_num; i++)
    {
        Task(in_stream, out_stream);
    }
}