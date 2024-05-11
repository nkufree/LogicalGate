# 逻辑电路模拟程序

## 基本信息

2024年春 南开大学 软件工程 实践课题4： 软件编程实现、分析和测试

使用C++编写，GoogleTest作为单元测试的工具。

GoogleTest相关的链接库是我在自己电脑上编译的，可以替换。

编译使用MinGW的g++，版本为13.2.0。

## 文件结构

```
LogicalGate
|   Makefile							// 编译命令
+---src									// 编程问题的源代码目录
|   |   main.cpp						// 程序入口
|   \---logical_gate					// 逻辑电路相关目录
|       |   logical_gate.cpp
        |   logical_simulator.cpp
|       \---include
|               logical_gate.h
    		   logical_simulator.h
\---unittest							// 单元测试相关文件
    +---googletest						// GoogleTest相关文件
    |   +---include						// GoogleTest头文件
    |   |   +---gmock
    |   |   \---gtest
    |   \---lib							 // GoogleTest相关链接库
    \---testcase						 // 单元测试相关文件
        |   each_case_test.cpp			   // 测试EachCase函数
        |   generate_gate_test.cpp		   // 测试GenerateGate函数
        |   graph_generate.cpp			   // 测试用例生成
        |   logical_main_test.cpp		   // 测试LogicalMain函数
        |   logic_op_test.cpp			   // 测试逻辑门
        |   main.cpp					  // 单元测试入口
        |   task_test.cpp				   // 测试Task函数
        |   topological_sort_test.cpp		// 测试TopologicalSort函数
        \---include						  // 测试用例生成相关函数的头文件
                graph_generate.h
```
