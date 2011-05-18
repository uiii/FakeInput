#ifndef FI_KEY_BASE_HPP
#define FI_KEY_BASE_HPP

#include "config.hpp"

#include <string>

namespace FakeInput
{
    /** Represents real keyboard button.
     */
    class Key_base
    {
    public:
        /** Gives the hardware code of the key.
         *
         * @returns
         *     Device dependend code of the key.
         */
        virtual unsigned int code() const;

        /** Gives the name of the key.
         *
         * @returns
         *     The name of the key.
         */
        virtual const std::string& name() const;

    protected:
        /** Key_base constructor.
         *
         * Creates key representing no real key.
         */
        Key_base();

        unsigned int code_;
        std::string name_;
    };
}

#endif
