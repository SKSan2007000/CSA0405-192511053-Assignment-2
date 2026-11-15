# CSA0405-192511053-Assignment2 — Operating Systems (CO2)

Student: B. Santhosh Kumar | Register Number: 192511053
Faculty: Dr. Jayasakthi Velmurugan Kannaiyan
Required repository name: `CSA0405-192511053-Assignment2`

## Execution environment used for the attached reproducibility evidence
The included command outputs were produced in a Debian GNU/Linux 13 x86_64 container using GCC 14.2.0 and Linux kernel 6.18.57. This is stated to avoid presenting container measurements as measurements from the student's WSL2 installation. Re-run the programs in Ubuntu/WSL2 and replace environment-specific evidence if the course requires that exact machine.

## Build and run
All C files use `gcc -std=c11 -Wall -Wextra`; thread and semaphore programs additionally use `-pthread`. Each Task folder contains its own README, input, output, source and evidence. Run `./run_all.sh` from the repository root to compile and execute the reproducible tests.

## Task summary
- Task01: `process_demo.c`, `process_scale.c`, `observe_processes.sh`
- Task02: `scheduling.c`, `schedule_analysis.py`
- Task03: `thread_pool.c` (64 cameras; worker pools 1/4/8/16/64)
- Task04: `pipe_weather.c`, `shm_weather.c`, `ipc_benchmark.c` (1/10/100 MB; five trials, median)
- Task05: `bounded_buffer.c`, `lock_test.c`, `sync_benchmark.c`, `peterson.c`, `monitor_buffer.c`
- Task06: `banker.c`, `banker_bench.c` (7 trials, median)



## Important measurement note
Timings depend on CPU, kernel, compiler, power mode and background load. The report labels the actual environment and explains the measurement method. Do not present these timings as universal constants.
