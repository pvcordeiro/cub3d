import os
import re
import shutil

HEADER_FILE = 'headers/error.h'
OUTPUT_DIR = 'src/errors/'

HEADER_42 = '''/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   {:50} :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 22:25:55 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/26 22:26:16 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

'''

shutil.rmtree(OUTPUT_DIR, ignore_errors=True)
os.makedirs(OUTPUT_DIR)

with open(HEADER_FILE, 'r') as f:
    lines = f.readlines()

error_definitions = []
for line in lines:
    match = re.match(r'#define (\w+)_MSG\s*"([^"]+)"', line)
    if match:
        error_name = match.group(1)
        error_message = match.group(2)
        error_definitions.append((error_name, error_message))

print(f'Found {len(error_definitions)} error definitions.')

with open(os.path.join(OUTPUT_DIR, 'errors.c'), 'w') as f:
    f.write(HEADER_42.format('errors.c'))
    f.write('#include <error.h>\n\n')
    f.write('char\t*get_error_message1(t_error _error);\n\n')
    f.write('char\t*get_error_message(t_error _error)\n')
    f.write('{\n')
    f.write('\treturn (get_error_message1(_error));\n')
    f.write('}\n')

for i, (error_name, error_message) in enumerate(error_definitions):
    function_number = i + 1
    next_function_number = function_number + 1
    file_path = os.path.join(OUTPUT_DIR, f"errors{function_number}.c")

    with open(file_path, 'w') as f:
        f.write(HEADER_42.format(f"errors{function_number}.c"))
        f.write('#include <error.h>\n\n')
        
        if function_number != len(error_definitions):
            f.write(f'char\t*get_error_message{next_function_number}(t_error _error);\n\n')
            f.write(f'char\t*get_error_message{function_number}(t_error _error)\n')
            f.write('{\n')
            f.write(f'\tif (_error == {error_name})\n')
            f.write(f'\t\treturn ({error_name}_MSG);\n')
            f.write(f'\treturn (get_error_message{next_function_number}(_error));\n')
            f.write('}\n')
        else:
            f.write(f'char\t*get_error_message{function_number}(t_error _error)\n')
            f.write('{\n')
            f.write(f'\t(void)_error;\n')
            f.write(f'\treturn ({error_name}_MSG);\n')
            f.write('}\n')
