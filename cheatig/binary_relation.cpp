#include "binary_relation.h"
#include <iostream>
#include <algorithm>
bool comp(std::vector<int> first, std::vector<int> second)
{
    if (first.at(1) - second.at(1))
    {
        if (first.at(1) > second.at(1))
            return 1;
        else
            return 0;
    }
    else if (first.at(1) == second.at(1))
    {
        if (first.at(0) < second.at(0))
            return 1;
        else
            return 0;
    }
}
bool Binary_relation::relation(int first, int second)
{
    int b = first % 10;
    int a = first / 10;
    int d = second % 10;
    int c = second / 10;
    //std::cout << "a = " << a << " b = " << b;
    if (a >= c)
    {
        if (b >= d)
            return true;
    }
    return false;
}

void Binary_relation::enter()
{
    std::cout << "Enter the cardinality: ";
    std::cin >> cardinality;
    std::cout << "Enter your set: ";
    int value = 0;
    for (int i = 0; i < cardinality; i++)
    {
        std::cin >> value;
        M.push_back(value);
    }
    std::cout << "Warning! We will sort it!\n";
    std::sort(M.begin(), M.end());
}
void Binary_relation::calculate_matrix()
{
    matrix.resize(cardinality);
    for (int i = 0; i < cardinality; i++)
    {
        for (int j = 0; j < cardinality; j++)
        {
            //std::cout << M.at(i) << " R " << M.at(j) << " = " << relation(M.at(i), M.at(j)) << "\n";
            matrix.at(i).push_back(relation(M.at(i), M.at(j)));
        }
    }
    std::cout << "\nThere are your sorted M and your matrix:\n";
    out();
}
void Binary_relation::out()
{
    std::cout << "\x1b[33mM \x1b[0m{\x1b[32m";
    for (auto i: M)
    {
        std::cout << i << ", ";
    }
    std::cout << "\b\b\x1b[0m}\n";
    for (auto i : matrix)
    {
        for (auto j : i)
        {
            std::cout << j << " ";
        }
        std::cout << "\n";
    }
}
Binary_relation::Binary_relation()
{
    enter();
    calculate_matrix();
    solve_2_3();
    solve_4();
}

void Binary_relation::solve_2_3()
{
    bool rez = matrix.at(0).at(0);
    bool reflex = 0;
    for (int i = 0; i < cardinality; i++)//calculate reflex
    {
        rez = rez && matrix.at(i).at(i);
        if (rez == 0)
        {
            std::cout << "Is not mreflexive, cause " << M.at(i) << "R" << M.at(i) << " == 0\n";
            break;
        }
    }
    if (rez)
    {
        std::cout << "\x1b[32mReflexive\x1b[0m, cause Va aRa == 1\n";
        reflex = 1;
    }

    rez = 0;
    bool irreflex = 0;
    for (int i = 0; i < cardinality; i++)//calculate irreflex
    {
        rez = rez || matrix.at(i).at(i);
        if (rez)
        {
            std::cout << "Is not \x1b[31mirreflexive\x1b[0m, cause " << M.at(i) << "R" << M.at(i) << " == 1\n";
            break;
        }
    }
    if (!rez)
    {
        std::cout << "\x1b[32mIrreflexive\x1b[0m, cause Va aRa == 0\n";
        irreflex = 1;
    }

    rez = 1;
    bool sym = 0;
    for (int i = 0; i < cardinality && rez; i++)
    {
        for (int j = i; j < cardinality; j++)
        {
            if (!(matrix.at(i).at(j) == matrix.at(j).at(i)))
            {
                std::cout << "Is not \x1b[31msymmetrical\x1b[0m, cause martix is not symmetrical\n";
                rez = 0;
                break;
            }

        }
    }
    if (rez)
    {
        std::cout << "\x1b[32mSymmetrical\x1b[0m, cause martix is symmetrical\n";
        sym = 1;
    }
    
    rez = 1;
    for (int i = 0; i < cardinality && rez; i++)
    {
        for (int j = i; j < cardinality; j++)
        {
            if (matrix.at(i).at(j) && matrix.at(j).at(i))
            {
                if (M.at(i) != M.at(i))
                {
                    rez = 0;
                    std::cout << "Is not \x1b[31mantisymmetric\x1b[0m, cause " << M.at(i) << "R" << M.at(j) << " == 1, but " << M.at(i) << " != " << M.at(j) << "\n";
                    break;
                }
            }
        }
    }
    if (rez)
    {
        std::cout << "\x1b[32mAntisymmetric\x1b[0m, cause V x, y, e M (xRy && yRx) => x == y\n";
    }

    if (rez && irreflex)
        std::cout << "\x1b[32mAsymmetric\x1b[0m, cause Antisymmetric && Irreflexive\n";
    else
        std::cout << "Is not \x1b[31mAsymmetric\x1b[0m, cause !(Antisymmetric && Irreflexive)\n";

    std::vector<std::vector <int>> qrt;
    qrt.resize(cardinality);
    for (int i = 0; i < cardinality; i++)
    {
        qrt.at(i).resize(cardinality);
    }
    rez = 1;
    std::cout << "matrix^2:\n";
    for (int i = 0; i < cardinality; i++) 
    {
        for (int j = 0; j < cardinality; j++) 
        {
            qrt.at(i).at(j) = 0;
            for (int k = 0; k < cardinality; k++)
            {
                qrt.at(i).at(j) += matrix.at(i).at(k) * matrix.at(k).at(j);
            }
            if (matrix.at(i).at(i) == 0 && qrt.at(i).at(j) != 0)
            {
                rez = 0;
                std::cout << "\x1b[31m" << qrt.at(i).at(j) << "\x1b[0m ";
            }
            else
                std::cout << qrt.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
    if (rez)
        std::cout << "\x1b[32mTransitive\x1b[0m. See proof above\n";
    else
        std::cout << "mIs not \x1b[31transitive\x1b[0m. See proof above\n";

    if ((reflex && sym) && rez)
        std::cout << "Is an \x1b[32mequivalence\x1b[0m relation, cause Reflexive && Symmetrical && Transitive == true\n";
    else
        std::cout << "Is not an \x1b[31mequivalence\x1b[0m relation, cause Reflexive && Symmetrical && Transitive == false\n";

}
void Binary_relation::solve_4()
{
    std::cout << "\nTry topological order... ";
    std::vector<std::vector<int>> order;
    order.resize(cardinality);
    for (int i = 0; i < cardinality; i++)
    {
        order.at(i).resize(2);
        order.at(i).at(0) = M.at(i);
        order.at(i).at(1) = 0;
    }

    for (int i = 0; i < cardinality; i++)
    {
        for (int j = 0; j < cardinality; j++)
        {
            order.at(i).at(1) += matrix.at(j).at(i);
        }
    }
    std::sort(order.begin(), order.end(), comp);
    std::cout << " Complete. \nSorted order: \x1b[33mM \x1b[0m{\x1b[32m";
    for (int i = 0; i < cardinality; i++)
    {
        std::cout << order.at(i).at(0) << ", ";
    }
    std::cout << "\b\b\x1b[0m}";
}
