#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <chrono>
#include <cstddef>
#include <cstring>
#include <cstddef>
#include <deque>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

class PmergeMe
{
private:
    int m_comparisons_vector{0};
    std::vector<int> m_vector{};
    std::deque<int> m_deque{};
    char **m_argv;

    int stoi_wrapper(const char *s);
    bool input_contains_duplicates(char *argv[]);

    /* VECTOR */
    std::vector<std::pair<int, int>> pairs_generate_vector(int *remainder);
    static std::vector<int> largest_generate_vector(const std::vector<std::pair<int, int>> &pairs);
    std::vector<int> pend_generate_vector(const std::vector<std::pair<int, int>> &pairs);
    static std::vector<int> insert_seq_generate_vector(size_t pend_chain_len);

    /* DEQUE */
    std::deque<std::pair<int, int>> pairs_generate_deque(int *remainder);
    static std::deque<int> largest_generate_deque(const std::deque<std::pair<int, int>> &pairs);
    std::deque<int> pend_generate_deque(const std::deque<std::pair<int, int>> &pairs);
    static std::deque<int> insert_seq_generate_deque(size_t pend_chain_len);

public:
    /* Default constructor */
    PmergeMe(void);
    /* Paramterized constructor */
    PmergeMe(char *argv[]);
    /* Copy assignment operator overload*/
    PmergeMe &operator=(const PmergeMe &source);
    /* Copy constructor */
    PmergeMe(const PmergeMe &source);
    /* Destructor */
    ~PmergeMe(void);

    /* Getters */
    int get_comparisons(void) { return m_comparisons_vector; }
    const std::vector<int> &get_vector(void) { return m_vector; }
    const std::deque<int> &get_deque(void) { return m_deque; }
    char **get_argv(void) { return m_argv; }

    template <typename SeqContainer>
    static void seq_container_print(const std::string &label, const SeqContainer &seqcontainer)
    {
        std::cout << label;
        for (const auto &elem : seqcontainer)
            std::cout << elem << ' ';
        std::cout << '\n';
    }

    template <typename SeqContainerPairs>
    static void pairs_print(const std::string &label, const SeqContainerPairs &pairs)
    {
        std::cout << label;
        for (const auto &p : pairs)
            std::cout << "(" << p.first << ", " << p.second << ") ";
        std::cout << '\n';
    }

    template <typename SeqContainerPairs>
    void pairs_sort_inner(SeqContainerPairs &pairs)
    {
        for (auto &pair : pairs)
        {
            m_comparisons_vector++;
            if (pair.first > pair.second)
                std::swap(pair.first, pair.second);
        }
    }

    template <typename SeqContainer>
    int ft_bisect_left(const SeqContainer &seqcontainer, int x, int lo, int hi)
    {
        if (lo < 0)
            throw std::runtime_error("lo must be non-negative");
        if (hi == -1)
            hi = seqcontainer.size();
        while (lo < hi)
        {
            int mid = (lo + hi) / 2;
            m_comparisons_vector++;
            if (seqcontainer[mid] < x)
                lo = mid + 1;
            else
                hi = mid;
        }
        return lo;
    }

    /* Methods */
    void args_to_vector(void);
    void ford_johnson_algo_vector(void);

    void args_to_deque(void);
    void ford_johnson_algo_deque(void);
};

#endif
