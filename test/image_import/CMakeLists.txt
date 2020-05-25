add_executable ( test_image_import image_import.c)
target_link_libraries ( test_image_import cyan cyan_fileio )

# image_import_01 : lena.png ( square ) 

add_test (NAME image_import_01
    COMMAND test_image_import ${CYAN_DATASETS_DIR}/images/lena.png ./output_01.cyan )

add_test( NAME image_import_01_bis 
    COMMAND ${CMAKE_COMMAND} -E compare_files ./output_01.cyan
    ${PROJECT_SOURCE_DIR}/test/image_import/reference_output/output_01.cyan )


# image_import_02 : lena.jpg ( square ) 

add_test (NAME image_import_02
    COMMAND test_image_import ${CYAN_DATASETS_DIR}/images/lena.jpg ./output_02.cyan )

add_test( NAME image_import_02_bis 
    COMMAND ${CMAKE_COMMAND} -E compare_files ./output_02.cyan
    ${PROJECT_SOURCE_DIR}/test/image_import/reference_output/output_02.cyan )


# image_import_03 : lena.tiff ( square ) 

add_test (NAME image_import_03
    COMMAND test_image_import ${CYAN_DATASETS_DIR}/images/lena.tiff ./output_03.cyan )

add_test( NAME image_import_03_bis 
    COMMAND ${CMAKE_COMMAND} -E compare_files ./output_03.cyan
    ${PROJECT_SOURCE_DIR}/test/image_import/reference_output/output_03.cyan )
