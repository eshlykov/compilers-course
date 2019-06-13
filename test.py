import os
import shutil

INPUT_DIRECTORIES = [
    '../input/good',
    '../input/bad'
]

OUTPUT_DIRECTORIES = [
    '../output/good',
    '../output/bad'
]


def test():
    create()

    for input_directory, output_directory in zip(INPUT_DIRECTORIES, OUTPUT_DIRECTORIES):
        for filename in os.listdir(input_directory):
            file = os.path.join(input_directory, filename)

            print('\033[1;34mFile:\033[0;39m {}'.format(file))

            directory = os.path.splitext(os.path.join(output_directory, filename))[0]

            if not os.path.exists(directory):
                os.makedirs(directory)

            os.system('bin/compiler {} {}'.format(file, directory))

            generate_images(directory)


def generate_images(directory):
    for filename in os.listdir(directory):
        file = os.path.join(directory, filename)

        if os.path.isfile(file) and os.path.splitext(file)[1] == '.gv':
            picture = os.path.splitext(file)[0] + '.svg'
            os.system('dot -T svg {} -o {}'.format(file, picture))
        elif os.path.isdir(file):
            generate_images(file)
        else:
            continue


def create():
    for directory in OUTPUT_DIRECTORIES:
        try:
            os.makedirs(directory)
        except FileExistsError:
            pass


def clean():
    for directory in OUTPUT_DIRECTORIES:
        try:
            shutil.rmtree(directory)
        except FileNotFoundError:
            pass


if __name__ == '__main__':
    clean()
    test()
