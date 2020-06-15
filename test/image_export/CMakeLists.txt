add_executable ( test_image_export image_export.c)
target_link_libraries ( test_image_export cyan cyan_fileio )

# image_export_01 : lena ( square ) -> png

add_test (NAME image_export_01
    COMMAND test_image_export ${CYAN_DATASETS_DIR}/images/lena.cyan "PNG" ./output_01.png )

add_test( NAME image_export_01_bis 
    COMMAND ${CMAKE_COMMAND} -E compare_files ./output_01.png
    ${PROJECT_SOURCE_DIR}/test/image_export/reference_output/output_01.png )


# image_export_02 : lena ( square ) -> jpg

add_test (NAME image_export_02
    COMMAND test_image_export ${CYAN_DATASETS_DIR}/images/lena.cyan "JPG" ./output_02.jpg )

add_test( NAME image_export_02_bis 
    COMMAND ${CMAKE_COMMAND} -E compare_files ./output_02.jpg
    ${PROJECT_SOURCE_DIR}/test/image_export/reference_output/output_02.jpg )


# image_export_03 : lena ( square ) -> tiff 

add_test (NAME image_export_03
    COMMAND test_image_export ${CYAN_DATASETS_DIR}/images/lena.cyan "TIFF" ./output_03.tiff )

add_test( NAME image_export_03_bis 
    COMMAND ${CMAKE_COMMAND} -E compare_files ./output_03.tiff
    ${PROJECT_SOURCE_DIR}/test/image_export/reference_output/output_03.tiff )
