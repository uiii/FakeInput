#ifndef FI_ACTION_HPP
#define FI_ACTION_HPP

namespace FakeInput
{
    /** Abstract class representing arbitrary action which can be sent. */
    class Action
    {
    public:
        /** Creates new copy of this action.
         *
         * @returns
         *     New copy of this action allocated on heap.
         */
        virtual Action* clone() const = 0;

        /** Performs the action. */
        virtual void send() const = 0;
    };
}

#endif
