from pyrr import Matrix44, Vector3
import numpy as np
import os

os.system("cls")

transformMatrix = np.array([
    [1, 0, 0, 0],
    [0, 1, 0, 0],
    [0, 0, 1, 0],
    [0, 0, 0, 1]
])

targetPos = np.array([11,12, 13])
up = np.array([0, 1, 0])
resMatrix = np.zeros((4, 4))


# Using pyrr for comparison (OpenGL-compatible lookAt matrix)
lookAt_lib = Matrix44.look_at(eye=Vector3(transformMatrix[:3, 3]), target=Vector3(targetPos), up=Vector3(up))





# Print lookat matrix ready to copy-paste in c++ code as a std::array
# including "{ }" and ",", and "\n" at the end of each line
# It builds a string buffer and then prints it
lookAt_str = "{\n"
for i in range(4):
    lookAt_str += "    {"
    for j in range(4):
        # Format the number to a specific precision (e.g., 6 decimal places)
        lookAt_str += "{:.6f}".format(lookAt_lib[i, j])
        if j < 3:
            lookAt_str += ", "
    lookAt_str += "}"
    if i < 3:
        lookAt_str += ",\n"
    else:
        lookAt_str += "\n"
lookAt_str += "};\n"

print(lookAt_str)