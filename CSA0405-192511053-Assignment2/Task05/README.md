# Task 05 — Synchronisation

`bounded_buffer.c` supports 1x1 and 4x4 producer/consumer tests with unique item IDs and exact-once checking. `lock_test.c` compares global, per-train and per-coach mutexes. `sync_benchmark.c` compares mutex, C11 atomic increment and spin lock at 1, 4 and 16 threads, including per-thread CPU time. `peterson.c` uses sequentially-consistent C11 atomics for Peterson mutual exclusion. `monitor_buffer.c` shows a monitor-style condition-variable buffer.

Run with `-pthread`. The 100-run record is in evidence/100_runs.txt.
