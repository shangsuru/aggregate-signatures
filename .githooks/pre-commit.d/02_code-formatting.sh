echo "[githook] Running clang-format for code formatting"

clang-format --dry-run --Werror ${CXX_CHANGED_FILES}
if [ $? -ne 0 ]; then 
  echo -n "Apply changes ... "
  clang-format -i -style=file src/*.cpp include/*.h tests/*.cpp
  echo "Done"
  exit 1
fi