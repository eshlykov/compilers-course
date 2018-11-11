import os
import subprocess
import sys

assert(len(sys.argv) == 2)

compiler = sys.argv[1]


def draw_ast_for_directory(directory):

    ast_count = 0

    for file in os.listdir(directory):
        if file.endswith('.java'):

            print('Drawing {}'.format(file))

            test = os.path.abspath(os.path.join(directory, file))
            return_code = subprocess.call('./{} < {} {}'.format(compiler, test, 'ast_{}.dot'.format(ast_count) ), shell=True)

            if return_code != 0:
                print('Drawing failed!')
                print('')
                sys.exit(-1)

            ast_count += 1

draw_ast_for_directory('tests/samples-good/')

