#include "../include/functions.h"

void hash_func_noop(void *data, void *key)
{
  data;
  key;
}

int mini_ls(hashtable_t *ht, char **args)
  {
    struct dirent **namelist;
    int n;
    if(args[1] == NULL) {
      n = scandir(".", &namelist, NULL, alphasort);
    }
    else
      n = scandir(args[1], &namelist, NULL, alphasort);
    if(n < 0)
    {
      perror("scandir");
    }
    else
    {
      if((args[2] && !(strcmp(args[2],"-r")))) {
        while (n--) {
          if(strcmp(namelist[n]->d_name,".") && strcmp(namelist[n]->d_name,".."))
          printf("%s",namelist[n]->d_name);
          if(n > 1)
            printf(" ");
          free(namelist[n]);
        }
      } else {
      int i = 0;
      while (i < n)
      {
        if(strcmp(namelist[i]->d_name,".") && strcmp(namelist[i]->d_name,".."))
        {
          printf("%s",namelist[i]->d_name);
          if(i != n-1)
            printf(" ");
        }
        free(namelist[i]);
        ++i;
      }
    }
    free(namelist);
    printf("\n");
  }
  return 1;
}

int mini_echo(hashtable_t *ht, char **args)
{
  for (int i = 1; args[i] != NULL; i++)
  {
    if(i != 1) printf(" ");
    if(args[i][0] == '$') {
      printf("%s",hash_get(ht, args[i]+1));
    }
    else
      printf("%s",args[i]);
  }
  printf("\n");
  return 1;
}

int mini_export(hashtable_t *ht, char **args)
{
  if(args[1] == NULL) {
    printf("minishell: need more argunents\n");
  } else {
    printf("\n");
    char *dst = strtok(args[1], "=");
    char *key= malloc((strlen(dst)+1)*sizeof(char*));
    strcpy(key,dst);
    char *value;
    while(dst != NULL) {
      value = malloc((strlen(dst)+1)*sizeof(char*));
      strcpy(value,dst);
      dst = strtok(NULL, "=");
    }
    hash_set(ht, key, value, &hash_func_noop);
    }
    return 1;
 }

int mini_env(hashtable_t *ht, char **args)
{
  printf("\n");
  hash_print(ht);
  return 1;
}

int mini_cd(hashtable_t *ht, char **args)
{
  if (args[1] == NULL) {
  fprintf(stderr, "minishell: waiting for argument for \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("minishell");
    }
  }
  return 1;
}

int mini_exit(hashtable_t *ht, char **args)
{
  return 0;
}

void signal_handler(int sign) {
	if (sign == SIGINT) {
		puts("");
    write(1,"$_>",3);
		signal(SIGINT, signal_handler);
	}
}
