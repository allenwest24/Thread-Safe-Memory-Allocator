# Thread-Safe-Memory-Allocator
Memory allocator that beats the system memory allocator time when threaded.

A Makefile is included that links these two programs with each of three different memory allocators: the system allocator and 
two allocators. One that is not thread safe and one that is.
    The hmalloc.c is made thread safe by adding a single mutex guarding the free list. There are no data races when calling 
    hmalloc/hfree functions concurrently from multiple threads.
    Implementation of realloc.
    Edited hmalloc.

Features:
    My par_malloc is faster than sys_malloc.
    My par_malloc correctly handles coalescing when malloc and free occur in the same thread.
    My par_malloc correctly handles coalescing when malloc and free occur in different threads.
