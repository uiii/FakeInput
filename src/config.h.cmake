#ifndef WC_CONFIG_H
#define WC_CONFIG_H

#cmakedefine TEST_APP

#ifndef UNIX
    #cmakedefine UNIX
#endif

#ifndef WIN32
    #cmakedefine WIN32
#endif

#endif
