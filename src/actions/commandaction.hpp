#ifndef FI_COMMANDACTION_HPP
#define FI_COMMANDACTION_HPP

#include <string>

#include "action.hpp"

namespace FakeInput
{
    /** Represents a command run action.
     *
     * Runs a specified command-line command.
     */
    class CommandRun : public Action
    {
    public:
        /** CommandRun action constructor.
         *
         * @param cmd
         *     Command to run.
         */
        CommandRun(const std::string& cmd);

        /** Creates new copy of this action.
         *
         * @returns
         *     New copy of this action allocated on heap.
         */
        Action* clone() const;

        /** Performs this action. */
        void send() const;

    private:
        /** Command to run. */
        std::string cmd_;
    };
}

#endif
