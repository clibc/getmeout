#ifndef H_CROSSREF
#define H_CROSSREF

#include <stdio.h>
#include "stack.h"
#include "stack_member.h"

static void cross_ref( Stack* token_stack ) {
    Stack s = create_stack( sizeof( StackMember ) );

    for ( unsigned int i = token_stack->item_count - 1; (int)i != -1; --i ) {
        StackMember* m = get_element_at( token_stack, i );

        if ( m->i_type == ST_IF ) {
            m->jump_address = i;
            push( &s, (void*)m );
        } else if ( m->i_type == ST_ELSE ) {
            StackMember* if_token = pop( &s );
            if ( if_token == NULL ) {
                // TODO: Handle error
                printf( "if is missing" );
                exit( -1 );
            }
            m->defined_address = if_token->jump_address;
            m->jump_address    = i;
            push( &s, (void*)m );
            //// doooooo
        } else if ( m->i_type == ST_END ) {
            StackMember* token = pop( &s );
            if ( token == NULL ) {
                // TODO: Handle error
                printf( "if/else is missing" );
                exit( -1 );
            }
            m->defined_address = token->jump_address;
        } else if ( m->i_type == ST_FOR ) {
            m->defined_address = i;
            push( &s, (void*)m );

        } else if ( m->i_type == ST_LOOP ) {
            StackMember* for_token = pop( &s );
            if ( for_token == NULL ) {
                // TODO: Handle error
                printf( "for is missing" );
                exit( -1 );
            }
            m->jump_address    = for_token->defined_address;
            m->defined_address = i;

            StackMember* old_for  = get_element_at( token_stack, for_token->defined_address );
            old_for->jump_address = m->defined_address;
        }
    }
}

#endif  // H_CROSSREF
