#include "./include/graph_generate.h"
#include "logical_simulator.h"
#include <algorithm>
#include <random>
#include <time.h>
#include <sstream>

using namespace std;

// 生成一个随机的有向无环图
// 输入：
// n: 图的节点数
// rate: 生成图的稀疏程度，0-1之间的浮点数，越大越稀疏
Graph generate_DAG(int n, float rate)
{
    Graph graph(n);
    int stop = rate * 100;
    srand(time(0));
    int *nodes = new int[n];
    for (int i = 0; i < n; i++)
    {
        nodes[i] = i;
    }
    random_shuffle(nodes, nodes + n);
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (rand() % 100 < stop)
            {
                graph[nodes[i]].push_back(nodes[j]);
            }
        }
    }
    delete[] nodes;
    return graph;
}

// 生成一个随机的有向有环图
// 输入：
// n: 图的节点数
// rate: 生成图的稀疏程度，0-1之间的浮点数，越大越稀疏
Graph generate_cycle(int n, float rate)
{
    Graph graph(n);
    int stop = rate * 100;
    srand(time(0));
    int *nodes = new int[n];
    for (int i = 0; i < n; i++)
    {
        nodes[i] = i;
    }
    random_shuffle(nodes, nodes + n);
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (rand() % 100 < stop)
            {
                graph[nodes[i]].push_back(nodes[j]);
            }
        }
    }
    // 逆向生成一个环，就不需要考虑重复的问题了
    for (int i = 0; i < n; i++)
    {
        graph[nodes[(n + 1) % n]].push_back(nodes[i]);
    }
    delete[] nodes;
    return graph;
}

// 生成若干个随机的逻辑门输入字符串
// 输入：
// input_num: 电路的输入个数
// gate_num: 逻辑门的个数
// has_cycle: 是否有环
// max_gate_input: 逻辑门的最大输入个数
string generate_gate_input(int input_num, int gate_num, bool has_cycle, int max_gate_input)
{
    stringstream ss;
    ss << input_num << " " << gate_num << endl;
    Graph graph;
    srand(time(0));
    // 在这里为了方便起见，我们认为图中存储的是每一个门的输入
    graph = generate_DAG(gate_num);
    vector<LogicalGate> gates(gate_num);
    // 第一次遍历，从有向无环图生成输入
    for (int i = 0; i < gate_num; i++)
    {
        vector<int> &edges = graph[i];
        vector<int> &gate_inputs = gates[i].inputs;
        int gate_type = rand() % GATE_NUM;
        gates[i].type = gate_type;
        gates[i].output = input_num + i;
        int gate_input_num;
        if (gate_type == NOT)
        {
            gate_input_num = 1;
        }
        else
        {
            gate_input_num = rand() % (max_gate_input - 1) + 2;
        }
        if (gate_input_num < edges.size())
        {
            for (int i = 0; i < gate_input_num; i++)
            {
                gate_inputs.push_back(edges[i] + input_num);
            }
            // 随机改变一些输入为电路的输入
            int rand_change_index = rand() % (gate_input_num * 3);
            if (rand_change_index < gate_input_num)
            {
                gate_inputs[rand_change_index] = rand() % input_num;
            }
        }
        else
        {
            for (int &src : edges)
            {
                gate_inputs.push_back(src + input_num);
            }
            // 在最后插入一些电路输入
            for (int i = edges.size(); i < gate_input_num; i++)
            {
                gate_inputs.push_back(rand() % input_num);
            }
        }
    }
    // 如果需要有环，进行第二次遍历，添加环路
    if (has_cycle)
    {
        vector<int> cycle;
        for (int i = 0; i < gate_num; i++)
        {
            cycle.push_back(i);
        }
        random_shuffle(cycle.begin(), cycle.end());
        for (int i = 0; i < gate_num; i++)
        {
            int replace_pos = rand() % gates[cycle[i]].inputs.size();
            gates[cycle[i]].inputs[replace_pos] = gates[cycle[(i + 1) % gate_num]].output;
        }
    }
    // 最后一次遍历，将逻辑门信息写入到ss中
    for (int i = 0; i < gate_num; i++)
    {
        ss << GateNameMap[gates[i].type] << " " << gates[i].inputs.size();
        for (int &input : gates[i].inputs)
        {
            ss << " ";
            if (input < input_num)
            {
                ss << "I" << input + 1;
            }
            else
            {
                ss << "O" << input - input_num + 1;
            }
        }
        ss << endl;
    }
    return ss.str();
}

// 生成若干个随机的测试用例的字符串
// 输入：
// input_num: 电路的输入个数
// gate_num: 逻辑门的个数
// case_num: 测试用例的个数
// unique_output_num: 不同的输出个数
// output_each_num_min: 每个输出的最小个数
// output_each_num_max: 每个输出的最大个数
string generate_test_case(int input_num, int gate_num, int case_num, int unique_output_num, int output_each_num_min, int output_each_num_max)
{
    stringstream ss;
    ss << case_num << endl;
    // 生成随机输入
    for (int i = 0; i < case_num; i++)
    {
        for (int j = 0; j < input_num; j++)
        {
            ss << rand() % 2 << " ";
        }
        ss << endl;
    }
    // 生成随机输出
    vector<string> output_case;
    for (int i = 0; i < unique_output_num; i++)
    {
        stringstream tmp;
        if (output_each_num_min > output_each_num_max)
        {
            output_each_num_min = output_each_num_max;
        }
        int curr_output_num = (rand() % (output_each_num_max - output_each_num_min) + output_each_num_min) % gate_num + 1;
        tmp << curr_output_num;
        for (int j = 0; j < curr_output_num; j++)
        {
            tmp << " " << rand() % gate_num + 1;
        }
        output_case.push_back(tmp.str());
    }
    // 从随机输出中随机选择作为正式的输出
    for (int i = 0; i < case_num; i++)
    {
        ss << output_case[rand() % unique_output_num] << endl;
    }
    return ss.str();
}