import os
import json
import argparse

def process_node(base_path, node):
    folder_path = os.path.join(base_path, node["fileName"])
    os.makedirs(folder_path, exist_ok=True)

    if node["isLeaf"]:
        index_txt_path = os.path.join(folder_path, "index.txt")
        if not os.path.exists(index_txt_path):
            with open(index_txt_path, "w", encoding="utf-8") as f:
                f.write(f"<h2>{node['name']}</h2>\n\n<p>Статья пока не заполнена.</p>\n")
        print(f"[OK] index.txt → {index_txt_path}")

    else:
        sub_index_path = os.path.join(folder_path, "index.json")
        if not os.path.exists(sub_index_path):
            with open(sub_index_path, "w", encoding="utf-8") as f:
                json.dump([], f, indent=2, ensure_ascii=False)
        print(f"[OK] index.json → {sub_index_path}")


def process_index(path):
    with open(path, "r", encoding="utf-8") as f:
        data = json.load(f)

    base_path = os.path.dirname(path)

    for node in data:
        process_node(base_path, node)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--path", default="index.json", help="Путь к index.json")
    args = parser.parse_args()

    index_path = args.path

    if not os.path.exists(index_path):
        print(f"Ошибка: index.json не найден по пути: {index_path}")
    else:
        process_index(index_path)
        print("Готово.")
