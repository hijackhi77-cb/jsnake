#include <ncurses.h>

int
main()
{
    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    while (true) {
        if (getch() == 'g') {
            printw("You pressed G\n");
        }
        napms(500);
        printw("Running\n");
    }
}