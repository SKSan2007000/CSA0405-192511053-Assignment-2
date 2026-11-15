#!/bin/sh
set -eu
for t in Task01 Task02 Task03 Task04 Task05 Task06; do
  echo "===== $t ====="
  case "$t" in
    Task01) (cd "$t"; gcc -std=c11 -Wall -Wextra process_demo.c -o process_demo; gcc -std=c11 -Wall -Wextra process_scale.c -o process_scale; ./process_demo; ./process_scale 2000);;
    Task02) (cd "$t"; gcc -std=c11 -Wall -Wextra scheduling.c -o scheduling; ./scheduling; python3 schedule_analysis.py);;
    Task03) (cd "$t"; gcc -std=c11 -Wall -Wextra -pthread thread_pool.c -o thread_pool; ./thread_pool);;
    Task04) (cd "$t"; gcc -std=c11 -Wall -Wextra pipe_weather.c -o pipe_weather; gcc -std=c11 -Wall -Wextra shm_weather.c -o shm_weather -pthread; gcc -std=c11 -Wall -Wextra ipc_benchmark.c -o ipc_benchmark -pthread; ./pipe_weather; ./shm_weather; ./ipc_benchmark);;
    Task05) (cd "$t"; for f in bounded_buffer lock_test sync_benchmark peterson monitor_buffer; do gcc -std=c11 -Wall -Wextra -pthread "$f.c" -o "$f"; done; ./bounded_buffer 1 1; ./bounded_buffer 4 4; ./lock_test; ./sync_benchmark; ./peterson; ./monitor_buffer);;
    Task06) (cd "$t"; gcc -std=c11 -Wall -Wextra banker.c -o banker; gcc -std=c11 -Wall -Wextra banker_bench.c -o banker_bench; ./banker; ./banker_bench);;
  esac
done
