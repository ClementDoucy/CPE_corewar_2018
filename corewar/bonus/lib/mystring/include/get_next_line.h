/*
** EPITECH PROJECT, 2018
** CPE_getnextline_2018
** File description:
** get_next_line
*/

#ifndef  READ_SIZE
    #define  READ_SIZE (80)
#endif  /* !READ_SIZE  */

#ifndef MACROS
    #define MACROS
#define IS_READ_OK(mread)      if ((mread) < 0) return NULL
#define IS_MALLOCD(str)        if (!(str)) return NULL
#define my_memset_(buf, n, c)   for (int i = 0; i < n; i++) (buf[i]) = c
#define my_strcpy_(d, c)        for (int j = 0; c[j] != 0; d[j] = c[j], j++)
#define my_strlen_(str, len)    for (; str[len] != 0; len++)
#define BREAK_IF_EOF(m)        if (!m) break;
#define CHECK_FILE(fd, rsize)  if (fd < 0 || rsize <= 0) return NULL
#define IS_CONCATED(my_read)   if ((my_read) == -1) return NULL
#endif /* !MACROS */

#ifndef GET_NEXT_LINE_H_
    #define GET_NEXT_LINE_H_
char *get_next_line(int fd);
#endif /* !GET_NEXT_LINE_H_ */