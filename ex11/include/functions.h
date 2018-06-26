#ifndef FUNCS_H
#define FUNCS_H

#include "hash.h"

void hash_func_noop(void *data, void *key);

int mini_ls(hashtable_t *ht, char **args);

int mini_echo(hashtable_t *ht, char **args);

int mini_export(hashtable_t *ht, char **args);

int mini_env(hashtable_t *ht, char **args);

int mini_cd(hashtable_t *ht, char **args);

int mini_exit(hashtable_t *ht, char **args);

int mini_help(hashtable_t *ht, char **args);

void signal_handler(int sign);
#endif

