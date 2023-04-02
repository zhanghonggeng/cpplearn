/* -------------------------------
    有向图
-------------------------------*/
#pragma once

#include <graph_node.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstddef>

namespace ProCpp {

    /* -------------------------------
    有向图的类模板
    -------------------------------*/
    template<typename T>
    class directed_graph {
    public:
        /* -------------------------------
        有向图中插入、删除节点
         -------------------------------*/
        bool insert(const T &node_value);

        bool insert(T &&node_value);

        bool erase(const T &node_value);

        /* -------------------------------
        插入、删除有向图的边
        -------------------------------*/
        bool insert_edge(const T &from_node_value, const T &to_node_value);

        bool erase_edge(const T &from_node_value, const T &to_node_value);

        /* -------------------------------
        删除有向图中所有节点
        -------------------------------*/
        void clear() noexcept;

        /* -------------------------------
        返回给定索引的节点的引用
        -------------------------------*/
        T &operator[](size_t index);

        const T &operator[](size_t index) const;

        /* -------------------------------
        判断有向图相等、不相等
        -------------------------------*/
        bool operator==(const directed_graph &rhs) const;

        bool operator!=(const directed_graph &rhs) const;

        /* -------------------------------
         此有向图和给定有向图的所有节点进行交换
        -------------------------------*/
        void swap(directed_graph &other_graph) noexcept;

        /* -------------------------------
         返回有向图中的节点数
        -------------------------------*/
        [[nodiscard]] size_t size() const noexcept;

        /* -------------------------------
         返回一个具有给定节点的相邻节点的集合。如果给定节点不存在，则返回一个空集。
        -------------------------------*/
        [[nodiscard]] std::set<T> get_adjacent_nodes_values(const T &node_value) const;

    private:

        friend details::graph_node<T>;
        /* -------------------------------
         邻接表中用vector表示里面存储图中已有节点类型
        -------------------------------*/
        using nodes_container_type = std::vector<details::graph_node<T>>;
        nodes_container_type m_nodes;

        /* -------------------------------
         Helper方法将迭代器返回给给定节点，如果给定节点不在图中，则返回结束迭代器。
         note：
            当使用依赖于模板参数的类型（类型别名）时，必须使用typename
        -------------------------------*/
        typename nodes_container_type::iterator findNode(const T &node_value);

        typename nodes_container_type::const_iterator findNode(const T &node_value) const;

        /* -------------------------------
         给定一个节点的迭代器，将该节点从所有其他节点的所有邻接列表中删除。
        -------------------------------*/
        void remove_all_links_to(typename nodes_container_type::const_iterator node_iter);

        /* -------------------------------
         给定一组相邻节点索引，返回相应的一组节点值。
        -------------------------------*/
        [[nodiscard]] std::set<T>
        get_adjacent_nodes_values(const typename details::graph_node<T>::adjacency_list_type &indices) const;

        /* -------------------------------
         给定一个节点的迭代器，返回节点容器中该节点的索引。
        -------------------------------*/
        [[nodiscard]] size_t
        get_index_of_node(const typename nodes_container_type::const_iterator &node) const noexcept;
    };

    /* -------------------------------
     全局swap函数，下面的独立swap（）函数简单地转发到swap（）方法。
    -------------------------------*/
    template<typename T>
    void swap(directed_graph<T> &first, directed_graph<T> &second) noexcept {
        first.swap(second);
    }

    template<typename T>
    bool directed_graph<T>::insert(const T &node_value) {
        T copy{node_value};
        return insert(std::move(copy));
    }

    template<typename T>
    bool directed_graph<T>::insert(T &&node_value) {
        auto iter{findNode(node_value)};
        if (iter != std::end(m_nodes)) {
            // Value is already in the graph, return false.
            return false;
        }
        // 在vector后面插入一个节点
        m_nodes.emplace_back(this, std::move(node_value));
        // Value successfully added to the graph, return true.
        return true;
    }

    template<typename T>
    size_t
    directed_graph<T>::get_index_of_node(const typename nodes_container_type::const_iterator &node) const noexcept {
        const auto index{std::distance(std::cbegin(m_nodes), node)};
        return static_cast<size_t>(index);
    }

    template<typename T>
    bool directed_graph<T>::insert_edge(const T &from_node_value, const T &to_node_value) {
        const auto from{findNode(from_node_value)};
        const auto to{findNode(to_node_value)};
        if (from == std::end(m_nodes) || to == std::end(m_nodes)) {
            return false;
        }

        const size_t to_index{get_index_of_node(to)};
        return from->get_adjacent_nodes_indices().insert(to_index).second;
    }

