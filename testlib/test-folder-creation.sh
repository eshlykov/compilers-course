#!/bin/bash

TEST_RESULTS=test-results

if [ -d "$TEST_RESULTS" ]; then
    rm -r $TEST_RESULTS
fi

mkdir $TEST_RESULTS

cd $TEST_RESULTS
mkdir svg
mkdir dot
