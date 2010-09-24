/* sleep_list.h */
// blank

#ifndef SLEEP_LIST_H
#define SLEEP_LIST_H

#include <stdint.h>

/*  List of semaphore and the time they will be unlocked.
 *  List is in order of time to be unlocked. 
 */
struct sleep_list
  {
    int64_t scheduled_time;
    struct semaphore* sema;
    struct sleep_list* next;
  };

typedef struct sleep_list sleep_list;

/*  Adds a new thread to the wait list in the proper 
 *  place in the list .
 */
void add_new_sleep_thread (sleep_list**, int64_t);

/*  Checks the current head of the list if its time has 
 *  been reached. Returns 1 if reached, 0 otherwie.
 */
int check_current_head (sleep_list*, int64_t);

/*  Unlocks the semaphore at the current head, makes the 
 *  next in line the new head. 
 */
void unlock_current_head (sleep_list**);

#endif
