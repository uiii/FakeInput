#ifndef FI_SYSTEM_HPP
#define FI_SYSTEM_HPP

#include "config.hpp"

#include <string>

namespace FakeInput
{
    /** Handler of some system operations.
     *
     * Allows you to run command-line commands
     * and wait for specified time
     */
    class System
    {
    public:
        /** Executes command-line command.
         *
         * @param cmd
         *     %Command to run.
         */
        static void run(const std::string& cmd);

        /** Sleeps the current thread and wait for specified time.
         *
         * @param milisec
         *     time to wait in miliseconds
         */
        static void wait(unsigned int milisec);
    };
}

#endif
