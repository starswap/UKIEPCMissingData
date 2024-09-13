import os
from pathlib import Path
import subprocess
import statistics

N = 30
file = "2021/eerie/data/secret/57.in"
my_result = float(subprocess.check_output(f"cat {file} | a.exe", shell=True).strip())
total_mc = 0 
print(f"\tOutput was {my_result}")

res = []
for i in range(N):
    print(i)
    mc = float(subprocess.check_output(f"cat {file} | mc.exe", shell=True).strip())
    res.append(mc)

print(f"avg {sum(res) / N}")
print(f"std {statistics.stdev(res)}")
