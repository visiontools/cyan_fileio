add_executable ( image image.c)
target_link_libraries ( image cyan cyan_fileio )

add_test (NAME image COMMAND image)

