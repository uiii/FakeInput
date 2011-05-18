#ifndef FI_COMMAND_HPP
#define FI_COMMAND_HPP

#include "config.hpp"

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
