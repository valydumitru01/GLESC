import os
import re

def check_for_pragma_once(file_content):
    if '#pragma once' not in file_content:
        return 'Error: #pragma once missing.'
    else:
        return ''


def check_access_specifier_order(file_content):
    access_specifiers = re.findall(r'\b(private|protected|public)\b', file_content)

    correct_order = ['private', 'protected', 'public']
    correct_order_optional_protected = ['private', 'public']

    # Handle case where there are no specifiers at all
    if not access_specifiers:
        return ''

    # Handle case where only a subset is present
    is_valid = all(a == b for a, b in zip(access_specifiers, correct_order[:len(access_specifiers)])) or \
               all(a == b for a, b in zip(access_specifiers, correct_order_optional_protected[:len(access_specifiers)]))

    if is_valid:
        return ''
    else:
        return 'Error: Incorrect access specifier order.'

def check_friend_declarations(file_content):
    # This pattern will find all classes.
    class_pattern = re.compile(
        r'class\s+\w+\s*{[\s\S]*?};', re.MULTILINE | re.DOTALL
    )

    # This pattern will find classes with friends defined in wrong positions.
    friend_pattern = re.compile(
        r'(private|protected|public)[\s\S]*friend[\s\S]*?};', re.MULTILINE | re.DOTALL
    )

    class_matches = class_pattern.findall(file_content)
    error_messages = []

    for class_declaration in class_matches:
        if friend_pattern.search(class_declaration):
            error_messages.append('Error: Friend declarations are not following the class definition in one or more classes.')

    return ' '.join(error_messages)

def check_file(filename):
    with open(filename, 'r', encoding='utf-8') as file:
        file_content = file.read()
        pragma_error = check_for_pragma_once(file_content)
        access_error = check_access_specifier_order(file_content)
        friend_error = check_friend_declarations(file_content)
    return pragma_error + access_error + friend_error


def print_file_structure(dirpath, prefix=''):
    items = os.listdir(dirpath)
    items.sort()

    for i, item in enumerate(items):
        path = os.path.join(dirpath, item)
        if os.path.isfile(path):
            if item.endswith('.h') or item.endswith('.hpp'):
                errors = check_file(path)
                print(prefix + ('└── ' if i == len(items) - 1 else '├── ') + item + (' - ' + errors if errors else ''))
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