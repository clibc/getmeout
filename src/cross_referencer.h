#ifndef H_CROSSREF
#define H_CROSSREF

#include <stdio.h>
#include "stack.h"
#include "stack_member.h"
#include "file.h"

static void put_loop_vars_to_data_seg( int );
static void put_strings_into_data_seg( Stack* );
static int scan_string_newlines( char*, int );

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
            int newlines = scan_string_newlines( member->string_value, (int)strlen( member->string_value ) );
            char* string = member->string_value;

            if ( newlines == 0 ) {
                fput( "str%i db %s\n", string_id, string );
            } else {
                fput( "str%i db ", string_id );
                char* string      = member->string_value;
                int string_lenght = strlen( string );
                fput( "%s\",10,", string );
                string += string_lenght + 2;  // one for n ( in "\n" )

                for ( int j = 0; j < newlines; ++j ) {
                    int string_lenght = strlen( string );
                    if ( j == 0 ) {
                        fput( "\"%s", string );
                    } else
                        fput( ",10,%s", string );
                    string += string_lenght + 2;  // + 2 for \n
                }
                fput( "\n" );
            }
            fput( "strLen%i equ $- str%i\n", string_id, string_id );
            member->string_id_value = string_id;
            string_id += 1;
        }
    }
}

static int scan_string_newlines( char* string, int size ) {
    int counted_newlines = 0;
    for ( int i = 0; i < size; ++i ) {
        char letter = *( string + i );

        if ( letter == '\\' ) {  // backslash detected search for n
            char next_letter = *( string + i + 1 );
            if ( next_letter == 'n' ) {  // match
                *( string + i )     = 0;
                *( string + i + 1 ) = 0;
                counted_newlines += 1;
            } else {
                i += 1;
            }
        }
    }

    return counted_newlines;
}

static void put_loop_vars_to_data_seg( int total_loop_count ) {
    fput( "segment .data\n" );

    for ( int i = 0; i < total_loop_count; ++i ) {
        fput( "LPPE%i dq 0\n", i );
        fput( "LPPI%i dq 0\n", i );
    }
}

#endif  // H_CROSSREF
