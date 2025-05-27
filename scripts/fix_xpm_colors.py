import os
import re
from PIL import ImageColor

def grayN_to_hex(gray_name):
    m = re.match(r'gray(\d+)', gray_name.lower())
    if m:
        n = int(m.group(1))
        if 0 <= n <= 100:
            val = round(255 * n / 100)
            return '{:02X}{:02X}{:02X}'.format(val, val, val)
    return None

def force_hex_color(color_value):
    original = color_value.strip()

    if original.lower() == 'none':
        return '#00000000'

    hex_match = re.match(r'^#([0-9a-fA-F]+)$', original)
    if hex_match:
        hex_val = hex_match.group(1).upper()

        if len(hex_val) == 3:
            r, g, b = hex_val
            rgb = r * 2 + g * 2 + b * 2
            return f'#FF{rgb}'

        elif len(hex_val) == 4:
            r, g, b, a = hex_val
            rgb = r * 2 + g * 2 + b * 2
            aa = a * 2
            return f'#{aa}{rgb}'

        elif len(hex_val) == 6:
            return f'#FF{hex_val}'

        elif len(hex_val) == 8:
            rrggbb = hex_val[:6]
            aa = hex_val[6:]
            return f'#{aa}{rrggbb}'

        elif len(hex_val) == 10:
            return f'#{hex_val}'

    hex_gray = grayN_to_hex(original)
    if hex_gray:
        return f'#FF{hex_gray}'

    try:
        r, g, b = ImageColor.getrgb(original)
        return '#FF{:02X}{:02X}{:02X}'.format(r, g, b)
    except Exception:
        return original

def clean_xpm_colors(xpm_path):
    with open(xpm_path, 'r') as f:
        lines = f.readlines()

    new_lines = []
    for line in lines:
        if ' c ' in line:
            try:
                before_c, after_c = line.split(' c ', 1)
                match = re.match(r'([^",]+)', after_c.strip())
                if match:
                    cor_original = match.group(1)
                    cor_hex = force_hex_color(cor_original)
                    rest = after_c[len(cor_original):]
                    line_corrigida = f'{before_c} c {cor_hex}{rest}'
                    new_lines.append(line_corrigida)
                else:
                    new_lines.append(line)
            except Exception as e:
                print(f"[erro] {xpm_path}: {e}")
                new_lines.append(line)
        else:
            new_lines.append(line)

    with open(xpm_path, 'w') as f:
        f.writelines(new_lines)

    print(f'✔ Corrigido: {xpm_path}')

def processar_xpms_recursivamente():
    for root, _, files in os.walk('.'):
        for file in files:
            if file.endswith('.xpm'):
                caminho_completo = os.path.join(root, file)
                try:
                    print(f'🧼 A limpar {caminho_completo}...')
                    clean_xpm_colors(caminho_completo)
                except Exception as e:
                    print(f'✘ Erro em {caminho_completo}: {e}')

if __name__ == "__main__":
    processar_xpms_recursivamente()
