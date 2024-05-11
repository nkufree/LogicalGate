#include <gtest/gtest.h>
#include "logical_simulator.h"
#include <vector>
#include "./include/graph_generate.h"

using namespace std;

// 测试简单的拓扑排序
TEST(TOPOLOGICAL_SORT_TEST, test_DAG)
{
    vector<vector<int>> graph = {
        {1, 2},
        {3},
        {3},
        {}};
    vector<int> result = TopologicalSort(graph);
    EXPECT_EQ(result.size(), 4);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[3], 3);
}

// 测试只有一种拓扑排序的有向无环图
TEST(TOPOLOGICAL_SORT_TEST, test_DAG_simple)
{
    vector<vector<int>> graph = {
        {1},
        {2},
        {3},
        {}};
    vector<int> result = TopologicalSort(graph);
    EXPECT_EQ(result.size(), 4);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 1);
    EXPECT_EQ(result[2], 2);
    EXPECT_EQ(result[3], 3);
}

// 测试大规模的有向无环图
TEST(TOPOLOGICAL_SORT_TEST, test_DAG_big)
{
    vector<vector<int>> graph;
    vector<int> result;
    graph = generate_DAG(100);
    result = TopologicalSort(graph);
    EXPECT_EQ(result.size(), graph.size());
    graph = generate_DAG(1000);
    result = TopologicalSort(graph);
    EXPECT_EQ(result.size(), graph.size());
    graph = generate_DAG(10000);
    result = TopologicalSort(graph);
    EXPECT_EQ(result.size(), graph.size());
}

// 测试简单的有环的图
TEST(TOPOLOGICAL_SORT_TEST, test_cycle_simple)
{
    vector<vector<int>> graph = {
        {1, 2},
        {3},
        {3},
        {0}};
    vector<int> result = TopologicalSort(graph);
    EXPECT_NE(result.size(), graph.size());
}

// 测试大规模的有环图
TEST(TOPOLOGICAL_SORT_TEST, test_cycle_big)
{
    vector<vector<int>> graph;
    vector<int> result;
    graph = generate_cycle(100);
    result = TopologicalSort(graph);
    EXPECT_NE(result.size(), graph.size());
    graph = generate_cycle(1000);
    result = TopologicalSort(graph);
    EXPECT_NE(result.size(), graph.size());
    graph = generate_cycle(10000);
    result = TopologicalSort(graph);
    EXPECT_NE(result.size(), graph.size());
}