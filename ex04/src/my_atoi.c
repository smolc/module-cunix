int my_atoi(const char *nptr){
  int num = 0;
  int k = (*nptr == '-' ? -1 : 1);
  int i = (k == -1 ? 1 : 0);
  while(*(nptr + i) >= '0' && *(nptr + i) <= '9'){
    num = num*10 + (*(nptr + i) - '0');
    i++;
  }
  return num*k;
}