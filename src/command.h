#ifndef FI_COMMAND_H
#define FI_COMMAND_H

#include "config.h"

#include <string>

namespace FakeInput
{
    /** Command-line commands executor.
     *
     * Allows you to run command-line commands.
     */
    class Command
    {
    public:
        /** Executes command-line command.
         *
         * @param cmd
         *     %Command to run.
         */
        static void run(const std::string& cmd);
    };
}

#endif
