#ifndef MAIN_SAVITCH_STACK2_H
#define MAIN_SAVITCH_STACK2_H
#include <cstdlib>   
#include <cassert>
#include "node2.h"   

namespace LABCALC
{
    template <class Item>
    class stack
    {
    public:
        // TYPEDEFS
        typedef std::size_t size_type;
        typedef Item value_type;
        // CONSTRUCTORS and DESTRUCTOR
        stack( ) { top_ptr = NULL; }
        stack(const stack& source);
        ~stack( ) { list_clear(top_ptr); }
        // MODIFICATION MEMBER FUNCTIONS
        void push(const Item& entry);
        void pop( );
        void operator =(const stack& source);
        // CONSTANT MEMBER FUNCTIONS
        size_type size( ) const
	    { return LABCALC::list_length(top_ptr); }
        bool empty( ) const { return (top_ptr == NULL); }
        Item top( ) const;
    private:
        LABCALC::node<Item> *top_ptr;  // Points to top of stack
    };

}

#include "stack2.hpp" // Include the implementation
#endif
