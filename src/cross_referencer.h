#ifndef H_CROSSREF
#define H_CROSSREF

#include <stdio.h>
#include "stack.h"
#include "stack_member.h"
#include "file.h"

static void put_loop_vars_to_data_seg( int );
static void put_strings_into_data_seg( Stack* );
static char* scan_string_newlines( char*, int );

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
                // @TODO: Handle error
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
                // @TODO: Handle error
                printf( "if/else is missing" );
                exit( -1 );
            }
            m->defined_address = token->jump_address;
        } else if ( m->i_type == ST_FOR ) {
            m->defined_address = i;
            push( &s, (void*)m );
            m->loop_index_mem_ref = ++loopIndex;
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
            m->loop_index_mem_ref = loopIndex--;
        } else if ( m->i_type == VAR_FORINDEX ) {
            m->loop_index_mem_ref = loopIndex;
        } else if ( m->i_type == STRING ) {
            // TODO : Implement string concationation here
        }
    }
    put_loop_vars_to_data_seg( total_loop_count );
    put_strings_into_data_seg( token_stack );
}

/* static void put_strings_into_data_seg( Stack* stack ) { */
/*     unsigned int string_id = 0; */

/*     for ( int i = stack->item_count - 1; i > -1; --i ) { */
/*         StackMember* member = (StackMember*)stack->base + i; */

/*         if ( member->i_type == STRING ) { */
/*             fput( "str%i db %s\n", string_id, member->string_value ); */
/*             fput( "strLen%i equ $- str%i\n", string_id, string_id ); */
/*             member->string_id_value = string_id; */

/*             string_id += 1; */
/*         } */
/*     } */
/* } */

static void put_strings_into_data_seg( Stack* stack ) {
    unsigned int string_id = 0;

    for ( int i = stack->item_count - 1; i > -1; --i ) {
        StackMember* member = (StackMember*)stack->base + i;

        if ( member->i_type == STRING ) {
            char* new_string = scan_string_newlines( member->string_value, (int)strlen( member->string_value ) );
            if( new_string != NULL ) member->string_value = new_string;
            fput( "str%i db %s\n", string_id, member->string_value );
            fput( "strLen%i equ $- str%i\n", string_id, string_id );
            member->string_id_value = string_id;
            string_id += 1;
        }
    }
}

static char* scan_string_newlines( char* string, int size ) {
    int start_nl_count = 0;
    int middle_nl_count = 0;
    int end_nl_count = 0;
    
    for ( int i = 0; i < size; ++i ) {
        char letter = *( string + i );

        if ( letter == '\\' ) {  // backslash detected search for n
            char next_letter = *( string + i + 1 );
            if ( next_letter == 'n' ) {  // match
                if( i == 1 ) start_nl_count = 1;
                else if( i == size - 3 ) end_nl_count = 1;
                else middle_nl_count += 1;
            }
        }
    }

    int new_string_size = start_nl_count * 3 + middle_nl_count * 6 + end_nl_count * 3 + ( size - (start_nl_count + middle_nl_count + end_nl_count) * 2 );
    if( new_string_size == size ) { // we did not encounter any new lines
        return NULL;
    }

    int iter, start_pos, end_pos = 0;
    
    char* new_string = ( char* ) malloc( new_string_size + 1 );
    new_string[new_string_size] = 0;

    if( start_nl_count ){
        new_string[0] = '1';
        new_string[1] = '0';
        new_string[2] = ',';
        new_string[3] = '\"';

        start_pos = 4;
    }
    else {
        new_string[0] = '\"';
        start_pos = 1;
    }
    
    if( end_nl_count ){
        new_string[ new_string_size - 1 ] = '0';
        new_string[ new_string_size - 2 ]  = '1';
        new_string[ new_string_size - 3 ]  = ',';
        new_string[ new_string_size - 4 ]  = '\"';

        end_pos = new_string_size - 4;
    }
    else {
        new_string[new_string_size - 1] = '\"';
        end_pos = new_string_size - 1;
    }
    
    iter = 1 + start_nl_count * 2; // store index for old string & skip " , so it is 1
    for( int i = start_pos; i < end_pos; ++i ) {
        char letter = *( string + iter );

        if( letter == '\\' ) {
            char next_letter = *( string + iter + 1 );
            if( next_letter == 'n' ) {
                iter += 2;

                *( new_string + i ) = '\"';
                *( new_string + i + 1 ) = ',';
                *( new_string + i + 2 ) = '1';
                *( new_string + i + 3 ) = '0';
                *( new_string + i + 4 ) = ',';
                *( new_string + i + 5 ) = '\"';
                i += 5;
                continue;
            }
        }

        *( new_string + i ) = letter;
        iter += 1;
    }
    return new_string;
}

static void put_loop_vars_to_data_seg( int total_loop_count ) {
    fput( "segment .data\n" );

    for ( int i = 0; i < total_loop_count; ++i ) {
        fput( "LPPE%i dq 0\n", i );
        fput( "LPPI%i dq 0\n", i );
    }
}

#endif  // H_CROSSREF
