add_executable ( test_image_import image_import.c)
target_link_libraries ( test_image_import cyan cyan_fileio )

# image_import_01 : lena.png ( square ) 

add_test (NAME image_import_01
    COMMAND test_image_import ${CYAN_DATASETS_DIR}/images/lena.png ./output_01.cyan )

add_test( NAME image_import_01_bis 
    COMMAND ${CMAKE_COMMAND} -E compare_files ./output_01.cyan
    ${PROJECT_SOURCE_DIR}/test/image_import/reference_output/output_01.cyan )
