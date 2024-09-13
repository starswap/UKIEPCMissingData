import os
from pathlib import Path
import subprocess

START = 30
base = Path(".") / "2021" / "eerie" / "data" / "secret"
for file in os.listdir(base):
    if file.endswith(".in"):
        number = int(file.replace(".in", ""))
        if number < START:
            print(f"Skipping file {file}")
            continue
        
        print(f"For file: {file}")
        
        N = 5
        total_err = 0
        my_result = float(subprocess.check_output(f"cat {base / file} | a.exe", shell=True).strip())
        print(f"\tOutput was {my_result}")
        above = 0
        below = 0
        for i in range(N):
            mc = float(subprocess.check_output(f"cat {base / file} | mc.exe", shell=True).strip())
            rel_error = abs(mc - my_result) / my_result if my_result != 0 else 0
            total_err += rel_error
            if mc > my_result:
                above += 1
            elif mc < my_result:
                below += 1
            print(f"\tMC: {mc}, abs_error: {abs(mc - my_result)}, rel_error: {rel_error}")

        avg_err = total_err / N
        print(f"AVG: {avg_err}")
        if avg_err >= 0.0005:
            raise Exception("Too much relative error to be reasonable")
        if (above == 5 or below == 5) and avg_err >= 0.0001:
            raise Exception("In all trials the mc was on the same side as the 'correct' answer")