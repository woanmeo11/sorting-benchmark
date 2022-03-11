#ifndef GENTESTS_H_INCLUDED
#define GENTESTS_H_INCLUDED

#include <algorithm>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>

#include "rewritten_random.h"

using namespace std;

const long long MIN_VALUE = -1e9;
const long long MAX_VALUE = 1e9;

long long *test_arr = new long long [TESTCASE_SIZE];

void gen_input(int test_number) {
    ofstream out((to_string(test_number) + ".inp").c_str());

    out << TESTCASE_SIZE << '\n';

    for (int i = 0; i < TESTCASE_SIZE; ++i)
        test_arr[i] = random(MIN_VALUE, MAX_VALUE);
    if (test_number < 2) {
        if (test_number == 0)
            sort(test_arr, test_arr + TESTCASE_SIZE);
        else
            sort(test_arr, test_arr + TESTCASE_SIZE, greater<long long>());
    }

    for (int i = 0; i < TESTCASE_SIZE; ++i)
        out << test_arr[i] << ' ';

    out.close();
}

void gen_answer(int test_number) {
    ofstream ans((to_string(test_number) + ".ans").c_str());

    sort(test_arr, test_arr + TESTCASE_SIZE);
    for (int i = 0; i < TESTCASE_SIZE; ++i)
        ans << test_arr[i] << ' ';

    ans.close();
}

void gentests() {
    puts("[*] Creating directory...");

    mkdir("testcases", 0755);
    chdir("testcases");

    for (int t = 0; t < N_TESTCASE; ++t) {
        printf("[*] Generating test case %d...\n", t);
        gen_input(t);
        gen_answer(t);
    }

    delete [] test_arr;
}

#endif // GENTESTS_H_INCLUDED
