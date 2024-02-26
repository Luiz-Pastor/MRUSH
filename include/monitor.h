#ifndef MONITOR_H
# define MONITOR_H

# include "libs.h"
# include "error.h"
# include "pow.h"

/*
 * @brief Function that is responsible for checking if
 *        the results found are valid
 *
 * @param send File descriptor in which the results are sent
 * @param recieve File descriptor in which the data is recieved
 * 
 * @note The function stops when the file where the data
 *       is written to is closed
*/
void	monitor(int send, int recieve);

#endif