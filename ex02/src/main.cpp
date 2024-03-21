#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        std::cerr << "Error: please provide at least 2 command line arguments\n";
        return -1;
    }

    PmergeMe pmergeme;

    /* VECTOR */
    const auto start_vector{std::chrono::steady_clock::now()};
    try
    {
        pmergeme = PmergeMe(argv);
        pmergeme.args_to_vector();
    }
    catch (std::invalid_argument const &ex)
    {
        std::cerr << "Error: " << ex.what() << '\n';
        return -2;
    }
    catch (std::out_of_range const &ex)
    {
        std::cerr << "Error: " << ex.what() << '\n';
        return -3;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << '\n';
        return -4;
    }
    pmergeme.ford_johnson_algo_vector();
    const auto end_vector{std::chrono::steady_clock::now()};

    PmergeMe::seq_container_print("After:\t", pmergeme.get_vector());
    std::cout << "Comparisons: " << pmergeme.get_comparisons() << '\n';

    /* DEQUE */
    const auto start_deque{std::chrono::steady_clock::now()};
    pmergeme.args_to_deque();
    pmergeme.ford_johnson_algo_deque();
    const auto end_deque{std::chrono::steady_clock::now()};

    const std::chrono::duration<double> elapsed_seconds_vector{end_vector - start_vector};
    std::cout << "Time to process a range of " << pmergeme.get_vector().size() << " elements with std::vector:\t" << std::fixed << std::setprecision(6) << elapsed_seconds_vector.count() << "s\n";

    const std::chrono::duration<double> elapsed_seconds_deque{end_deque - start_deque};
    std::cout << "Time to process a range of " << pmergeme.get_deque().size() << " elements with std::deque: \t" << std::fixed << std::setprecision(6) << elapsed_seconds_deque.count() << "s\n";

    return 0;
}