add_test_files(mouseEventTest_manual mouseEventTest.cpp mouseController.cpp clickButton.cpp)
add_test_moc_headers(mouseEventTest_manual mouseController.hpp)
add_test_link_libs(mouseEventTest_manual ${QT_LIBRARIES} ${X11_LIBRARIES} ${XTest_LIBRARIES})

add_manual_test_gui(mouseEventTest_manual)
