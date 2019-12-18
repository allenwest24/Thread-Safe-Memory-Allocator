/*#ifndef OPT_MALLOC_H
#define OPT_MALLOC_H

typedef struct hm_stats {
	long pages_mapped;
	long pages_unmapped;
	long chunks_allocated;
	long chunks_freed;
	long free_length;
} hm_stats;

//hm_stats hgetstats();
//void hprintstats();
void* opt_malloc(size_t usize);
void opt_free(void* addr);
void* opt_realloc(void* prev, size_t bytes);

#endif
*/
