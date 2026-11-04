#include "PmergeMe.hpp"

/*Default constructor */
PmergeMe::PmergeMe(void)
{
}

/* Paramterized constructor */
PmergeMe::PmergeMe(char *argv[]) : m_argv(argv)
{
    std::cout << "Before: ";
    for (int i = 1; argv[i]; i++)
        std::cout << argv[i] << " ";
    std::cout << "\n";

    input_contains_duplicates(argv);
}

/* Copy constructor */
PmergeMe::PmergeMe(const PmergeMe &source) : m_comparisons_vector{source.m_comparisons_vector}, m_vector{source.m_vector}, m_deque{source.m_deque}, m_argv{source.m_argv}
{
}

/* Copy assignment operator overload*/
PmergeMe &PmergeMe::operator=(const PmergeMe &source)
{
    // self-assignment check
    if (this == &source)
        return *this;

    m_comparisons_vector = source.m_comparisons_vector;
    m_vector = source.m_vector;
    m_deque = source.m_deque;
    m_argv = source.m_argv;

    // return the existing object so we can chain this operator
    return *this;
}

/* Destructor */
PmergeMe::~PmergeMe(void) {}

bool PmergeMe::input_contains_duplicates(char *argv[])
{
    std::unordered_set<int> numbers{};

    for (int i = 1; argv[i]; i++)
    {
        auto result = numbers.insert(stoi_wrapper(argv[i]));
        if (!result.second)
            throw std::invalid_argument("Input must not contain duplicate numbers");
    }
    return false;
}

int PmergeMe::stoi_wrapper(const char *s)
{
    std::size_t pos{};

    const int i{std::stoi(s, &pos)};
    if (pos != std::strlen(s))
        throw std::invalid_argument("Input must contain digits only");
    if (i <= 0)
        throw std::invalid_argument("Input must be postive");

    return i;
}

/* VECTOR */
void PmergeMe::args_to_vector(void)
{
    for (int i = 1; m_argv[i]; i++)
        m_vector.push_back(stoi_wrapper(m_argv[i]));
}

std::vector<std::pair<int, int>> PmergeMe::pairs_generate_vector(int *remainder)
{
    std::vector<std::pair<int, int>> pairs{};

    if (m_vector.size() % 2 != 0)
    {
        *remainder = m_vector.back();
        m_vector.pop_back();
    }
    for (size_t i = 0; i < m_vector.size(); i += 2)
        pairs.push_back(std::make_pair(m_vector[i], m_vector[i + 1]));

    return pairs;
}

std::vector<int> PmergeMe::largest_generate_vector(const std::vector<std::pair<int, int>> &pairs)
{
    std::vector<int> largest{};

    for (const auto &elem : pairs)
        largest.push_back(elem.second);

    return largest;
}

std::vector<int> PmergeMe::pend_generate_vector(const std::vector<std::pair<int, int>> &pairs)
{
    std::vector<int> pend{};

    for (const auto &elem : m_vector)
    {
        for (const auto &pair : pairs)
        {
            if (elem == pair.second)
            {
                pend.push_back(pair.first);
                break;
            }
        }
    }

    return pend;
}

std::vector<int> PmergeMe::insert_seq_generate_vector(size_t pend_chain_len)
{
    std::vector<int> insert_seq{};

    if (!pend_chain_len)
        return insert_seq;

    constexpr std::uint_least64_t jacobsthal_diff[] = {
        2u, 2u, 6u, 10u, 22u, 42u, 86u, 170u, 342u, 682u, 1366u,
        2730u, 5462u, 10922u, 21846u, 43690u, 87382u, 174762u, 349526u, 699050u,
        1398102u, 2796202u, 5592406u, 11184810u, 22369622u, 44739242u, 89478486u,
        178956970u, 357913942u, 715827882u, 1431655766u, 2863311530u, 5726623062u,
        11453246122u, 22906492246u, 45812984490u, 91625968982u, 183251937962u,
        366503875926u, 733007751850u, 1466015503702u, 2932031007402u, 5864062014806u,
        11728124029610u, 23456248059222u, 46912496118442u, 93824992236886u, 187649984473770u,
        375299968947542u, 750599937895082u, 1501199875790165u, 3002399751580331u,
        6004799503160661u, 12009599006321322u, 24019198012642644u, 48038396025285288u,
        96076792050570576u, 192153584101141152u, 384307168202282304u, 768614336404564608u,
        1537228672809129216u, 3074457345618258432u, 6148914691236516864u};

    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    int start = 2;
    bool is_complete = false;
    std::vector<int> tmp;
    std::size_t jacobsthal_diff_length = sizeof(jacobsthal_diff) / sizeof(jacobsthal_diff[0]);

    while (i < jacobsthal_diff_length)
    {
        while (j < jacobsthal_diff[i])
        {
            start = start + 1;
            tmp.insert(tmp.begin(), start);
            j += 1;
            k += 1;
            if (k == pend_chain_len)
            {
                is_complete = true;
                break;
            }
        }
        for (int elem : tmp)
            insert_seq.push_back(elem);
        tmp.clear();
        if (is_complete)
            break;
        j = 0;
        i += 1;
    }
    i += 1;

    return insert_seq;
}

