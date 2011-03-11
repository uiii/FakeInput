add_test_files(commandTest_manual commandTest.cpp executer.cpp)
add_test_moc_headers(commandTest_manual executer.h)
add_test_link_libs(commandTest_manual ${QT_LIBRARIES})

add_manual_test_gui(commandTest_manual)
