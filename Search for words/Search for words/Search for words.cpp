#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>


template < typename TKey, typename TValue >
class descending_pair_value_comparer : public std::binary_function < std::pair<TKey, TValue>, std::pair<TKey, TValue>, bool >
{
public:
    bool operator() (const std::pair<TKey, TValue>& p1, const const std::pair<TKey, TValue>& p2)
    {
        return p1.second > p2.second;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    int amount;
    std::string word;
    std::ifstream ifs("pg11.txt");

    std::cout << "Введите чисто слов которое хотите найти: ";
    std::cin >> amount;

    if (ifs.is_open())
    {
        std::map<std::string, int> words;

        while (ifs >> word)
        {
            ++words[word];
        }

        std::vector<std::pair<std::string, int>> vector;
        std::copy(words.cbegin(), words.cend(), std::back_insert_iterator<std::vector<std::pair<std::string, int>>>(vector));

        std::sort(vector.begin(), vector.end(), descending_pair_value_comparer<std::string, int>());

        for (std::vector<std::pair<std::string, int>>::size_type i = 0; i < amount; i++)
        {
            std::cout << vector[i].second << ": " << vector[i].first << std::endl;
        }

        ifs.close();
    }
    else
    {
        std::cerr << "Файл не найден или не возможно открыть. " << std::endl;
        return 1;
    }

#ifdef _MSC_VER
    system("pause");
#endif

    return 0;
}