void PmergeMe::ford_johnson_algo_vector(void)
{
    if (m_vector.size() <= 1)
        return;

    int remainder{0};

    std::vector<std::pair<int, int>> pairs = PmergeMe::pairs_generate_vector(&remainder);
    PmergeMe::pairs_sort_inner(pairs);

    m_vector = PmergeMe::largest_generate_vector(pairs);
    PmergeMe::ford_johnson_algo_vector();

    std::vector<int> pend = PmergeMe::pend_generate_vector(pairs);
    if (remainder)
        pend.push_back(remainder);

    m_vector.insert(m_vector.begin(), pend.front());
    pend.erase(pend.begin());

    std::vector<int> insert_seq = PmergeMe::insert_seq_generate_vector(pend.size());

    int inserted = 0;
    for (auto element : insert_seq)
    {
        int position = PmergeMe::ft_bisect_left(
            m_vector,
            pend[element - 3],
            0,
            element + inserted - 1);
        m_vector.insert(m_vector.begin() + position, pend[element - 3]);
        inserted++;
    }
}

/* DEQUE */
void PmergeMe::args_to_deque(void)
{
    for (int i = 1; m_argv[i]; i++)
        m_deque.push_back(stoi_wrapper(m_argv[i]));
}

std::deque<std::pair<int, int>> PmergeMe::pairs_generate_deque(int *remainder)
{
    std::deque<std::pair<int, int>> pairs{};

    if (m_deque.size() % 2 != 0)
    {
        *remainder = m_deque.back();
        m_deque.pop_back();
    }
    for (size_t i = 0; i < m_deque.size(); i += 2)
        pairs.push_back(std::make_pair(m_deque[i], m_deque[i + 1]));

    return pairs;
}

std::deque<int> PmergeMe::largest_generate_deque(const std::deque<std::pair<int, int>> &pairs)
{
    std::deque<int> largest{};

    for (const auto &elem : pairs)
        largest.push_back(elem.second);

    return largest;
}

std::deque<int> PmergeMe::pend_generate_deque(const std::deque<std::pair<int, int>> &pairs)
{
    std::deque<int> pend{};

    for (const auto &elem : m_deque)
    {
        for (const auto &pair : pairs)
        {
            if (elem == pair.second)
            {
                pend.push_back(pair.first);
                break;
            }
        }
    }

    return pend;
}

std::deque<int> PmergeMe::insert_seq_generate_deque(size_t pend_chain_len)
{
    std::deque<int> insert_seq{};

    if (!pend_chain_len)
        return insert_seq;

    constexpr std::uint_least64_t jacobsthal_diff[] = {
        2u, 2u, 6u, 10u, 22u, 42u, 86u, 170u, 342u, 682u, 1366u,
        2730u, 5462u, 10922u, 21846u, 43690u, 87382u, 174762u, 349526u, 699050u,
        1398102u, 2796202u, 5592406u, 11184810u, 22369622u, 44739242u, 89478486u,
        178956970u, 357913942u, 715827882u, 1431655766u, 2863311530u, 5726623062u,
        11453246122u, 22906492246u, 45812984490u, 91625968982u, 183251937962u,
        366503875926u, 733007751850u, 1466015503702u, 2932031007402u, 5864062014806u,
        11728124029610u, 23456248059222u, 46912496118442u, 93824992236886u, 187649984473770u,
        375299968947542u, 750599937895082u, 1501199875790165u, 3002399751580331u,
        6004799503160661u, 12009599006321322u, 24019198012642644u, 48038396025285288u,
        96076792050570576u, 192153584101141152u, 384307168202282304u, 768614336404564608u,
        1537228672809129216u, 3074457345618258432u, 6148914691236516864u};

    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    int start = 2;
    bool is_complete = false;
    std::deque<int> tmp;
    std::size_t jacobsthal_diff_length =
        sizeof(jacobsthal_diff) / sizeof(jacobsthal_diff[0]);

    while (i < jacobsthal_diff_length)
    {
        while (j < jacobsthal_diff[i])
        {
            start = start + 1;
            tmp.insert(tmp.begin(), start);
            j += 1;
            k += 1;
            if (k == pend_chain_len)
            {
                is_complete = true;
                break;
            }
        }
        for (int elem : tmp)
            insert_seq.push_back(elem);
        tmp.clear();
        if (is_complete)
            break;
        j = 0;
        i += 1;
    }
    i += 1;

    return insert_seq;
}

void PmergeMe::ford_johnson_algo_deque(void)
{
    if (m_deque.size() <= 1)
        return;

    int remainder{0};
    std::deque<std::pair<int, int>> pairs = PmergeMe::pairs_generate_deque(&remainder);
    PmergeMe::pairs_sort_inner(pairs);

    m_deque = PmergeMe::largest_generate_deque(pairs);
    PmergeMe::ford_johnson_algo_deque();

    std::deque<int> pend = PmergeMe::pend_generate_deque(pairs);
    if (remainder)
        pend.push_back(remainder);

    m_deque.insert(m_deque.begin(), pend.front());
    pend.erase(pend.begin());

    std::deque<int> insert_seq = PmergeMe::insert_seq_generate_deque(pend.size());

    int inserted = 0;
    for (auto element : insert_seq)
    {
        int position = PmergeMe::ft_bisect_left(
            m_deque,
            pend[element - 3],
            0,
            element + inserted - 1);
        m_deque.insert(m_deque.begin() + position, pend[element - 3]);
        inserted++;
    }
}