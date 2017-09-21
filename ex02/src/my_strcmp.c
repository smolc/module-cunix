int my_strcmp(char *str1, char *str2){
 int i = 0;
 while(*str1++ != '\0' && *str2++ != '\0'){
  if (*str1 < *str2) return -1;
  if (*str1 > *str2) return 1;
 }
 return 0;
}