echo "Running tests before pushing to remote repository"

cmake -S . -B build
cmake --build build

tests=$(find build/tests -type f -name '*-t')

for test in $tests; do
  echo "\n**************** ${test} ****************************************"
  $test
  if [ "$($test | grep 'SUCCESS!')" = "" ]; then
    exit 1
  fi
done
