#ifndef ASSERTION_H
#define ASSERTION_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
void assert_type( StackMember* m, int expected_type ) {
    if ( m->type != (TInfo)expected_type ) {
        printf( "Expected type " );
        switch ( expected_type ) {
            case INST:
                printf( "INST " );
                break;
            case LITERAL:
                printf( "LITERAL " );
                break;
            default:
                printf( "UNDEFINED " );
                break;
        }
        printf( "but got " );
        switch ( m->type ) {
            case INST:
                printf( "INST " );
                break;
            case LITERAL:
                printf( "LITERAL " );
                break;
            default:
                printf( "UNDEFINED " );
                break;
        }
        printf( "\n" );
        exit( -1 );
    }
}

void assert_itype( StackMember* m, int expected_type ) {
    if ( m->i_type != (TInfo)expected_type ) {
        printf( "Expected type " );
        switch ( expected_type ) {
            case INST:
                printf( "INST " );
                break;
            case LITERAL:
                printf( "LITERAL " );
                break;
            default:
                printf( "UNDEFINED " );
                break;
        }
        printf( "but got " );
        switch ( m->type ) {
            case INST:
                printf( "INST " );
                break;
            case LITERAL:
                printf( "LITERAL " );
                break;
            default:
                printf( "UNDEFINED " );
                break;
        }
        printf( "\n" );
        exit( -1 );
    }
}

#pragma GCC diagnostic pop

#endif  // ASSERTION_H
