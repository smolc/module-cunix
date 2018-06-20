#include "../include/minishell.h"

int mini_help(hashtable_t *ht, char **args);

char *builtInStr[] = {
  "ls",
  "cd",
  "echo",
  "export",
  "env",
  "help",
  "exit"
};
int (*builtInFunc[]) (hashtable_t *,char **) = {
  &mini_ls,
  &mini_cd,
  &mini_echo,
  &mini_export,
  &mini_env,
  &mini_help,
  &mini_exit
};

int numBuiltins()
{
  return sizeof(builtInStr) / sizeof(char *);
}

int mini_help(hashtable_t *ht, char **args)
{
  printf("Alexander`s Mini shell\nCommands:\n");
  for (int i = 0; i < numBuiltins(); i++) {
    printf("  %s\n", builtInStr[i]);
  }
}

char **splitInput(char *input)
{
  int buffsize = TOK_BUFFSIZE, pos = 0;
  char **tokens = malloc(buffsize * sizeof(char*));
  char *token;

  if(!tokens) {
    fprintf(stderr, "minishell: memory alloc error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(input, TOK_DELIM);
  while (token != NULL) {
    tokens[pos] = token;
    pos++;

    if (pos >= buffsize) {
      buffsize += TOK_BUFFSIZE;
      tokens = realloc(tokens, buffsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "minishell: memory realloc error\n");
        exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL, TOK_DELIM);
  }
  tokens[pos] = NULL;
  return tokens;
}

char *readInput(void)
{
  char *input = NULL;
  ssize_t buffsize = 0;
  getline(&input, &buffsize, stdin);
  return input;
}

int executeIt(hashtable_t *ht, char **args)
{
  if(args[0] == NULL) {
    printf("minishell: empty input, try again\n");
    return 1; }
  for(int i = 0; i < numBuiltins(); i++) {
    if(strcmp(args[0], builtInStr[i]) == 0)
      return (*builtInFunc[i])(ht, args);
    else {
      if( i == (numBuiltins()-1) ) printf("minishell: no such command\n");
    }
  }
  return 1;
}

int main()
{
  char *input;
  char **args;
  int status;
  hashtable_t *ht = hash_create(64);

  do {
    printf("$_>");
    signal(SIGINT, signal_handler);
    input = readInput();
    args = splitInput(input);
    status = executeIt(ht, args);
    free(input);
    free(args);
  } while (status);
  hash_destroy(ht, hash_func_noop);
  printf("\n\n");
  return EXIT_SUCCESS;
}

