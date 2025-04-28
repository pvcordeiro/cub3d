import os
import sys

def check_dir(dir):
    try:
        ls = os.listdir(dir)
    except:
        return False
    for item in ls:
        item_path = f"{dir}/{item}"
        if not check_dir(item_path):
            check_file(item_path)
    return True

def check_file(file):
    if file[-2:] == ".c":
        check_c_file(file)

def check_c_file(file):
    with open(file, 'r') as f:
        lines = f.readlines()
    last_function_name = None
    for index, line in enumerate(lines):
        if not line.startswith("\t") and "\t" in line and "(" in line:
            last_function_name = line[line.find("\t") + 1:line.find("(")]
            continue
        if "_e(" in line:
            next_line = None
            for index2, line2 in enumerate(lines[index:]):
                if line2.endswith(";\n"):
                    next_line = lines[index + index2 + 1]
                    break
            if not next_line or ("ft_has_error()" not in next_line and "ft_error_assert()" not in next_line and "}" not in next_line):
                print(f"{file}:{index + 1}: Function that throws errors called without any check after")
            continue
        if "ft_error(" not in line:
            continue
        if not last_function_name.endswith("_e"):
            print(f"{file}:{index + 1}: Missing ft_error (_e) symbol in throwing function's name")

dir = None
match (len(sys.argv)):
    case 1:
        dir = "."
    case 2:
        dir = sys.argv[1]

if not dir:
    raise "Invalid Args"

check_dir(dir)