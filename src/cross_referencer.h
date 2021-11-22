#ifndef H_CROSSREF
#define H_CROSSREF

#include <stdio.h>
#include "stack.h"

static void cross_ref( Stack* token_stack ) {
    int count = 0;
    int depth = 0;

    for ( int i = token_stack->item_count - 1; i >= 0; --i ) {
        count += 1;

        StackMember* m = get_element_at( token_stack, i );
        if ( m->type == ST_IF ) {
            depth += 1;

        } else if ( m->type == ST_ELSE ) {
            //// doooooo
        } else if ( m->type == ST_END ) {
            depth -= 1;
        }
    }
}

#endif  // H_CROSSREF
