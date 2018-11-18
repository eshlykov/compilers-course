import os
import subprocess


def type_check(directory='tests/type-check/', compiler='compiler'):
    passed, total = 0, 0

    for file in os.listdir(directory):
        if file.endswith('.java'):
            print('Testing: {}'.format(file))

            total += 1

            test = os.path.abspath(os.path.join(directory, file))
            return_code = subprocess.call('./{} {}'.format(compiler, test), shell=True)

            state = 'failed'

            if return_code != 0:
                passed += 1
                state = 'passed'

            print('State: {}\n'.format(state))

    return passed, total


if __name__ == '__main__':
    passed, total = type_check()
    print('{} out of {} test were passed'.format(passed, total))
