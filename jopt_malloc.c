// CS3650 CH02 starter code
// Spring 2019
//
// Author: Nat Tuck
//
// Once you've read this, you're done with the simple allocator homework.
/*
#include <stdint.h>
#include <sys/mman.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "opt_hmem.h"
#include "jopt_malloc.h"

typedef struct nu_free_cell {
    int64_t              size;
    struct nu_free_cell* next;
} nu_free_cell;

static const int64_t CHUNK_SIZE = 65536;
static const int64_t CELL_SIZE  = (int64_t)sizeof(nu_free_cell);
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// list of free_list bins:
const nu_free_cell* t_bins[];
// done.
static nu_free_cell* nu_free_list = 0;

static
int64_t
div_up(int64_t aa, int64_t bb) {
	int64_t cc = aa / bb;
	if(cc * bb == aa) {
		return cc;
	}
	else {
		return cc+1;
	}
}

int64_t
nu_free_list_length()
{
    int len = 0;

    for (nu_free_cell* pp = nu_free_list; pp != 0; pp = pp->next) {
        len++;
    }

    return len;
}

void
nu_print_free_list()
{
    nu_free_cell* pp = nu_free_list;
    printf("= Free list: =\n");

    for (; pp != 0; pp = pp->next) {
        printf("%lx: (cell %ld %lx)\n", (int64_t) pp, pp->size, (int64_t) pp->next); 

    }
}

static
void
nu_free_list_coalesce()
{
    nu_free_cell* pp = nu_free_list;
    int free_chunk = 0;

    while (pp != 0 && pp->next != 0) {
        if (((int64_t)pp) + pp->size == ((int64_t) pp->next)) {
            pp->size += pp->next->size;
            pp->next  = pp->next->next;
        }

        pp = pp->next;
    }
}

static
void
nu_free_list_insert(nu_free_cell* cell)
{
    if (nu_free_list == 0 || ((uint64_t) nu_free_list) > ((uint64_t) cell)) {
        cell->next = nu_free_list;
        nu_free_list = cell;
        return;
    }

    nu_free_cell* pp = nu_free_list;

    while (pp->next != 0 && ((uint64_t)pp->next) < ((uint64_t) cell)) {
        pp = pp->next;
    }

    cell->next = pp->next;
    pp->next = cell;

    nu_free_list_coalesce();
}

static
nu_free_cell*
free_list_get_cell(int64_t size)
{
    nu_free_cell** prev = &nu_free_list;

    for (nu_free_cell* pp = nu_free_list; pp != 0; pp = pp->next) {
        if (pp->size >= size) {
            *prev = pp->next;
            return pp;
        }
        prev = &(pp->next);
    }
    return 0;
}

static
nu_free_cell*
make_cell()
{
    void* addr = mmap(0, CHUNK_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    nu_free_cell* cell = (nu_free_cell*) addr; 
    cell->size = CHUNK_SIZE;
    return cell;
}

void*
opt_malloc(size_t usize)
{
	// Added thread variables:
	long t_count = div_up(usize, CHUNK_SIZE);
	pthread_t kids[t_count];
	int64_t rem_global_size = sizeof(int64_t) + usize % CHUNK_SIZE;
	t_bins[t_count] = nu_free_list;
	// done.
//    pthread_mutex_lock(&mutex);
    
    int64_t size = (int64_t) usize;

    // space for size
    int64_t alloc_size = size + sizeof(int64_t);

    // space for free cell when returned to list
    if (alloc_size < CELL_SIZE) {
	pthread_mutex_lock(&mutex); // only global free is used
	nu_free_list = mmap(0, CHUNK_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	nu_free_list->size = alloc_size;
	nu_free_list->next->size = CHUNK_SIZE - alloc_size;
	nu_free_list->next->next = NULL;
	pthread_mutex_unlock(&mutex); // only 1 thread used global.
	return (void*) nu_free_list;
    }
    
    // TODO: Handle large allocations.
    if (alloc_size > CHUNK_SIZE) {
	    //t_bins[t_count] = nu_free_list; // last array index = global free_list remaining
	    for (long pp = 0; pp < t_count; pp++) {
		    t_bins[pp] = pthread_create(&(kids[pp]), 0, j_hmalloc, (void*)CHUNK_SIZE);
		    t_bins[pp]->size = CHUNK_SIZE;
	    }
	    
	    // Wait for all threads to allocate memory
	    for (long pp = 0; pp < t_count; pp++) {
		    pthread_join(kids[pp], 0);
	    }
	    

	    // Create global nu_free_cell SIZE = REMAING FREE SPACE!
	    pthread_mutex_lock(&mutex);
	    nu_free_cell* cell = free_list_get_cell(rem_global_size);
	    if (!cell) {
		    cell = make_cell();
	    }
	    
	    // Resize Global nu_free_cell to remaining free space after malloc
	    if (CHUNK_SIZE >= rem_global_size) {
		    void* addr = (void*) cell;
		    cell->size = rem_global_size;
		    nu_free_list_insert(cell);
	    }
	   
	    pthread_mutex_unlock(&mutex);
	    return ((void*)cell);
    }
}

void
opt_free(void* addr) 
{
    pthread_mutex_lock(&mutex);
    nu_free_cell* cell = (nu_free_cell*)(addr - sizeof(int64_t));
    int64_t size = *((int64_t*) cell);

    if (size > CHUNK_SIZE) {
        //nu_free_chunks += 1;
        munmap((void*) cell, size);
    }
    else {
        cell->size = size;
        nu_free_list_insert(cell);
    }
    pthread_mutex_unlock(&mutex);
}

void*
opt_realloc(void* prev, size_t bytes)
{
	void* update = opt_malloc(bytes);
	long old = (long)prev;
	old = old - sizeof(long);
	size_t new_size = *((long*)old);
	if(new_size < bytes) {
		memmove(update, prev, new_size);
	}
	else {
		memmove(update, prev, bytes);
	}
	opt_free(prev);
	return update;
}
*/
