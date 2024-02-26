#ifndef UTILS_H
# define UTILS_H

# include "libs.h"

/*
 * @brief Function to close a file descriptor
 *
 * @param fd A pointer to the file descriptor
 * 
 * @note The difference with the `close` function is that, in addition,
 *       this function sets the content of the variable to -1
*/
void	close_better(int *fd);

/*
 * @brief Function to close the pipes used on the programm
 *
 * @param pipe1 Pipe number 1
 * @param pipe2 Pipe number 2
*/
void	close_pipes(int *pipe1, int *pipe2);

#endif