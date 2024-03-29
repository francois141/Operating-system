#include "screen.h"
#include "../system_lib/graphics/color.h"


#define TABLE_OFFSET 32

u8 characters[96][6][6] =
{
    // Space
    {
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0}
    },
    // !
    {
        {0,0,0,0,0,0},
        {0,0,0,0,1,0},
        {0,0,0,0,1,0},
        {0,0,0,0,1,0},
        {0,0,0,0,0,0},
        {0,0,0,0,1,0}
    }, 
    // "
    {
        {0,0,0,0,0,0},
        {0,1,0,0,1,0},
        {0,1,0,0,1,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0}
    },
    // #
    {
        {0,1,0,0,1,0},
        {1,1,1,1,1,1},
        {0,1,0,0,1,0},
        {0,1,0,0,1,0},
        {1,1,1,1,1,1},
        {0,1,0,0,1,0}
    },
    // $
    {
        {0,0,1,0,0,0},
        {0,1,1,1,1,0},
        {1,0,1,0,0,0},
        {0,1,1,1,0,0},
        {0,0,1,0,1,0},
        {1,1,1,1,0,0}
    },
    // %
    {
        {1,1,0,0,0,1},
        {1,1,0,0,1,0},
        {0,0,0,1,0,0},
        {0,0,1,0,0,0},
        {0,1,0,0,1,1},
        {1,0,0,0,1,1}
    },
    // &
    {
        {0,1,1,0,0,0},
        {1,0,0,1,0,0},
        {0,1,1,0,0,0},
        {1,0,0,1,0,1},
        {1,0,0,0,1,0},
        {0,1,1,1,0,1}
    },
    //  '
    {
        {0,0,0,0,0,0},
        {0,0,0,1,0,0},
        {0,0,0,1,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0}
    },
    // (
    {
        {0,0,0,1,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,0,1,0,0}
    },
    // ) 
    {
        {0,0,1,0,0,0},
        {0,0,0,1,0,0},
        {0,0,0,1,0,0},
        {0,0,0,1,0,0},
        {0,0,0,1,0,0},
        {0,0,1,0,0,0}
    },
    // *
    {
        {0,0,0,0,0,0},
        {0,0,1,0,1,0},
        {0,0,0,1,0,0},
        {0,1,1,1,1,1},
        {0,0,0,1,0,0},
        {0,0,1,0,1,0}
    },
    // +
    {
        {0,0,0,0,0,0},
        {0,0,0,1,0,0},
        {0,0,0,1,0,0},
        {0,1,1,1,1,1},
        {0,0,0,1,0,0},
        {0,0,0,1,0,0}
    },
    // '
    {
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,1,0,0},
        {0,0,1,0,0,0}
    },
    // -
    {
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,1,1,1,1,1},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0}
    },
    // .
    {
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,1,0,0,0,0}
    },
    // /
    {
        {0,0,0,0,0,1},
        {0,0,0,0,1,0},
        {0,0,0,1,0,0},
        {0,0,1,0,0,0},
        {0,1,0,0,0,0},
        {1,0,0,0,0,0}
    },
    // 0
    {
        {0,1,1,1,1,0},
        {1,0,0,0,1,1},
        {1,0,0,1,0,1},
        {1,0,1,0,0,1},
        {1,1,0,0,0,1},
        {0,1,1,1,1,0}
    }, 
    // 1 
    {
        {0,0,0,1,0,0},
        {0,0,1,1,0,0},
        {0,1,0,1,0,0},
        {0,0,0,1,0,0},
        {0,0,0,1,0,0},
        {1,1,1,1,1,1}
    },
    // 2  
    {
        {0,1,1,1,1,0},
        {1,0,0,0,0,1},
        {0,0,0,0,0,1},
        {0,1,1,1,1,0},
        {1,0,0,0,0,0},
        {1,1,1,1,1,1}
    },
    // 3 
    {
        {0,1,1,1,1,0},
        {1,0,0,0,0,1},
        {0,0,0,1,1,0},
        {0,0,0,0,0,1},
        {1,0,0,0,0,1},
        {0,1,1,1,1,0}
    },
    // 4  
    {
        {0,0,0,0,1,0},
        {0,0,0,1,1,0},
        {0,0,1,0,1,0},
        {0,1,0,0,1,0},
        {1,1,1,1,1,1},
        {0,0,0,0,1,0}
    }, 
    // 5 
    {
        {1,1,1,1,1,1},
        {1,0,0,0,0,0},
        {1,1,1,1,1,0},
        {0,0,0,0,0,1},
        {1,0,0,0,0,1},
        {0,1,1,1,1,0}
    },  
    // 6
    {
        {0,1,1,1,1,0},
        {1,0,0,0,0,0},
        {1,1,1,1,1,0},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {0,1,1,1,1,0}
    }, 
    // 7 
    {
        {1,1,1,1,1,1},
        {0,0,0,0,0,1},
        {0,0,0,0,1,0},
        {0,0,0,1,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0}
    }, 
    // 8
    {
        {0,1,1,1,1,0},
        {1,0,0,0,0,1},
        {0,1,1,1,1,0},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {0,1,1,1,1,0}
    },  
    // 9
    {
        {0,1,1,1,1,0},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {0,1,1,1,1,1},
        {0,0,0,0,0,1},
        {0,1,1,1,1,0}
    },
    // :
    {
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,1,0,0,0,0},
        {0,0,0,0,0,0},
        {0,1,0,0,0,0},
        {0,0,0,0,0,0}
    },
    // ;
    {
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,1,0,0,0,0},
        {0,0,0,0,0,0},
        {0,1,0,0,0,0},
        {1,0,0,0,0,0}
    },
    // < 
    {
        {0,0,0,0,0,0},
        {0,0,0,1,0,0},
        {0,0,1,0,0,0},
        {0,1,0,0,0,0},
        {0,0,1,0,0,0},
        {0,0,0,1,0,0}
    },
    // =
    {
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,1,1,1,1,0},
        {0,0,0,0,0,0},
        {0,1,1,1,1,0},
        {0,0,0,0,0,0}
    },
    // >
    {
        {0,0,0,0,0,0},
        {0,0,1,0,0,0},
        {0,0,0,1,0,0},
        {0,0,0,0,1,0},
        {0,0,0,1,0,0},
        {0,0,1,0,0,0}
    },

    // ?
    {
        {0,0,1,1,1,0},
        {0,1,0,0,0,1},
        {0,0,0,0,1,0},
        {0,0,0,1,0,0},
        {0,0,0,0,0,0},
        {0,0,0,1,0,0}
    },
    // @
    {
        {1,1,1,1,1,1},
        {1,0,0,0,0,1},
        {1,0,1,1,0,1},
        {1,0,1,1,1,1},
        {1,0,0,0,0,0},
        {1,1,1,1,1,1}
    },
    // A  
    {
        {0,1,1,1,1,0},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,1,1,1,1,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1}
    },
    // B
    {
        {1,1,1,1,1,0},
        {1,0,0,0,0,1},
        {1,1,1,1,1,0},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,1,1,1,1,0}
    },
    // C
    {
        {0,1,1,1,1,0},
        {1,0,0,0,0,1},
        {1,0,0,0,0,0},
        {1,0,0,0,0,0},
        {1,0,0,0,0,1},
        {0,1,1,1,1,0}
    },
    // D
    {
        {1,1,1,1,0,0},
        {1,0,0,0,1,0},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,1,0},
        {1,1,1,1,0,0}
    },
    // E
    {
        {1,1,1,1,1,1},
        {1,0,0,0,0,0},
        {1,1,1,1,1,0},
        {1,0,0,0,0,0},
        {1,0,0,0,0,0},
        {1,1,1,1,1,1}
    },
    //  F
    {
        {1,1,1,1,1,1},
        {1,0,0,0,0,0},
        {1,1,1,1,1,0},
        {1,0,0,0,0,0},
        {1,0,0,0,0,0},
        {1,0,0,0,0,0}
    },
    // G
    {
        {0,1,1,1,1,0},
        {1,0,0,0,0,1},
        {1,0,0,0,0,0},
        {1,0,0,1,1,1},
        {1,0,0,0,0,1},
        {0,1,1,1,1,0}
    },
    // H
    {
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,1,1,1,1,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1}
    },
    // I
    {
        {0,0,1,1,1,0},
        {0,0,0,1,0,0},
        {0,0,0,1,0,0},
        {0,0,0,1,0,0},
        {0,0,0,1,0,0},
        {0,0,1,1,1,0}
    },
    // J
    {
        {0,0,0,1,1,1},
        {0,0,0,0,1,0},
        {0,0,0,0,1,0},
        {1,0,0,0,1,0},
        {1,0,0,0,1,0},
        {0,1,1,1,0,0}
    },
    // K
    {
        {1,0,0,0,1,0},
        {1,0,0,1,0,0},
        {1,1,1,0,0,0},
        {1,0,0,1,0,0},
        {1,0,0,0,1,0},
        {1,0,0,0,0,1}
    },
    // L
    {
        {1,0,0,0,0,0},
        {1,0,0,0,0,0},
        {1,0,0,0,0,0},
        {1,0,0,0,0,0},
        {1,0,0,0,0,0},
        {1,1,1,1,1,1}
    },
    // M
    {
        {1,0,0,0,0,1},
        {1,1,0,0,1,1},
        {1,0,1,1,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1}
    },
    // N
    {
        {1,0,0,0,0,1},
        {1,1,0,0,0,1},
        {1,0,1,0,0,1},
        {1,0,0,1,0,1},
        {1,0,0,0,1,1},
        {1,0,0,0,0,1}
    },
    // O
    {
        {0,1,1,1,1,0},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {0,1,1,1,1,0}
    },
    // P
    {
        {1,1,1,1,1,0},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,1,1,1,1,0},
        {1,0,0,0,0,0},
        {1,0,0,0,0,0}
    },
    // Q
    {
        {0,1,1,1,1,0},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,1,0,1},
        {1,0,0,0,1,1},
        {0,1,1,1,1,0}
    },
    // R
    {
        {1,1,1,1,1,0},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,1,1,1,1,0},
        {1,0,0,0,1,0},
        {1,0,0,0,0,1}
    },
    // S
    {
        {0,1,1,1,1,1},
        {1,0,0,0,0,0},
        {0,1,1,1,1,0},
        {0,0,0,0,0,1},
        {0,0,0,0,0,1},
        {1,1,1,1,1,0}
    },
    // T
    {
        {1,1,1,1,1,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0}
    },
    // U
    {
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {0,1,1,1,1,0}
    },
    // V
    {
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {0,1,0,0,1,0},
        {0,0,1,1,0,0}
    },
    // W
    {
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,1,1,0,1},
        {0,1,0,0,1,0}
    },
    // X
    {
        {1,0,0,0,0,1},
        {0,1,0,0,1,0},
        {0,0,1,1,0,0},
        {0,0,1,1,0,0},
        {0,1,0,0,1,0},
        {1,0,0,0,0,1}
    },
    // Y
    {
        {1,0,0,0,1,0},
        {0,1,0,1,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0}
    },
    // Z
    {
        {1,1,1,1,1,1},
        {0,0,0,0,1,0},
        {0,0,0,1,0,0},
        {0,0,1,0,0,0},
        {0,1,0,0,0,0},
        {1,1,1,1,1,1}
    },
    // [
    {
        {0,0,1,1,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,1,1,0,0}
    },
    // /*\*/
    {
        {1,0,0,0,0,0},
        {0,1,0,0,0,0},
        {0,0,1,0,0,0},
        {0,0,0,1,0,0},
        {0,0,0,0,1,0},
        {0,0,0,0,0,1}
    },  
    // ]
    {
        {0,0,1,1,0,0},
        {0,0,0,1,0,0},
        {0,0,0,1,0,0},
        {0,0,0,1,0,0},
        {0,0,0,1,0,0},
        {0,0,1,1,0,0}
    },
    // ^
    {
        {0,0,0,1,0,0},
        {0,0,1,0,1,0},
        {0,1,0,0,0,1},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0}
    },  
    // _
    {
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {1,1,1,1,1,1}
    }, 
    // `
    {
        {0,0,1,0,0,0},
        {0,0,0,1,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {1,1,1,1,1,1}
    }, 
    // a 
    {
        {0,0,0,0,0,0},
        {0,1,1,1,1,0},
        {0,0,0,0,0,1},
        {0,1,1,1,1,1},
        {1,0,0,0,0,1},
        {0,1,1,1,1,1}
    },
    // b
    {
        {1,0,0,0,0,0},
        {1,0,0,0,0,0},
        {1,1,1,1,1,0},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,1,1,1,1,0}
    },
    // c
    {
        {0,0,0,0,0,0},
        {0,0,1,1,1,0},
        {0,1,0,0,0,0},
        {0,1,0,0,0,0},
        {0,1,0,0,0,0},
        {0,0,1,1,1,0}
    },
    //d
    {
        {0,0,0,0,0,1},
        {0,0,0,0,0,1},
        {0,1,1,1,1,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {0,1,1,1,1,1}
    },
    //e
    {
        {0,0,0,0,0,0},
        {0,1,1,1,1,0},
        {1,0,0,0,0,1},
        {1,1,1,1,1,1},
        {1,0,0,0,0,0},
        {0,1,1,1,1,1}
    },
    //f
    {
        {0,0,0,1,1,0},
        {0,0,1,0,0,0},
        {0,0,1,1,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0}
    },
    //g
    {
        {0,0,0,0,0,0},
        {0,1,1,1,1,1},
        {1,0,0,0,0,1},
        {0,1,1,1,1,1},
        {0,0,0,0,0,1},
        {0,1,1,1,1,0}
    },
    //h
    {
        {1,0,0,0,0,0},
        {1,0,0,0,0,0},
        {1,1,1,1,1,0},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1}
    },
    //i
    {
        {0,0,0,1,0,0},
        {0,0,0,0,0,0},
        {0,0,1,1,0,0},
        {0,0,0,1,0,0},
        {0,0,0,1,0,0},
        {0,0,1,1,1,0}
    },
    //j 
    {
        {0,0,0,1,0,0},
        {0,0,0,0,0,0},
        {0,0,0,1,0,0},
        {0,0,0,1,0,0},
        {0,1,0,1,0,0},
        {0,0,1,0,0,0}
    },
    //k
    {
        {0,1,0,0,0,0},
        {0,1,0,0,1,0},
        {0,1,0,1,0,0},
        {0,1,1,0,0,0},
        {0,1,0,1,0,0},
        {0,1,0,0,1,0}
    },
    //l
    {
        {0,1,0,0,0,0},
        {0,1,0,0,0,0},
        {0,1,0,0,0,0},
        {0,1,0,0,0,0},
        {0,1,0,0,0,0},
        {0,0,1,1,0,0}
    },
    // m
    {
        {0,0,0,0,0,0},
        {1,1,1,1,0,0},
        {1,0,1,0,1,0},
        {1,0,1,0,1,0},
        {1,0,1,0,1,0},
        {1,0,1,0,1,0}
    },
    // n
    {
        {0,0,0,0,0,0},
        {0,1,1,1,0,0},
        {0,1,0,0,1,0},
        {0,1,0,0,1,0},
        {0,1,0,0,1,0},
        {0,1,0,0,1,0}
    },
    // o
    {
        {0,0,0,0,0,0},
        {0,1,1,1,1,0},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {0,1,1,1,1,0}
    },
    // p
    {
        {0,0,0,0,0,0},
        {1,1,1,1,1,0},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,1,1,1,1,0},
        {1,0,0,0,0,0}
    },
    // q
    {
        {0,0,0,0,0,0},
        {0,1,1,1,1,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {0,1,1,1,1,1},
        {0,0,0,0,0,1}
    },
    // r
    {
        {0,0,0,0,0,0},
        {1,0,1,1,1,1},
        {1,1,0,0,0,0},
        {1,0,0,0,0,0},
        {1,0,0,0,0,0},
        {1,0,0,0,0,0}
    },
    // s
    {
        {0,0,0,0,0,0},
        {0,1,1,1,1,0},
        {1,0,0,0,0,0},
        {0,1,1,1,1,0},
        {0,0,0,0,0,1},
        {1,1,1,1,1,0}
    },
    // t
    {
        {0,0,1,0,0,0},
        {0,1,1,1,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,0,1,1,0}
    },
    // u 
    {
        {0,0,0,0,0,0},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {0,1,1,1,1,0}
    },
    // v
    {
        {0,0,0,0,0,0},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {0,1,0,0,1,0},
        {0,0,1,1,0,0}
    },
    // w
    {
        {0,0,0,0,0,0},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,1,1,0,1},
        {0,1,0,0,1,0}
    },
    // x
    {
        {0,0,0,0,0,0},
        {0,1,0,0,0,1},
        {0,0,1,0,1,0},
        {0,0,0,1,0,0},
        {0,0,1,0,1,0},
        {0,1,0,0,0,1}
    },
    // y
    {
        {0,0,0,0,0,0},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {0,1,1,1,1,1},
        {0,0,0,0,0,1},
        {0,1,1,1,1,0}
    },
    // z
    {
        {0,0,0,0,0,0},
        {1,1,1,1,1,1},
        {0,0,0,0,1,0},
        {0,0,0,1,0,0},
        {0,0,1,0,0,0},
        {0,1,1,1,1,1}
    },
    // {
    {
        {0,0,0,1,0,0},
        {0,0,1,0,0,0},
        {0,1,1,0,0,0},
        {0,1,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,0,1,0,0}
    },
    // |
    {
        {0,0,0,1,0,0},
        {0,0,0,1,0,0},
        {0,0,0,1,0,0},
        {0,0,0,1,0,0},
        {0,0,0,1,0,0},
        {0,0,0,1,0,0}
    },  
    // }
    {
        {0,0,1,0,0,0},
        {0,0,0,1,0,0},
        {0,0,0,1,1,0},
        {0,0,0,1,1,0},
        {0,0,0,1,0,0},
        {0,0,1,0,0,0}
    },
    // ~
    {
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,1,1,0,1},
        {0,1,0,0,1,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0}
    },    
};


