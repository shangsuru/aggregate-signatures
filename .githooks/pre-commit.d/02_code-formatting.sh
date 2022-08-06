echo "[githook] Running clang-format for code formatting"
echo -n "Apply changes ..."
clang-format -style=file -i src/*.cpp include/*.h tests/*.cpp
echo "Done"