unsigned int my_strlen(char* str){
  unsigned int i = 0;
  while (*str++ != '\0')
    i++;
  return i;
}
