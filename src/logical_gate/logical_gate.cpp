#include "logical_gate.h"
#include <iostream>

using namespace std;

// 逻辑门字符串到类型的映射
unordered_map<string, int> GateTypeMap = {
    {"NOT", NOT},
    {"AND", AND},
    {"OR", OR},
    {"XOR", XOR},
    {"NAND", NAND},
    {"NOR", NOR}};

unordered_map<int, string> GateNameMap = {
    {NOT, "NOT"},
    {AND, "AND"},
    {OR, "OR"},
    {XOR, "XOR"},
    {NAND, "NAND"},
    {NOR, "NOR"}};

// 逻辑门输入的数量限制，每一项都对应最小、最大输入数量
unsigned int GateInputNum[][2] = {
    [NOT] = {1, 1},
    [AND] = {2, (unsigned int)(-1)},
    [OR] = {2, (unsigned int)(-1)},
    [XOR] = {2, (unsigned int)(-1)},
    [NAND] = {2, (unsigned int)(-1)},
    [NOR] = {2, (unsigned int)(-1)}};

// 逻辑门的具体操作，从输入的vecotr<int>中获取输入的线的值，然后根据逻辑门的类型计算输出
bool (*LogicOp[])(vector<int> &, Wire *) = {
    [NOT] = [](vector<int> &inputs, Wire *wires) -> bool
    { return !wires[inputs[0]]; },
    [AND] = [](vector<int> &inputs, Wire *wires) -> bool
    {
        bool result = wires[inputs[0]];
        for (int i = 1; i < inputs.size(); i++)
        {
            result &= wires[inputs[i]];
        }
        return result;
    },
    [OR] = [](vector<int> &inputs, Wire *wires) -> bool
    {
        bool result = wires[inputs[0]];
        for (int i = 1; i < inputs.size(); i++)
        {
            result |= wires[inputs[i]];
        }
        return result;
    },
    [XOR] = [](vector<int> &inputs, Wire *wires) -> bool
    {
        bool result = wires[inputs[0]];
        for (int i = 1; i < inputs.size(); i++)
        {
            result ^= wires[inputs[i]];
        }
        return result;
    },
    [NAND] = [](vector<int> &inputs, Wire *wires) -> bool
    {
        bool result = wires[inputs[0]];
        for (int i = 1; i < inputs.size(); i++)
        {
            result &= wires[inputs[i]];
        }
        return !result;
    },
    [NOR] = [](vector<int> &inputs, Wire *wires) -> bool
    {
        bool result = wires[inputs[0]];
        for (int i = 1; i < inputs.size(); i++)
        {
            result |= wires[inputs[i]];
        }
        return !result;
    }};

// 打印一个逻辑门的信息
ostream &operator<<(ostream &os, const LogicalGate &gate)
{
    os << "type: " << gate.type << " inputs: ";
    for (auto &i : gate.inputs)
    {
        os << i << " ";
    }
    os << "-> " << gate.output;
    return os;
}