int ascii_to_array(char number)
{
    return number - TABLE_OFFSET;
}

u8* video_memory = 0x0;


void put_pixel(int y, int x, int z)
{
  video_memory[3*(x + 1280*y)] = z;
  video_memory[3*(x + 1280*y) + 1] = z>>8;
  video_memory[3*(x + 1280*y) + 2] = z>>16;
}

int write_char(int y, int x,int index)
{
  for(int i = 0; i < 6;i++)
  {
    for(int j = 0; j < 6;j++)
    {
      if(!(characters[index][i][j] == 0))
      {
        put_pixel(y+2*i+1,x+2*j,COLOR_GREEN);
        put_pixel(y+2*i+1,x+2*j+1,COLOR_GREEN);
        put_pixel(y+2*i,x+2*j,COLOR_GREEN);
        put_pixel(y+2*i,x+2*j+1,COLOR_GREEN);
      }

    }
  }
}


void clear_char(int y,int x)
{
    for(int i = 0; i < 14;i++)
    {
        for(int j = 0; j < 14;j++)
        {
            put_pixel(CHAR_SIZE*y+i,CHAR_SIZE*x+j,COLOR_BLACK);
        }
    } 
}

void remove_last_char()
{
    set_cursor_offset(get_cursor_offset() -1);
    clear_char(screen_settings.cursorY,screen_settings.cursorX);
}

