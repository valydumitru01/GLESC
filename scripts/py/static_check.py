import os

def check_for_pragma_once(filename):
    with open(filename, 'r', encoding='utf-8') as file:
        if '#pragma once' in file.read():
            return 'Success'
        else:
            return 'Failure'

def print_file_structure(dirpath, prefix=''):
    items = os.listdir(dirpath)
    items.sort()

    for i, item in enumerate(items):
        path = os.path.join(dirpath, item)
        if os.path.isfile(path):
            if item.endswith('.h') or item.endswith('.hpp'):
                print(prefix + ('└── ' if i == len(items) - 1 else '├── ') + item + ' - ' + check_for_pragma_once(path))
            else:
                print(prefix + ('└── ' if i == len(items) - 1 else '├── ') + item)
        elif os.path.isdir(path):
            print(prefix + ('└── ' if i == len(items) - 1 else '├── ') + item + '/')
            print_file_structure(path, prefix + ('    ' if i == len(items) - 1 else '│   '))

def main():
    path = os.path.dirname(os.path.abspath(__file__))
    print("Absolute path: " + path)
    # Find the index of "TFG---OpenGL-Engine" in the path
    index = path.find("TFG---OpenGL-Engine")
    # Remove everything on the right of "TFG---OpenGL-Engine"
    root = path[:index + len("TFG---OpenGL-Engine")]
    print("Root: " + root)
    # Concatenate the root with the include folder
    include = os.path.join(root, "include")

    print_file_structure(include)


if __name__ == '__main__':
    main()