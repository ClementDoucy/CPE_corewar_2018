/*
** EPITECH PROJECT, 2019
** mystring
** File description:
** mystring
*/

#ifndef MYSTRING_H_
    #define MYSTRING_H_

//INCLUDES///////////////////
#include <errno.h>         //
#include <stdio.h>         //
#include <unistd.h>        //
#include <stdlib.h>        //
#include <stdbool.h>       //
#include "get_next_line.h" //
//!_INCLUDES_!///////////////

/* No function parameters will be freed; all frees happen internally */

/*
Functions with "MLC" need their return value to be checked in case
malloc failed.
*/

//COUNTING////////////////////////////////////////////
size_t my_arrlen(char **arr);                       //
size_t _sizeof_arr(char **arr);                     //
size_t my_nstrcountw(char *str);                    //
size_t my_strlen(char const *str);                  //
size_t my_strcountw(char *str, char *delims);       //
size_t my_strlen_stop(char const *str, char stop);  //
//!_COUNTING_!////////////////////////////////////////

//STR_TO_NBR///////////////
int my_atoi(char *nbr);  //
float my_atof(char *n);  //
double my_atod(char *n); //
//!_STR_TO_NBR_!///////////

//CHAR_CHECK//////////////////////////////
int is_space(char c);                   //
int is_alpha(char c);                   //
int is_digit(char c);                   //
int is_alpha_numeric(char c);           //
int char_in(char c, char const *is_in); //
//!_CHAR_CHECK_!//////////////////////////

//STR_NBR_CHECK////////////////
int is_str_int(char *str);   //
int is_str_float(char *str); //
//!_STR_NBR_CHECK_!////////////

//OUTPUT////////////////////////////////////
int my_putchar(int std, char c);          //
int my_putstr(int std, const char *str);  //
int my_putarr(int std, char **arr);       //
int my_put_nbr(int nb);
//!_OUTPUT_!////////////////////////////////

//STR_COMPARISON////////////////////////////////////////////////////////
int my_strcmp(const char *str1, const char *str2);                    //
int is_same_str(const char *str1, const char *str2);                  //
int my_strncmp(const char *str1, const char *str2, size_t n);         //
int is_same_str_stop(const char *str1, const char *str2, char stop);  //
//!_STR_COMPARISON_!////////////////////////////////////////////////////

//STR_FLAGGERS////////////////////////////
char *my_strchr(char *str, char c);     //
char *my_strrchr(char *str, char c);    //
char *my_strchrnul(char *str, char c);  //
char *my_strrchrnul(char *str, char c); //
//!_STR_FLAGGER_!/////////////////////////

//STR_CPY//////////////////////////////////////////////////
char *my_strdup(char const *str);                        // [MLC]
char *my_strndup(char const *str, size_t n);             // [MLC]
char *my_strcpy(char *dest, char const *cpy);            //
char *my_strncpy(char *dest, char const *cpy, size_t n); //
//!_STR_CPY_!//////////////////////////////////////////////

//STR_CONCAT///////////////////////////////////////////////////
char *my_strmerge(char *str1, char *str2);                   // [MLC]
char *my_strcat(char *start, char const *end);               //
char *my_strncat(char *start, char const *end, size_t n);    //
char *my_strmerge_plus(char *str1, char *str2, char *split); // [MLC]
//!_STR_CONCAT_!///////////////////////////////////////////////

//STR_CLEANER///////////////////////////////////
char *my_strepure(char const *str, char *rm); // [MLC]
//!_STR_CLEANER_!///////////////////////////////

//STR_TO_ARRAY///////////////////////////////////////
char **str_to_word_array(char *str, char *delims); // [MLC]
//!_STR_TO_ARRAY_!///////////////////////////////////

//FREE/////////////////////////////////////////////
int ifree(void *ptr);                            //
void sfree(void *ptr);                           //
void *sfree_null(void *ptr);                     //
void **free_arr_null(void **arr, bool free_arr); //
//!_FREE_!/////////////////////////////////////////

//MEMORY///////////////////////////////////////////
void *my_memset(char *str, char fill, size_t n); //
void *my_memcpy(void *dest, void *src, size_t nb);
//!_MEMORY_!///////////////////////////////////////

//ARRAY/////////////////////////////////////////////////////
char **my_arrdup(char **arr);                             // [MLC]
char **arr_remove_index(char **arr, int ind);             //
char **arr_add_index(char **arr, char *stradd, int ind);  //
//!_ARRAY_!/////////////////////////////////////////////////

//CONVERT
int my_hexa_to_dec(char *);
unsigned int convert_endian_number(unsigned int nb);
unsigned short int convert_endian_number_short(unsigned short int nb);

char *my_revstr(char *);

#endif /* !MYSTRING_H_ */