void load_screen_driver()
{
    vbe_mode_info_structure *vbe = VESA_block_address;
    video_memory = vbe->framebuffer;
    clear_screen();
    screen_settings.cursorX = 0;
    screen_settings.cursorY = 0;
}

void clear_screen()
{
    memset(video_memory,COLOR_BLACK,ROW_SIZE*COLUMN_SIZE*BYTE_PER_PIXEL);
}

int get_cursor_offset()
{
    return MAX_COLS * screen_settings.cursorY + screen_settings.cursorX;
}

void set_cursor_offset(int offset)
{
    screen_settings.cursorX = offset % MAX_COLS;
    screen_settings.cursorY = offset / MAX_COLS;
}

int get_screen_offset(int col, int row) { return row * MAX_COLS + col;}
int get_screen_offset_row(int offset)   { return offset / MAX_COLS;}
int get_screen_offset_col(int offset)   { return offset % MAX_COLS;}  

int handle_scrolling()
{
    int cursor_offset = get_cursor_offset();
    int rowNumber = get_screen_offset_row(cursor_offset);

    if(rowNumber < MAX_ROWS)
    {
        return cursor_offset;
    }
    else
    {
        int offset = ROW_SIZE;
        for(int i = CHAR_SIZE;i <1024;i++)
        {
            memcpy(video_memory + 3*i*offset,video_memory + 3*((i-CHAR_SIZE)*offset),3*1280);
        }
        for(int i = 1024 - 7; i < 1024;i++)
        {
            memset(video_memory + 3*i*offset,0,3*1280);
        }
        screen_settings.cursorY--;
    }
}

