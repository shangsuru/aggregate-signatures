echo "[githook] Running clang-format for code formatting"

SOURCECODE="src/*.cpp include/*.h tests/*.cpp"
clang-format --dry-run --Werror ${SOURCECODE}
if [ $? -ne 0 ]; then 
  echo -n "Apply changes ... "
  clang-format -i -style=file ${SOURCECODE}
  echo "Done"
  exit 1
fi