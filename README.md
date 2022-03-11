# Benchmark sorting algorithms

## Description

This project is to measure the execution time of Quicksort, Heapsort, Mergesort and `std::sort` of C++ STL.  

## Results

The first two test cases are increasing array and decreasing array. The others are random array.

### Table of execution time:

| Test case | Quicksort | Heapsort | Mergesort | C++ STL Sort
|-----------|-----------|----------|-----------|--------------
| 0         | 0.023261  | 0.043582 | 0.020905  | 0.008432
| 1         | 0.022255  | 0.050116 | 0.025706  | 0.005233
| 2         | 0.07072   | 0.104661 | 0.080823  | 0.0506
| 3         | 0.070442  | 0.11108  | 0.08002   | 0.049978
| 4         | 0.070316  | 0.106772 | 0.080803  | 0.050588
| 5         | 0.071768  | 0.111115 | 0.08086   | 0.051074
| 6         | 0.070229  | 0.109914 | 0.08092   | 0.051211
| 7         | 0.069701  | 0.101542 | 0.080143  | 0.053128
| 8         | 0.069846  | 0.122158 | 0.080362  | 0.049328
| 9         | 0.070507  | 0.113921 | 0.079885  | 0.050674

### Chart of execution time:

<div align="center"> 
    <img src="chart.png" width="1000">
</div>

### Table of instructions, cache-misses (less is better)

| Algorithm    | Instructions | Cache-misses
|--------------|--------------|-------------
| Quicksort    | 19671795229  | 1559398
| Heapsort     | 22425140786  | 78402105
| Mergesort    | 20597828074  | 4425107
| C++ STL Sort | 17847755349  | 1039317

### This benchmarking is run on:
* **OS**: Gentoo/Linux x86_64
* **Kernel**: Kernel: 5.15.23-gentoo-dist
* **CPU**: AMD Ryzen 5 5600H with Radeon Graphics (12) @ 3.300GHz
* **GPU**: AMD ATI Radeon RX 5500/5500M / Pro 5500M
* **GPU**: AMD ATI 07:00.0 Cezanne
* **Memory**: 8GB DDR4
* **g++ version**: (Gentoo 11.2.1_p20220115 p4) 11.2.1

According to those infomations above we can easily realize that `std::sort` of C++ STL is far better than its opponents.

### `std::sort`

It seems like the are all average `O(N*log(N))` complexity, howerver, `std::sort` of C++ STL is better than the others. 
Why `std::sort` is so quick? Because most of `std::sort` implementations use Quicksort, (or usually a hybrid algorithm like Introsort, which combines Quicksort, Heapsort and Insertion sort).

> So, `std::sort` is also Quicksort but better :))

### Why Quicksort is faster than Mergesort?

Quicksort is faster than Mergesort because its cache performance is higher (less cache-misses) and it doesn't require extra space for merging operation as Mergesort.  
Sometime, Quicksort has `O(N^2)` in the worst case but we can avoid it by choosing random pivot.

### How about Quicksort and Heapsort?

When both algorithms have same complexity (`α*N*log(N)` for the Quicksort, and `β*N*log(N)` for the Heapsort), the Quicksort is faster because he has a proportionnality coefficient which equals the half of the Heapsort’s proportionnality coefficient; mathematically, we have:

```
α = β / 2
```

## How to run this project?

Clone the project and build it:

```
$ git clone https://github.com/woanmeo11/sorting-benchmark.git
$ cd sorting-benchmark
$ ./build.sh
```

To display help, run the binary without any arguments:

```
$ ./benchmark
Usage: benchmark [OPTION]...
Measure execution time of common sorting algorithms.

 --gentests	generate test cases

 --all		    equivalent to --heapsort --mergesort --quicksort --stlsort
 --heapsort	    measure execution time of Heapsort
 --mergesort	measure execution time of Mergesort
 --quicksort	measure execution time of Quicksort
 --stlsort	    measure execution time of std::sort of C++ STL
```

Then run `benchmark --gentests` to generate test cases:

```
$ ./benchmark --gentests
[*] Creating directory...
[*] Generating test case 0...
[*] Generating test case 1...
[*] Generating test case 2...
[*] Generating test case 3...
[*] Generating test case 4...
[*] Generating test case 5...
[*] Generating test case 6...
[*] Generating test case 7...
[*] Generating test case 8...
[*] Generating test case 9...
```

### Measure the execution time

Run `benchmark --all` to view the benchmarking progress:

```
$ ./benchmark --all
│ Test case │ Quicksort │ Heapsort  │ Mergesort │ C++ STL Sort
├───────────┼───────────┼───────────┼───────────┼──────────────
│ 0         │ 0.023261  │ 0.043582  │ 0.020905  │ 0.008432
│ 1         │ 0.022255  │ 0.050116  │ 0.025706  │ 0.005233
│ 2         │ 0.07072   │ 0.104661  │ 0.080823  │ 0.0506
│ 3         │ 0.070442  │ 0.11108   │ 0.08002   │ 0.049978
│ 4         │ 0.070316  │ 0.106772  │ 0.080803  │ 0.050588
│ 5         │ 0.071768  │ 0.111115  │ 0.08086   │ 0.051074
│ 6         │ 0.070229  │ 0.109914  │ 0.08092   │ 0.051211
│ 7         │ 0.069701  │ 0.101542  │ 0.080143  │ 0.053128
│ 8         │ 0.069846  │ 0.122158  │ 0.080362  │ 0.049328
│ 9         │ 0.070507  │ 0.113921  │ 0.079885  │ 0.050674
```

### Show the number of instructions and cache-misses

To view the number of instructions and cache-misses, we use a tool called `perf`. `--quicksort` option is used to investigate only Quicksort algorithm.

```
$ perf stat -e instructions,cache-misses ./benchmark --quicksort
│ Test case │ Quicksort
├───────────┼───────────
│ 0         │ 0.023233
│ 1         │ 0.021968
│ 2         │ 0.070674
│ 3         │ 0.072379
│ 4         │ 0.070832
│ 5         │ 0.07087
│ 6         │ 0.070956
│ 7         │ 0.070517
│ 8         │ 0.069469
│ 9         │ 0.07105

Performance counter stats for './benchmark --quicksort':

    19671795229      instructions:u
        1559398      cache-misses:u

    1.576466517 seconds time elapsed

    1.527792000 seconds user
    0.046613000 seconds sys
```

# References:

* [heap-quick-comparison.pdf](https://orbi.uliege.be/bitstream/2268/19656/1/heap-quick-comparison.pdf)
* [Memory location matters for performance](https://pythonspeed.com/articles/performance-memory-locality/)