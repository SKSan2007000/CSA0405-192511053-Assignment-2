# Task 06 — Deadlock and Banker’s Algorithm

`banker.c` implements safety and resource-request algorithms for the supplied state. `banker_bench.c` measures a reverse dependency chain at n=10, 100 and 1,000 processes, m=3 resource types, using seven trials and the median. `evidence/resource_allocation_graph.png` shows a resource cycle.

Run: `gcc -std=c11 -Wall -Wextra banker.c -o banker && ./banker`; compile and run banker_bench.c similarly.
