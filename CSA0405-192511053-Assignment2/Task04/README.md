# Task 04 — Inter-Process Communication

`pipe_weather.c` demonstrates pipe EOF when the writer closes its write end. `shm_weather.c` uses a process-shared semaphore to publish six readings in shared memory. `ipc_benchmark.c` measures 1, 10 and 100 MB transfers using five trials and reports the median.

Run: compile each with GCC; link the shared-memory examples with `-pthread`.
