import os
import subprocess
import sys

assert(len(sys.argv) == 2)

compiler = sys.argv[1]


def run_tests(directory, is_good):
    failures_count = 0
    print('Run tests!')
    print()
    for file in os.listdir(directory):
        if file.endswith('.java'):
            test = os.path.abspath(os.path.join(directory, file))
            print('Test: {}'.format(file))
            return_code = subprocess.call('./{} < {}'.format(compiler, test), shell=True)
            if return_code != 0 and is_good or return_code == 0 and not is_good:
                print('State: failed')
                print('')
                failures_count += 1
                continue
            print('State: passed')
    return failures_count

false_negatives_count = run_tests('tests/samples-good/', True)
false_positives_count = run_tests('tests/samples-bad/', False)

print(false_negatives_count, 'good tests were failed')
print(false_positives_count, 'bad tests were failed')
