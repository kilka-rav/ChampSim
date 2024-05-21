import os
import subprocess

src_dir = r'./../traces'
name_files = []

def collect_benchmarks(path):
    res = []
    files = os.listdir(path)
    for name in files:
        bench_path = f'{path}/{name}'
        res.append(bench_path)
    return res

def launch_bench(benchmark):
    print(benchmark)
    res_file = benchmark[benchmark.rindex("/") + 1:benchmark.find(".xz")]
    command = "./../bin/champsim --warmup_instructions 5000000 --simulation_instructions 20000000 " + benchmark
    dump = " > ./../stats/" + res_file
    command = command + dump
    os.system(command=command)
    print(command)

def collect_statistics():
    pass

def main():
    print("start")
    path = src_dir
    benchmarks = collect_benchmarks(path)
    print(benchmarks)
    for bench in benchmarks:
        launch_bench(bench)
    collect_statistics()
    print("finish")
main()