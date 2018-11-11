import os
import subprocess
import sys

assert(len(sys.argv) == 2)

compiler = sys.argv[1]


def run_tests(directory, is_good):

    print('Run {} tests!'.format('good' if is_good else 'bad '))
    print()

    failures_count = 0

    for file in os.listdir(directory):
        if file.endswith('.java'):

            print('Test: {}'.format(file))

            test = os.path.abspath(os.path.join(directory, file))
            return_code = subprocess.call('./{} < {}'.format(compiler, test), shell=True)
            if return_code != 0 and is_good or return_code == 0 and not is_good:

                print('State: failed')
                print('')

                failures_count += 1
                continue

            print('State: passed')
            print('')

    return failures_count

false_negatives_count = run_tests('tests/samples-good/', True)
false_positives_count = run_tests('tests/samples-bad/', False)

print(false_negatives_count, 'good tests were failed')
print(false_positives_count, 'bad tests were failed')
