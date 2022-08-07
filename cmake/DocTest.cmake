if(ENABLE_DOCTESTS)
  add_definitions(-DENABLE_DOCTEST_IN_LIBRARY)
  FetchContent_Declare(
    DocTest
    GIT_REPOSITORY "https://github.com/doctest/doctest"
    GIT_TAG "v2.4.9"
  )
  FetchContent_MakeAvailable(DocTest)
  FetchContent_GetProperties(DocTest SOURCE_DIR DOCTEST_SOURCE_DIR)
  set(DOCTEST_INCLUDE_DIR ${DOCTEST_SOURCE_DIR}/doctest)
  add_subdirectory(tests)
endif()