import os
from pathlib import Path
import subprocess

base = Path(".") / "2021" / "eerie" / "data" / "secret"
for file in os.listdir(base):
    if file.endswith(".in"):
        my_result = float(subprocess.check_output(f"cat {base / file} | a.exe", shell=True).strip())
        with open(base / file.replace(".in", ".ans"), "w") as f:
            f.write(str(my_result) + "\n")
