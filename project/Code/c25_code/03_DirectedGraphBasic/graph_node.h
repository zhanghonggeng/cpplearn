/* -------------------------------
    表示图的单个节点的数据结构
-------------------------------*/
#pragma once

//#include <directed_graph1.h>
/*
 * note:
 * directed_graph.h 和 graph_node.h 互相包含了对方的头文件，这会导致编译器无法解析定义，从而产生错误。
 * 可以通过前向声明来解决，而不是包含头文件。
 */
#include <set>

namespace details {

    /*-------------------------------
    directed_graph的前向声明
    directed_graph 为有向图的类
    使用前向声明，directed_graph就不要作用域 ProCpp::directed_graph<T>
    -------------------------------*/
    template<typename T>
    class directed_graph;

    /*-------------------------------
    定义图节点的类模板
    -------------------------------*/
    template<typename T>
    class graph_node {
    public:
        /*-------------------------------
        构造函数
         directed_graph<T>*为有向图的指针
        -------------------------------*/
//        graph_node() = default;
        graph_node(directed_graph<T> *graph, const T &t);

        graph_node(directed_graph<T> *graph, T &&t);

        /*-------------------------------
        返回节点存储值的引用
        -------------------------------*/
        [[nodiscard]] T &value() noexcept;

        [[nodiscard]] const T &value() const noexcept;

        /*-------------------------------
        C++20 defaulted operator==,会自动默认!=
        -------------------------------*/
        bool operator==(const graph_node &) const = default;

        using adjacency_list_type = std::set<std::size_t>;
    private:
        friend class directed_graph<T>;

        /*-------------------------------
        指向节点所在图的指针
        -------------------------------*/
        directed_graph<T> *m_graph;
        /*-------------------------------
        set用于存储顶点指向的节点，这里是类型别名
        -------------------------------*/
        //using adjacency_list_type = std::set<size_t>;  //私有类型别名在友元访问时有问题

        /*-------------------------------
        返回对邻接列表的引用
        -------------------------------*/
        [[nodiscard]] adjacency_list_type &get_adjacent_nodes_indices();

        [[nodiscard]] const adjacency_list_type &get_adjacent_nodes_indices() const;

        /*-------------------------------
        m_data：顶点的值
        m_adjacentNodeIndices：用set保存顶点所指向的节点
        -------------------------------*/
        T m_data;
        adjacency_list_type m_adjacentNodeIndices;
    };
}
