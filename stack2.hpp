#include <cassert>  
#include "node2.h"  

namespace LABCALC
{
    template <class Item>
    stack<Item>::stack(const stack<Item>& source)
    {
    	LABCALC::node<Item> *tail_ptr; 

        list_copy(source.top_ptr, top_ptr, tail_ptr);
    }

    template <class Item>
    void stack<Item>::push(const Item& entry)
    // Library facilities used: node2.h
    {
        list_head_insert(top_ptr, entry);
    }

    template <class Item>
    void stack<Item>::pop( )
    // Library facilities used: cassert, node2.h
    {
        assert(!empty( ));
        list_head_remove(top_ptr);
    }

    template <class Item>
    void stack<Item>::operator =(const stack<Item>& source)
    // Library facilities used: node2.h
    {
    	LABCALC::node<Item> *tail_ptr; // Needed for argument of list_copy

        if (this == &source) // Handle self-assignment
            return;

        list_clear(top_ptr);
        list_copy(source.top_ptr, top_ptr, tail_ptr);
    }

    template <class Item>
    Item stack<Item>::top( ) const
    // Library facilities used: cassert
    {
        assert(!empty( ));
        return top_ptr->data( );
    }
}

