import sys


def parse_line(line):
    """Parse each line to find the depth, extract the node, and store the title."""
    parts = line.strip().split('\t')
    node_id = parts[0]
    node_label = parts[1] if len(parts) > 1 else ""
    depth = node_id.count('.')  # Counting dots to determine the depth
    return depth, node_id, node_label


def build_relationships(file_path):
    """Build a dictionary of parent-child relationships based on file content and map node IDs to titles."""
    tree = {}
    last_node_at_depth = {}
    id_to_title = {}

    with open(file_path, 'r', encoding='utf-8') as file:
        for line in file:
            if line.strip():  # Ignore empty lines
                depth, node_id, node_label = parse_line(line)
                id_to_title[node_id] = node_label
                last_node_at_depth[depth] = node_id

                if depth > 0:
                    parent_id = last_node_at_depth.get(depth - 1)
                    if parent_id:
                        if parent_id not in tree:
                            tree[parent_id] = []
                        tree[parent_id].append(node_id)
                    else:
                        print(f"Error: No parent node defined for node {node_label} ({node_id}) at depth {depth}")
                        sys.exit(1)
                else:
                    tree[node_id] = []  # Initializing list for root level nodes

    return tree, id_to_title





def write_drawio_edges(tree, id_to_title, output_path):
    """Writes each parent-child relationship to a file in draw.io import format, ensuring all node titles are unique."""
    # Tracks each node title and the number of times it has been used
    node_count = {}
    with open(output_path, 'w', encoding='utf-8') as file:
        for parent, children in tree.items():
            parent_title = id_to_title.get(parent, "Unnamed Node")
            for child in children:
                child_title = id_to_title.get(child, "Unnamed Node")
                original_child_title = child_title

                # If the child title has been used, modify it by appending the parent title enough times to ensure uniqueness
                while True:
                    # Generate the key to check against existing titles
                    node_key = f"{parent_title} - {child_title}" if child_title in node_count else child_title
                    if node_key not in node_count:
                        node_count[node_key] = 0
                        child_title = node_key  # Set the child title to the unique key
                        break
                    else:
                        # Append the parent title to make the title unique
                        child_title = f"{parent_title} - {original_child_title}"

                # Write the relationship to the file
                file.write(f'{parent_title}->{child_title}\n')
                node_count[child_title] = node_count.get(child_title, 0) + 1






def main():
    if len(sys.argv) != 3:
        print("Usage: python <script.py> input_file.txt output_file.txt")
        return

    input_file_path = sys.argv[1]
    output_file_path = sys.argv[2]
    tree, id_to_title = build_relationships(input_file_path)
    write_drawio_edges(tree, id_to_title, output_file_path)
    print(f"Output successfully written to {output_file_path}")


if __name__ == "__main__":
    main()
