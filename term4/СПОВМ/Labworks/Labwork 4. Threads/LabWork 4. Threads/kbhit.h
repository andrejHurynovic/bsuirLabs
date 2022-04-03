//
//  kbhit.h
//  LabWork 2. Synchronization
//
//  Created by Andrej Hurynovič on 9.03.21.
//

#ifndef kbhit_h
#define kbhit_h

#include <sys/ioctl.h>
#include <termios.h>

#include <termios.h>
    
class keyboard{
    public:
        keyboard();
        ~keyboard();
        int kbhit();
        int getch();

    private:
        struct termios initial_settings, new_settings;
        int peek_character;
};


#endif /* kbhit_h */
