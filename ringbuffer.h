#include <stdlib.h>
#define RINGBUFFER_OK (0)
#define RINGBUFFER_ERR_NULL (-1)
#define RINGBUFFER_ERR_EMPTY (-2)
#define RINGBUFFER_ERR_FULL (-3)

typedef struct {
	void* start;
	void* end;
	volatile void* readptr; //энергозависимый тип
	volatile void* writeptr;
	volatile int full;
} ringbuffer;

ringbuffer* ringbuffer_new(unsigned long int capacity, size_t size);
void ringbuffer_delete(ringbuffer* rb);;
int ringbuffer_try_write(ringbuffer* rb, void* src, size_t size);
int ringbuffer_try_read(ringbuffer* rb, void* dst, size_t size);
