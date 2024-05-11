#ifndef LOGICAL_GATE_H
#define LOGICAL_GATE_H

#include <unordered_map>
#include <string>
#include <vector>

// 电路输入输出的线上的信号值
typedef bool Wire;

// 逻辑门类型
enum GateType
{
    NOT,     // 非
    AND,     // 与
    OR,      // 或
    XOR,     // 异或
    NAND,    // 与非
    NOR,     // 或非
    GATE_NUM // 逻辑门数量
};

// 逻辑门结构体，包含类型，输入，输出
struct LogicalGate
{
    int type;                // 逻辑门类型
    std::vector<int> inputs; // 逻辑门输入编号
    int output;              // 逻辑门输出编号
};

extern std::unordered_map<std::string, int> GateTypeMap;
extern std::unordered_map<int, std::string> GateNameMap;
extern unsigned int GateInputNum[][2];
extern bool (*LogicOp[])(std::vector<int> &, Wire *);

std::ostream &operator<<(std::ostream &os, const LogicalGate &gate);

#endif // LOGICAL_GATE_H