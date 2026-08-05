#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <list>
# include <string>
# include <vector>

class PmergeMe
{
private:
	struct Pair
	{
		int	small;
		int	large;
	};

	PmergeMe(void);
	PmergeMe(const PmergeMe &other);
	~PmergeMe(void);

	PmergeMe	&operator=(const PmergeMe &other);

	static void							insertVector(std::vector<int> &chain, int value);
	static void							insertPairVector(std::vector<Pair> &chain, const Pair &value);
	static void							insertList(std::list<int> &chain, int value);
	static void							insertPairList(std::list<Pair> &chain, const Pair &value);
	static std::vector<unsigned int>	buildInsertionOrder(unsigned int size);
	static void							sortPairsVector(std::vector<Pair> &pairs);
	static void							sortPairsList(std::list<Pair> &pairs);
	static int							parsePositiveInt(const std::string &text);

public:
	static std::vector<int>	parseVector(int argc, char **argv);
	static std::list<int>	parseList(int argc, char **argv);
	static void				sortVector(std::vector<int> &values);
	static void				sortList(std::list<int> &values);
};

#endif
