#!/usr/bin/env python3

# Copyright (c) 2021 R. Tohid (@rtohid)
# Copyright (c) 2021 Shahrzad Shirzad
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

import glob
import numpy
import os
import re
import sys

from matplotlib import pyplot as plt
from pathlib import Path
from types import FunctionType
from typing import List


def get_filename(full_path: str) -> str:
    return os.path.basename(full_path)


def get_logs(logs_directory: str,
             logs_suffix: str = 'log',
             recursively: bool = True) -> List:
    return glob.glob(logs_directory + f'/**/*.{logs_suffix}',
                     recursive=recursively)


def get_execution_times(filename: str) -> numpy.array:
    with open(filename, 'r') as content:
        log = content.read()

    # lines containing the execution times
    time_lines = re.compile('Manually-tuned time: \d+\.\d+')
    times = numpy.asarray(
        [float(time.split(': ')[-1]) for time in time_lines.findall(log)])
    return times


class LogFile:
    def __init__(self, full_path: str) -> None:
        self.full_path = full_path
        self.name = get_filename(full_path)

    def rename(self, new_name: str) -> None:
        full_path = self.full_path.replace(self.name, new_name)
        os.rename(self.full_path, full_path)

        self.name = get_filename(full_path)
        self.full_path = full_path

    def __str__(self) -> str:
        str_ = f"file name: {self.name}\nfile path: {self.full_path}\n"
        return str_


class Run:
    def __init__(self, log_file: LogFile) -> None:
        no_suffix = '.'.join(log_file.name.split('.')[:-1])
        (machine, node, runtime, app, num_threads) = no_suffix.split('--')
        self.file = log_file
        self.machine = machine
        self.node = node
        self.app = app
        self.num_threads = int(num_threads)
        self.runtime = runtime

        self.execution_times: numpy.array = None
        self.throughputs: numpy.array = None

    def extract_times(self, time_extractor: FunctionType) -> numpy.array:
        self.execution_times = time_extractor(self.file.full_path)

    def get_average_time(self) -> float:
        return numpy.mean(self.execution_times)


class Profiler:
    def __init__(self, log_files: List) -> None:
        self.runs = [Run(a_log) for a_log in log_files]
        [run.extract_times(get_execution_times) for run in self.runs]
        # [print(run.file.name, run.get_average_time()) for run in self.runs]

    def plot(self):
        hpx_runs = sorted([run for run in self.runs if run.runtime == 'hpx'],
                          key=lambda run: run.num_threads)
        halide_runs = sorted(
            [run for run in self.runs if run.runtime == 'halide'],
            key=lambda run: run.num_threads)

        runtimes = [halide_runs, hpx_runs]

        if not halide_runs or not hpx_runs:
            print(f"Nothing to plot; no Halide or HPX runs:")
            print(f"Halide runs: {halide_runs}")
            print(f"HPX runs: {hpx_runs}")
            return

        for runtime in runtimes:
            runtime_name = runtime[0].runtime
            threads = [run.num_threads for run in runtime]
            times = [run.get_average_time() for run in runtime]

            plt.figure(1)
            plt.scatter(threads, times, label=runtime_name)
            plt.legend(bbox_to_anchor=(.8, .95), loc=2, borderaxespad=0.)
            plt.xlabel('Number of Threads')
            plt.ylabel('Execution Time (ms)')

        plt.show()


if __name__ == "__main__":
    if len(sys.argv) == 2:
        current_dir = sys.argv[1]
    else:
        current_dir = os.path.dirname(os.path.realpath(__file__))

    paths = sorted(Path(current_dir).iterdir(), key=os.path.getmtime)
    logs_dir = paths[-1].as_posix()
    log_files = [LogFile(full_path) for full_path in get_logs(logs_dir)]
    profile = Profiler(log_files)
    profile.plot()
