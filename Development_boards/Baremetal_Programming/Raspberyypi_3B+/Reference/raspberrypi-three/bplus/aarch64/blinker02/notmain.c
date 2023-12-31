
//-------------------------------------------------------------------
//-------------------------------------------------------------------

extern void PUT32 ( unsigned int, unsigned int );
extern void PUT16 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void dummy ( unsigned int );

#define GPFSEL2 0x3F200008
#define GPSET0  0x3F20001C
#define GPCLR0  0x3F200028

#define SYSTIMERCLO 0x3F003004

//0x01000000 17 seconds
//0x00400000 4 seconds
//#define TIMER_BIT 0x01000000
#define TIMER_BIT 0x00400000

int notmain ( void )
{
    unsigned int ra;
    unsigned int rb;

    ra=GET32(GPFSEL2);
    ra&=~(7<<27);
    ra|=1<<27;
    PUT32(GPFSEL2,ra);

    while(1)
    {
        for(rb=0;rb<32;rb++)
        {
            PUT32(GPSET0,1<<29);
            while(1)
            {
                ra=GET32(SYSTIMERCLO);
                if((ra&=TIMER_BIT)==TIMER_BIT) break;
            }
            PUT32(GPCLR0,1<<29);
            while(1)
            {
                ra=GET32(SYSTIMERCLO);
                if((ra&=TIMER_BIT)==0) break;
            }
        }
    }
    return(0);
}

//-------------------------------------------------------------------------
//
// Copyright (c) 2014 David Welch dwelch@dwelch.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//-------------------------------------------------------------------------