void print(char* message)
{
    int i = 0;
    while(message[i] != 0)
    {   
        if((char)message[i] == '\n')
        {
            new_line();
            i++;
            handle_scrolling();
            continue;
        }
        int x = screen_settings.cursorX;
        int y = screen_settings.cursorY;
        write_char(CHAR_SIZE*y,CHAR_SIZE*x,ascii_to_array(message[i]));
        i++;
        set_cursor_offset(get_cursor_offset()+1);
        handle_scrolling();
    }
}

void println(char* message)
{
    print(message); 
    print("\n");
}

static void new_line()
{
    screen_settings.cursorY++;
    screen_settings.cursorX = 0;
}

void putch(char letter)
{
    char *message = "Z";
    *message = letter;
    print(message);
}   

u16 getHeight(){
    return (u16)COLUMN_SIZE;
}

u16 getWidth(){
    return (u16)ROW_SIZE;
}

static void print_hex(u8 _byte)
{
    int value;
    if(_byte < 10)
    {
        value = '0' + _byte;
    }
    else
    {
        _byte -= 10;
        value = 'a' + _byte;
    }
    print((char *)&value);
}

void print_byte(u8 _byte)
{
    print_hex((_byte >> 4) & 0xF);
    print_hex(_byte & 0xF);
} 

void print_word(u16 _word)
{
    print_byte((_word >> 8));
    print_byte(_word & 0xFF);
}

void print_long(u32 _long)
{
    print_word((_long >> 16) & 0xFFFF);
    print_word((_long) & 0xFFFF);
}

void print_number(u32 number)
{
    char output[15];
    memset(output,0,15);
    int i = 0;
    while(number != 0)
    {
        output[i] = '0' + (number % 10);
        number /= 10;
        i++;
    }
    for(;i >= 0;i--)
    {
        print(&output[i]);
    }
}