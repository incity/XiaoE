#ifndef _TINYPLAY_H
#define _TINYPLAY_H

extern int tinyplay(const char *filename);
extern int tinymix(int ctrl_num, char* value);
extern void tinyplay_SetPlayFileName(const char *filename);
extern void tinyplay_RequestPlay(int flag);
extern void tinyplay_init();

#endif
