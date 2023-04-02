/* -------------------------------
    ��ʾͼ�ĵ����ڵ�����ݽṹ
-------------------------------*/
#pragma once

//#include <directed_graph1.h>
/*
 * note:
 * directed_graph.h �� graph_node.h ��������˶Է���ͷ�ļ�����ᵼ�±������޷��������壬�Ӷ���������
 * ����ͨ��ǰ������������������ǰ���ͷ�ļ���
 */
#include <set>

namespace details {

    /*-------------------------------
    directed_graph��ǰ������
    directed_graph Ϊ����ͼ����
    ʹ��ǰ��������directed_graph�Ͳ�Ҫ������ ProCpp::directed_graph<T>
    -------------------------------*/
    template<typename T>
    class directed_graph;

    /*-------------------------------
    ����ͼ�ڵ����ģ��
    -------------------------------*/
    template<typename T>
    class graph_node {
    public:
        /*-------------------------------
        ���캯��
         directed_graph<T>*Ϊ����ͼ��ָ��
        -------------------------------*/
//        graph_node() = default;
        graph_node(directed_graph<T> *graph, const T &t);

        graph_node(directed_graph<T> *graph, T &&t);

        /*-------------------------------
        ���ؽڵ�洢ֵ������
        -------------------------------*/
        [[nodiscard]] T &value() noexcept;

        [[nodiscard]] const T &value() const noexcept;

        /*-------------------------------
        C++20 defaulted operator==,���Զ�Ĭ��!=
        -------------------------------*/
        bool operator==(const graph_node &) const = default;

        using adjacency_list_type = std::set<std::size_t>;
    private:
        friend class directed_graph<T>;

        /*-------------------------------
        ָ��ڵ�����ͼ��ָ��
        -------------------------------*/
        directed_graph<T> *m_graph;
        /*-------------------------------
        set���ڴ洢����ָ��Ľڵ㣬���������ͱ���
        -------------------------------*/
        //using adjacency_list_type = std::set<size_t>;  //˽�����ͱ�������Ԫ����ʱ������

        /*-------------------------------
        ���ض��ڽ��б������
        -------------------------------*/
        [[nodiscard]] adjacency_list_type &get_adjacent_nodes_indices();

        [[nodiscard]] const adjacency_list_type &get_adjacent_nodes_indices() const;

        /*-------------------------------
        m_data�������ֵ
        m_adjacentNodeIndices����set���涥����ָ��Ľڵ�
        -------------------------------*/
        T m_data;
        adjacency_list_type m_adjacentNodeIndices;
    };
}
