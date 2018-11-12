import os
import subprocess
import sys

assert(len(sys.argv) == 2)

compiler = sys.argv[1]

dot_file_names = []

# dot -T svg ast.dot -o ast.svg

def draw_svg():
    for file in os.listdir('.'):
        if file.endswith('.dot'):

            print('Generate .svg for {}'.format(file))
            return_code = subprocess.call('dot -T svg {} -o {}.svg'.format(file, file), shell=True)

            if return_code != 0:
                print('Generate failed!')
                print('')
                sys.exit(-1)

def draw_dot_for_directory(directory):

    ast_count = 0

    for file in os.listdir(directory):
        if file.endswith('.java'):

            print('Generate .dot for {}'.format(file))

            test = os.path.abspath(os.path.join(directory, file))
            return_code = subprocess.call('./{} {} < {}'.format(compiler,'ast-{}.dot'.format(file), test), shell=True)
            dot_file_names.append('ast-{}.dot'.format(file))

            if return_code != 0:
                print('Drawing failed!')
                print('')
                sys.exit(-1)

            ast_count += 1

draw_dot_for_directory('tests/samples-good/')
draw_svg()
