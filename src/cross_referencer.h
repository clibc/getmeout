#ifndef H_CROSSREF
#define H_CROSSREF

#include <stdio.h>
#include "stack.h"
#include "stack_member.h"
#include "file.h"

static void put_loop_vars_to_data_seg( int );

static void cross_ref( Stack* token_stack ) {
    Stack s       = create_stack( sizeof( StackMember ) );
    int loopIndex = -1;

    int total_loop_count = 0;

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
            m->loopIndexMemRef = ++loopIndex;
            total_loop_count += 1;
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
            m->loopIndexMemRef    = loopIndex--;
        } else if ( m->i_type == VAR_FORINDEX ) {
            m->loopIndexMemRef = loopIndex;
        }
    }
    put_loop_vars_to_data_seg( total_loop_count );
}

static void put_loop_vars_to_data_seg( int total_loop_count ) {
    fput( "segment .data\n" );

    for ( int i = 0; i < total_loop_count; ++i ) {
        fput( "LPPE%i dq 0\n", i );
        fput( "LPPI%i dq 0\n", i );
    }
}

#endif  // H_CROSSREF
