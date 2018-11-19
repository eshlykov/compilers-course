import os
import subprocess
import sys

assert(len(sys.argv) == 2)

compiler = sys.argv[1]


def run_tests(directory, is_good):

    print('Run {} tests!'.format('good' if is_good else 'bad '))
    print()

    failures_count = 0
    total_count = 0

    for file in sorted(os.listdir(directory)):
        if file.endswith('.java'):
            total_count += 1

            print('Test: {}'.format(file))

            test = os.path.abspath(os.path.join(directory, file))
            return_code = subprocess.call('./{} {}'.format(compiler, test), shell=True)
            if return_code != 0 and is_good or return_code == 0 and not is_good:

                print('State: failed')
                print('')

                failures_count += 1
                continue

            print('State: passed')
            print('')

    return failures_count, total_count

false_negatives_count, total_good_tests_count = run_tests('testlib/good-samples/', True)
false_positives_count, total_bad_tests_count = run_tests('testlib/bad-samples/', False)

print('{} out of {} good tests were failed'.format(false_negatives_count, total_good_tests_count))
print('{} out of {} bad tests were failed'.format(false_positives_count, total_bad_tests_count))
