# import pygetwindow as gw

# for window in gw.getAllWindows():
#     print(window)
#     if window.title == "framework":
#         window.activate()
#     elif window.title == "Windows PowerShell":
#         window.minimize()

import os
import shutil

def move_files_with_prefix(source_folder, destination_folder, prefix):
    # Ensure the destination folder exists
    if not os.path.exists(destination_folder):
        os.makedirs(destination_folder)

    # List all files in the source folder
    files = os.listdir(source_folder)

    # Iterate through the files and move those with content starting with the specified prefix
    for file in files:
        source_path = os.path.join(source_folder, file)
        destination_path = os.path.join(destination_folder, file)

        with open(source_path, 'r') as f:
            first_line = f.readline().strip()

        if first_line.startswith(prefix):
            shutil.move(source_path, destination_path)
            print(f"Moved {file} to {destination_folder}")

# Replace these paths with your actual source and destination folder paths
source_folder_path = "./data/sdl_1112_480hz_55"
destination_folder_path = "./data/sdl_1112_480hz_55_error"
prefix_to_match = "-"

move_files_with_prefix(source_folder_path, destination_folder_path, prefix_to_match)
