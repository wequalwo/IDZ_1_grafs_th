#pragma once
#include <vector>
class Binary_relation
{
private:
	std::vector<int> M;
	std::vector<std::vector<int>> matrix;
	int cardinality;
	bool relation(int a, int b);
	void enter();
	void calculate_matrix();
	void solve_2_3();
	void solve_4();
public:
	Binary_relation();
	void out();
};

