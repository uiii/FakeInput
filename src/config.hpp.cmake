#ifndef WC_CONFIG_HPP
#define WC_CONFIG_HPP

#cmakedefine TEST_APP

#ifndef UNIX
    #cmakedefine UNIX
#endif

#ifndef WIN32
    #cmakedefine WIN32
#endif

#endif
