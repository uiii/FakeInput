#ifndef WC_COMMAND_H
#define WC_COMMAND_H

#include "config.h"

#include <string>

namespace wc
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
