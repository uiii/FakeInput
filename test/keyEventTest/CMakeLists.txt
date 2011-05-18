add_test_files(keyEventTest_manual keyEventTest.cpp keyEventGrabber.cpp keyEventSender.cpp)
add_test_moc_headers(keyEventTest_manual keyEventGrabber.hpp keyEventSender.hpp)
add_test_link_libs(keyEventTest_manual ${QT_LIBRARIES} ${X11_LIBREARIES} ${XTest_LIBRARIES})

add_manual_test_gui(keyEventTest_manual)
