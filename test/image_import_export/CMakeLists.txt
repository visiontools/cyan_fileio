add_executable ( test_image_import_export image_import_export.c)
target_link_libraries ( test_image_import_export cyan cyan_fileio )

add_test (NAME image_import_export_01
    COMMAND test_image_import_export ${CYAN_DATASETS_DIR}/images/lena.png PNG ./output_01.png )

add_test( NAME image_import_export_01_bis 
    COMMAND ${CMAKE_COMMAND} -E compare_files ./output_01.png
    ${PROJECT_SOURCE_DIR}/test/image_import_export/reference_output/output_01.png )
