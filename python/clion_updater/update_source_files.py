import os

vs_folder = '../../vs/Source/'
target_folders = ['Geometry', 'Rendering', 'Patterns', 'PrecompiledHeaders', 'Libraries']
assets_folder = 'Assets/'

clion_folder = '../../clion/'
debug_folder = 'cmake-build-debug-visual-studio-x64/Debug/'
release_folder = 'cmake-build-release-visual-studio-x64/Release/'


# Copy folders from vs to clion
for folder in target_folders:
    os.system('cp -r ' + vs_folder + folder + ' ' + clion_folder)

# Copy assets folder to clion debug and release
os.system('cp -r ' + vs_folder + assets_folder + ' ' + clion_folder + debug_folder)
os.system('cp -r ' + vs_folder + assets_folder + ' ' + clion_folder + release_folder)
