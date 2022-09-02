cxx_test(
   TARGET euclidean_vector_test1
   FILENAME "euclidean_vector_test1.cpp"
   LINK euclidean_vector
)

cxx_test(
   TARGET constructor_test
   FILENAME "constructor_test.cpp"
   LINK euclidean_vector
)

cxx_test(
   TARGET operators_and_exception_test
   FILENAME "operators_and_exception_test.cpp"
   LINK euclidean_vector
)

cxx_test(
   TARGET member_and_exception_test
   FILENAME "member_and_exception_test.cpp"
   LINK euclidean_vector
)

cxx_test(
   TARGET norm_test
   FILENAME "norm_test.cpp"
   LINK euclidean_vector
)

cxx_test(
   TARGET cache_test
   FILENAME "cache_test.cpp"
   LINK euclidean_vector
)

cxx_test(
   TARGET utility_and_exception_test
   FILENAME "utility_and_exception_test.cpp"
   LINK euclidean_vector
)
