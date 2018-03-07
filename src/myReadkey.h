#ifndef MYREADKEY_H
#define MYREADKEY_H

enum keys {
	test = 0
};

int rk_readkey(enum keys *key);
int rk_mytermsave(void);
int rk_mytermrestore(void);
int rk_mytermregime(int regime, int value, int vmin, int echo, int sigint);

#endif
