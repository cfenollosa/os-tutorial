void memory_copy(char *source, char *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

/**
 * K&R implementation
 */
void int_to_ascii(int n, char str[]) {
    int i, sign,length;
    if ((sign = n) < 0) n = -n;
    i = 0;
    length=0;
    do {
        str[i++] = n % 10 + '0';
        length++;
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    //reverse
    for(int j=0;j<length/2;j++){
        char t=str[j];
        str[j]=str[length-j-1];
        str[length-j-1]=t;
    }
    str[i] = '\0';
    length++;
}
