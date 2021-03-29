// Avoid "using namespace std;" at all costs. Prefer typing out "std::"
// in front of each identifier, but "using std::NAME" isn't (very) dangerous.
#include <numeric>    //inner_product
#include <functional> //plus, equal_to, not2
#include <stdexcept>
#include <iostream>
using std::cout;
using std::cin;
#include <fstream>
using std::ifstream;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <iterator>
using std::istream_iterator;
#include <algorithm>
using std::copy;

#include<bits/stdc++.h>

//g++-4.8 -std=c++11 -O3 -fopenmp -msse2 -Wall -pedantic -pthread main.cpp && ./a.out
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
 
// function to calculate Hamming distance
int hammingDist(char *str1, char *str2)
{
    int i = 0, count = 0;
    while (str1[i] != '\0')
    {
        if (str1[i] != str2[i])
            count++;
        i++;
    }
    return count;
}

unsigned int hd(const std::string& s1, const std::string& s2)
{
    return std::inner_product(
        s1.begin(), s1.end(), s2.begin(),
        0, std::plus<unsigned int>(),
        std::not2(std::equal_to<std::string::value_type>())
    );
}

int hamming_distance_fix_omp(int* a, int*b, int n) {
    int disti = 0;
    #pragma omp parallel for reduction(+:disti)
    for(int i=0; i<n; i++) {
       disti += (a[i] != b[i]);
    }
    return 1.0*disti/n;
}

int main()
{

    // Store the words from the two files into these two vectors
    vector<string> DataArray;
    vector<string> QueryArray;

    // Create two input streams, opening the named files in the process.
    // You only need to check for failure if you want to distinguish
    // between "no file" and "empty file". In this example, the two
    // situations are equivalent.
    ifstream myfile("dictionary.txt"); 
    ifstream qfile("queries.txt");

    // std::copy(InputIt first, InputIt last, OutputIt out) copies all
    //   of the data in the range [first, last) to the output iterator "out"
    // istream_iterator() is an input iterator that reads items from the
    //   named file stream
    // back_inserter() returns an interator that performs "push_back"
    //   on the named vector.
    copy(istream_iterator<string>(myfile),
         istream_iterator<string>(),
         back_inserter(DataArray));
    copy(istream_iterator<string>(qfile),
         istream_iterator<string>(),
         back_inserter(QueryArray));

    int i = 0;
    int j = 0;

    int sizeQ = QueryArray.size();
    int sizeD = DataArray.size();

    int matres[sizeQ][21];
    memset(matres, 0, sizeof(matres));

    int matmat[sizeQ][sizeD];
    memset(matmat, 0, sizeof(matmat));

    #pragma omp parallel for shared(matres,matmat)
    for (i = 0; i < sizeQ; ++i){

        int j1;
        //#pragma omp parallel for shared(matres) private(i,j) schedule(static, DataArray.size())
        //#pragma omp parallel for num_threads( 40 )
        //#pragma omp parallel for shared(matres)
        for (j1 = 0; j1 < sizeD; ++j1){

            int dist = hd(QueryArray[i], DataArray[j1]);
            
            matres[i][dist]++;

            matmat[i][j1]+=dist;

        }
    }

    std::ofstream outfile;
    outfile.open ("Hist.txt");

    for (i = 0; i != sizeQ; ++i){

        outfile << QueryArray[i];

        for (j = 0; j != 5; ++j){
            outfile << ' ' << matres[i][j];
        }

        outfile << '\n';
    }

    outfile.close();

    std::ofstream matfile;
    matfile.open ("Matches.txt");

        for (i = 0; i != sizeQ; ++i){

        matfile << QueryArray[i];
        
        for (j = 0; j != sizeD; ++j){
            
            if(matmat[i][j] < 5){
            matfile << ' ' << matmat[i][j] << ':' << DataArray[j];
            }
        }
        
        matfile << '\n';

    }

    matfile.close();

    return 0;

}