    template<typename T>
    bool directed_graph<T>::erase_edge(const T &from_node_value, const T &to_node_value) {
        const auto from{findNode(from_node_value)};
        const auto to{findNode(to_node_value)};
        if (from == std::end(m_nodes) || to == std::end(m_nodes)) {
            return false; // nothing to erase
        }

        const size_t to_index{get_index_of_node(to)};
        from->get_adjacent_nodes_indices().erase(to_index);
        return true;
    }

    template<typename T>
    void directed_graph<T>::remove_all_links_to(typename nodes_container_type::const_iterator node_iter) {
        const size_t node_index{get_index_of_node(node_iter)};

        // Iterate over all adjacency lists of all nodes.
        for (auto &&node: m_nodes) {
            auto &adjacencyIndices{node.get_adjacent_nodes_indices()};
            // First, remove references to the to-be-deleted node.
            adjacencyIndices.erase(node_index);
            // Second, modify all adjacency indices to account for the removal of a node.
            std::vector<size_t> indices(std::begin(adjacencyIndices), std::end(adjacencyIndices));
            std::for_each(std::begin(indices), std::end(indices),
                          [node_index](size_t &index) {
                              if (index > node_index) {
                                  --index;
                              }
                          });
            adjacencyIndices.clear();
            adjacencyIndices.insert(std::begin(indices), std::end(indices));
        }
    }

    template<typename T>
    bool directed_graph<T>::erase(const T &node_value) {
        auto iter{findNode(node_value)};
        if (iter == std::end(m_nodes)) {
            return false;
        }
        remove_all_links_to(iter);
        m_nodes.erase(iter);
        return true;
    }

    template<typename T>
    void directed_graph<T>::clear() noexcept {
        m_nodes.clear();
    }

    template<typename T>
    typename directed_graph<T>::nodes_container_type::iterator
    directed_graph<T>::findNode(const T &node_value) {
        return std::find_if(std::begin(m_nodes), std::end(m_nodes),
                            [&node_value](const auto &node) { return node.value() == node_value; });
    }

    template<typename T>
    typename directed_graph<T>::nodes_container_type::const_iterator
    directed_graph<T>::findNode(const T &node_value) const {
        return const_cast<directed_graph<T> *>(this)->findNode(node_value);
    }

    template<typename T>
    T &directed_graph<T>::operator[](size_t index) {
        return m_nodes[index].value();
    }

    template<typename T>
    const T &directed_graph<T>::operator[](size_t index) const {
        return m_nodes[index].value();
    }

    template<typename T>
    std::set<T> directed_graph<T>::get_adjacent_nodes_values(
            const typename details::graph_node<T>::adjacency_list_type &indices) const {
        std::set<T> values;
        for (auto &&index: indices) {
            values.insert(m_nodes[index].value());
        }
        return values;
    }

    template<typename T>
    std::set<T> directed_graph<T>::get_adjacent_nodes_values(const T &node_value) const {
        auto iter{findNode(node_value)};
        if (iter == std::end(m_nodes)) {
            return std::set<T>{};
        }

        return get_adjacent_nodes_values(iter->get_adjacent_nodes_indices());
    }

    template<typename T>
    bool directed_graph<T>::operator==(const directed_graph &rhs) const {
        if (m_nodes.size() != rhs.m_nodes.size()) { return false; }

        for (auto &&node: m_nodes) {
            const auto rhsNodeIter{rhs.findNode(node.value())};
            if (rhsNodeIter == std::end(rhs.m_nodes)) {
                return false;
            }
            const auto adjacent_values_lhs{get_adjacent_nodes_values(node.get_adjacent_nodes_indices())};
            const auto adjacent_values_rhs{rhs.get_adjacent_nodes_values(rhsNodeIter->get_adjacent_nodes_indices())};
            if (adjacent_values_lhs != adjacent_values_rhs) {
                return false;
            }
        }
        return true;
    }

    template<typename T>
    bool directed_graph<T>::operator!=(const directed_graph &rhs) const {
        return !(*this == rhs);
    }

    template<typename T>
    void directed_graph<T>::swap(directed_graph &other_graph) noexcept {
        m_nodes.swap(other_graph.m_nodes);
    }

    template<typename T>
    size_t directed_graph<T>::size() const noexcept {
        return m_nodes.size();
    }
}