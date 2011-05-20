add_test_files(actionsTest_manual actionsTest.cpp actionsController.cpp actionForm.cpp)
add_test_moc_headers(actionsTest_manual actionsController.hpp actionForm.hpp)
add_test_link_libs(actionsTest_manual ${QT_LIBRARIES} ${X11_LIBRARIES} ${XTest_LIBRARIES})

add_manual_test_gui(actionsTest_manual)
