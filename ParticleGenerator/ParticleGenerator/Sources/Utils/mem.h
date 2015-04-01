#ifndef MEM_H_DEFINED
#define MEM_H_DEFINED

void *mem_alloc(size_t size);
void *mem_realloc(void *mem, size_t size);
void *mem_dupe(void *mem, size_t size);
void *mem_dupe2(void *mem);
void mem_free(void *mem);
void mem_free_all();
size_t mem_size(void *mem);
void mem_print();

#endif