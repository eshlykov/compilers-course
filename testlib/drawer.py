import os
import subprocess
import sys

assert(len(sys.argv) == 2)

compiler = sys.argv[1]

dot_file_names = []

def draw_svg(directory):
    for file in os.listdir(directory):
        if file.endswith('.dot'):

            print('Generate .svg for {}'.format(file))
            return_code = subprocess.call('dot -T svg {}{} -o test_results/svg/{}.svg'.format(directory, file, file), shell=True)

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
            return_code = subprocess.call('./{} {} {}'.format(compiler, test, 'test_results/dot/' + 'ast-{}.dot'.format(file)), shell=True)
            dot_file_names.append('ast-{}.dot'.format(file))

            if return_code != 0:
                print('Drawing failed!')
                print('')
                sys.exit(-1)

            ast_count += 1

draw_dot_for_directory('testlib/good-samples/')
draw_svg('test_results/dot/')
