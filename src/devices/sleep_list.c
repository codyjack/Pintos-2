/* sleep_list.c */

#include "threads/malloc.h"
#include "devices/sleep_list.h"
#include "threads/synch.h"
#include "threads/interrupt.h"
#include <stdio.h>

void
add_new_sleep_thread(sleep_list** list, int64_t wake_up_time)
{
  sleep_list* new_list_element = malloc(sizeof(sleep_list));
  sleep_list* current = NULL;
  sleep_list* temp = NULL;
  struct semaphore* sema = malloc(sizeof(struct semaphore));

  sema_init(sema, 0);
  new_list_element->sema = sema;
  new_list_element->next = NULL;
  new_list_element->scheduled_time = wake_up_time;

/*  if (*list == NULL)
  {
    *list = new_list_element;
  }
  else if (NULL == (*list)->next)
  {
    if ((*list)->scheduled_time > new_list_element->scheduled_time) 
    {
      new_list_element->next = *list;
      *list = new_list_element;
    }
    else
    {
      (*list)->next = new_list_element;
    }
  }
  else
  {
    current = *list;
    //printf("outside add loop\n");
    while ((current->next != NULL) && (current->next->scheduled_time > new_list_element->scheduled_time))
    {
    //  printf("inside add loop\n");
      current = current->next;
    }
    temp = current->next;
    current->next = new_list_element;
    new_list_element->next = temp;
  } */

/*Richard this is what was changed John's logic take a look  */
  if (*list == NULL) {
    *list = new_list_element;
  }

  /* add in front */
  else if ((*list)->scheduled_time > new_list_element->scheduled_time )
  {
    new_list_element->next = *list;
    *list = new_list_element;
  }
  
  /* add in middle or last */
  else {
    current = *list;
    while ((current->next != NULL) && (current->next->scheduled_time < new_list_element->scheduled_time))
    {
      current = current->next;
    }
    // current should now point to the spot in the list just 
    // before the spot where the new element should go.
    temp = current->next;
    current->next = new_list_element;
    new_list_element->next = temp;
  }

  sema_down(sema);
  //printf("ive woke up\n");
  free(new_list_element);
  free(sema);
}

int check_current_head (sleep_list* list, int64_t time)
{
  if (NULL == list)
  {
    return 0;
  }
  if (list->scheduled_time <= time)
  {
    return 1;
  }
  return 0;
}

void unlock_current_head (sleep_list** list)
{
  sleep_list* head = *list;
  *list = head->next;
  sema_up(head->sema);
}
