import os

include_folder = '../Source/'
target_folders = ['Geometry', 'Rendering', 'Patterns', 'PrecompiledHeaders', 'Libraries']
substitute_folder = {
    'Geometry': '${GEOMETRY}',
    'Rendering': '${RENDERING}',
    'Patterns': '${PATTERNS}',
    'PrecompiledHeaders': '${PRECOMPILED_HEADERS}',
    'Libraries': '${LIBRARIES}'
}

if __name__ == '__main__':
    # Recursive search of .h files
    file_str = ""

    for root, dirs, files in os.walk(include_folder):
        # If included in any of target_folders
        if any([root.endswith(folder) for folder in target_folders]):
            for file in files:
                if file.endswith('.h'):
                    file_processed = os.path.join(root, file).split('Source/')[1].replace('\\', '/')
                    for folder in substitute_folder:
                        file_processed = file_processed.replace(folder, substitute_folder[folder])

                    file_str += '\t' + file_processed + '\n'
                    file_str += '\t' + file_processed.replace('.h', '.cpp') + '\n'

    print(file_str)


