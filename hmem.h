#ifndef HMEM_H
#define HMEM_H

typedef struct hm_stats {
	long pages_mapped;
	long pages_unmapped;
	long chunks_allocated;
	long chunks_freed;
	long free_length;
} hm_stats;

//hm_stats hgetstats();
//void hprintstats();
void* hmalloc(size_t usize);
void hfree(void* addr);
void* hrealloc(void* prev, size_t bytes);

#endif
