#!/bin/sh
set -eu
cc -std=c11 -Wall -Wextra process_demo.c -o process_demo
./process_demo > process_demo_run.txt &
pid=$!
sleep 0.2
printf '%s\n' '--- ps process tree ---'
ps -o pid,ppid,stat,comm --forest -p "$pid" --ppid "$pid"
child=$(pgrep -P "$pid" | head -n 1 || true)
if [ -n "$child" ]; then
  printf '%s\n' "--- /proc/$child/status (selected fields) ---"
  grep -E '^(Name|State|Pid|PPid|VmRSS|VmSize|Threads):' "/proc/$child/status"
fi
wait "$pid"
cat process_demo_run.txt
