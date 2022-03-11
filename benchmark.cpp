//#include <woanmeo11>

#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <unistd.h>

const int N_TESTCASE = 10;
const int TESTCASE_SIZE = 1e6;

#include "gentests.h"
#include "quicksort.h"
#include "heapsort.h"
#include "mergesort.h"
#include "stl_sort.h"

using namespace std;

int n;
long long raw_input[TESTCASE_SIZE], sorted_arr[TESTCASE_SIZE];
long long temp_arr[TESTCASE_SIZE];

bool enable_all, enable_quicksort, enable_heapsort, enable_mergesort, enable_stlsort, enable_gentests;

void read_testcase(int test_number) {
    ifstream inp((to_string(test_number) + ".inp").c_str());
    inp >> n;
    for (int i = 0; i < n; ++i)
        inp >> raw_input[i];
    inp.close();

    ifstream ans((to_string(test_number) + ".ans").c_str());
    for (int i = 0; i < n; ++i)
        ans >> sorted_arr[i];
    ans.close();
}

// return runtime of sorting function in milisecond
double benchmark(void (*sort_func)(long long arr[], int n)) {
    for (int i = 0; i < n; ++i)
        temp_arr[i] = raw_input[i];

    clock_t t_begin = clock();
    sort_func(temp_arr, n);
    clock_t t_end = clock();

    for (int i = 0; i < n; ++i)
        assert(temp_arr[i] == sorted_arr[i]);

    return double(t_end - t_begin) * 1000 / CLOCKS_PER_SEC;
}

#define print(s) cout << "│ " << left << setw(10) << s;

void print_table() {
    print("Test case");

    if (enable_quicksort || enable_all)
        print("Quicksort");
    if (enable_heapsort || enable_all)
        print("Heapsort");
    if (enable_mergesort || enable_all)
        print("Mergesort");
    if (enable_stlsort || enable_all)
        print("C++ STL Sort");

    printf("\n├───────────");
    if (enable_quicksort || enable_all)
        printf("┼───────────");
    if (enable_heapsort || enable_all)
        printf("┼───────────");
    if (enable_mergesort || enable_all)
        printf("┼───────────");
    if (enable_stlsort || enable_all)
        printf("┼──────────────");

    putchar(10);
}

void display_help() {
    puts("Usage: benchmark [OPTION]...");
    puts("Measure execution time of common sorting algorithms.\n");

    puts(" --gentests\tgenerate test cases\n");

    puts(" --all\t\tequivalent to --heapsort --mergesort --quicksort --stlsort");
    puts(" --heapsort\tmeasure execution time of Heapsort");
    puts(" --mergesort\tmeasure execution time of Mergesort");
    puts(" --quicksort\tmeasure execution time of Quicksort");
    puts(" --stlsort\tmeasure execution time of std::sort of C++ STL");
}

void handle_argv(int argc, char *argv[]) {
    if (argc == 1) {
        display_help();
        exit(0);
    }
    else {
        for (int i = 1; i < argc; ++i) {
            if (strcmp(argv[i],"--gentests") == 0)
                enable_gentests = true;
            else if (strcmp(argv[i],"--quicksort") == 0)
                enable_quicksort = true;
            else if (strcmp(argv[i],"--heapsort") == 0)
                enable_heapsort = true;
            else if (strcmp(argv[i],"--mergesort") == 0)
                enable_mergesort = true;
            else if (strcmp(argv[i],"--stlsort") == 0)
                enable_stlsort = true;
            else if (strcmp(argv[i], "--all") == 0)
                enable_all = true;
            else {
                printf("Unknown argument '%s', run program without arguments to display help.\n", argv[i]);
                exit(0);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    handle_argv(argc, argv);

    if (enable_gentests)
        gentests();

    if (enable_all || enable_quicksort || enable_heapsort || enable_mergesort || enable_stlsort) {
        chdir("testcases");

        print_table();

        for (int t = 0; t < N_TESTCASE; ++t) {
            read_testcase(t);
            print(t);

            if (enable_quicksort || enable_all)
                print(benchmark(quicksort));

            if (enable_heapsort || enable_all)
                print(benchmark(heapsort));

            if (enable_mergesort || enable_all)
                print(benchmark(mergesort));

            if (enable_stlsort || enable_all)
                print(benchmark(stl_sort));

            putchar(10);
        }
    }
}
