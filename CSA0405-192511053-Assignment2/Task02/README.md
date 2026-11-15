# Task 02 — CPU Scheduling

`scheduling.c` implements Round Robin at quantum 1, 3, 5 and 20 and reports Gantt slices, CT, TAT, WT, RT and dispatch transitions. `schedule_analysis.py` calculates FCFS, SJF, SRTF and non-preemptive priority for the same workload.

Run: `gcc -std=c11 -Wall -Wextra scheduling.c -o scheduling && ./scheduling`; `python3 schedule_analysis.py`. Lower priority number is higher priority.
