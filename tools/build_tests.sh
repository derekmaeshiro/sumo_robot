#!/bin/bash
# This script is used by CI to build all test functions

SCRIPT_DIR=$(dirname "$0")
TEST_FUNCTIONS=$(ggrep -P '(?<=void )test_.+(?=\()' -o src/test/test.c)
for test_function in $TEST_FUNCTIONS
do
    make HW=LAUNCHPAD TEST=$test_function
    make HW=NSUMO TEST=$test_function
done