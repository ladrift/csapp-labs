/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    if (q == NULL) {
        return NULL;
    }

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;

    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL) {
        return;
    }

    list_ele_t *curr = q->head;
    list_ele_t *to_free = NULL;

    /* Free each element */
    while (curr != NULL) {
        to_free = curr;
        curr = curr->next;
        free(to_free);
    }

    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
    if (q == NULL) {
        return false;
    }

    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    /* What if malloc returned NULL? */
    if (newh == NULL) {
        return false;
    }

    newh->value = v;
    newh->next = q->head;
    q->head = newh;

    q->size += 1;

    /* If this is the first element in the queue, point tail to it too. */
    if (q->size == 1) {
        q->tail = newh;
    }
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    if (q == NULL) {
        return false;
    }

    list_ele_t *newt = malloc(sizeof(list_ele_t));
    if (newt == NULL) {
        return false;
    }

    newt->value = v;
    newt->next = NULL;

    q->size += 1;

    if (q->size == 0) {
        /* List q is empty now, just insert it as the first element. */
        q->head = newt;
        q->tail = newt;
    } else {
        q->tail->next = newt;
        q->tail = newt;
    }

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
    if (q == NULL || q->size == 0) {
        return false;
    }

    list_ele_t *to_free = q->head;

    q->head = q->head->next;
    q->size -= 1;

    if (q->size == 0) {
        q->tail = NULL;
    }

    if (vp != NULL) {
        *vp = to_free->value;
    }

    free(to_free);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL) {
        return 0;
    }

    return q->size;
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL || q->size < 2) {
        return;
    }

    /* list is broken up between prev and curr.
       curr->next === next
    */
    list_ele_t *prev = NULL;
    list_ele_t *curr = q->head;
    list_ele_t *next = curr->next;

    q->tail = q->head;

    while(next != NULL) {
        curr->next = prev;
        prev = curr;
        curr = next;
        next = curr->next;
    }

    curr->next = prev;

    q->head = curr;
}

