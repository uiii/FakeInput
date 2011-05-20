#ifndef FI_WAITACTION_HPP
#define FI_WAITACTION_HPP

#include "action.hpp"

namespace FakeInput
{
    /** Represents a wait action.
     *
     * Waits specified amount of time in miliseconds.
     */
    class Wait : public Action
    {
    public:
        /** Wait action constructor.
         *
         * @param milisec
         *     Amount of time to wait in miliseconds.
         */
        Wait(unsigned int milisec);

        /** Creates new copy of this action.
         *
         * @returns
         *     New copy of this action allocated on heap.
         */
        Action* clone() const;

        /** Performs this action. */
        void send() const;

    private:
        unsigned int milisec_;
    };
}

#endif
