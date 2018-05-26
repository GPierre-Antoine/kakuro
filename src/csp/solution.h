//
// Created by Pierre-Antoine on 26/05/2018.
//


#pragma once

#include <cstddef>
#include <vector>
#include <ctime>
#include "../forward.h"
#include "heuristic.h"

namespace csp
{

    class algorithm;

    class solution
    {
    public:
        const std::size_t variable_count;
        const std::string algorithm_info;
        const std::string heuristic_name;
    private:
        std::vector<std::vector<std::size_t>> records;
        std::size_t constraint_count;
        std::size_t node_count;
        std::clock_t start_time;
        std::clock_t end_time;
    public:
        friend void swap(solution &first, solution &second)
        {
            using std::swap;
            swap(first.records, second.records);
            swap(first.constraint_count, second.constraint_count);
            swap(first.node_count, second.node_count);
            swap(first.start_time, second.start_time);
            swap(first.end_time, second.end_time);
        }
        explicit solution(std::size_t variable_count, const csp::algorithm &algo, const csp::heuristic &heuristic);
        solution(solution &&previous) noexcept;
        void start_chrono();
        void stop_chrono();
        void add_record(const variable_vector &variables);
        std::clock_t get_execution_time() const;

        size_t get_constraint_count() const;
        void inc_constraint_count();

        size_t get_node_count() const;
        void inc_node_count();

        const std::vector<std::vector<std::size_t>> &get_records() const;
    };

}