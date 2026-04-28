import os
import re

DATA_DIR = "data"

# Ищем блоки вида:
# <pre><code>
# filename.txt
# <file>
#   ... code ...
# </file>
# </code></pre>
BLOCK_RE = re.compile(
    r"(<pre><code>\s*([\w\d_\-\.]+)\s*<file>(.*?)</file>\s*</code></pre>)",
    re.DOTALL
)

def process_index_txt(path):
    with open(path, "r", encoding="utf-8") as f:
        content = f.read()

    matches = BLOCK_RE.findall(content)
    if not matches:
        return

    index_dir = os.path.dirname(path)
    new_content = content

    for full_block, filename, code in matches:
        file_path = os.path.join(index_dir, filename)

        # Создаём файл, если его нет
        if not os.path.exists(file_path):
            with open(file_path, "w", encoding="utf-8") as f:
                f.write(code.strip() + "\n")
            print(f"[CREATE] {file_path}")
        else:
            print(f"[SKIP] {file_path} уже существует")

        # Формируем замену блока — только имя файла
        replacement = f"<pre><code>\n{filename}\n</code></pre>"

        # Удаляем <file>...</file> из index.txt
        new_content = new_content.replace(full_block, replacement)

    # Перезаписываем index.txt
    with open(path, "w", encoding="utf-8") as f:
        f.write(new_content)

    print(f"[UPDATE] {path}")


def walk_data():
    for root, dirs, files in os.walk(DATA_DIR):
        for name in files:
            if name == "index.txt":
                full_path = os.path.join(root, name)
                print(f"\n[SCAN] {full_path}")
                process_index_txt(full_path)


if __name__ == "__main__":
    walk_data()
