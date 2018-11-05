import os
import subprocess
import sys

assert(len(sys.argv) == 2)

compiler = sys.argv[1]


def run_tests(directory, is_good):
    failures_count = 0
    for file in os.listdir(directory):
        if file.endswith('.java'):
            test = os.path.abspath(os.path.join(directory, file))
            return_code = subprocess.call('./{} < {}'.format(compiler, test), shell=True)
            if return_code != 0 and is_good or return_code == 0 and not is_good:
                print('Test {} is failed'.format(file))
                failures_count += 1
    return failures_count

false_negatives_count = run_tests('tests/samples-good/', True)
false_positives_count = run_tests('tests/samples-bad/', False)

print(false_negatives_count, 'good tests were failed')
print(false_positives_count, 'bad tests were failed')
