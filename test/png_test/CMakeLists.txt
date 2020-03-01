add_executable( png_test png_test.c )
target_link_libraries( png_test cyan_fileio )

add_test( NAME png_test COMMAND png_test )
