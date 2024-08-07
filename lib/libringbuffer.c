#include <stdlib.h>

#define RINGBUFFER_OK (0)
#define RINGBUFFER_ERR_NULL (-1)
#define RINGBUFFER_ERR_EMPTY (-2)
#define RINGBUFFER_ERR_FULL (-3)

#define EXPORT
typedef struct
{
	void *start;
	void *end;
	volatile void *readptr; //энергозависимый тип
	volatile void *writeptr;
	volatile int full;
} ringbuffer;

EXPORT
ringbuffer *ringbuffer_new (unsigned long int capacity,
                            size_t size)  //емкость
{
	void *mem = malloc (capacity * size);

	if (mem == NULL)
		return NULL;

	memset (mem, 0, sizeof (void *));
	ringbuffer *rb = malloc (sizeof (ringbuffer));

	if (rb == NULL)
	{
		free (mem);
		return NULL;
	}

	rb->start = mem;
	rb->end = mem + (capacity* (size-1));
	rb->readptr = mem;
	rb->writeptr = mem;
	rb->full=0;

	return rb;
}

EXPORT
void ringbuffer_delete (ringbuffer *rb)
{
	if (rb == NULL)
		return;

	free (rb->start);
	free (rb);
}

EXPORT
int ringbuffer_try_write (ringbuffer *rb, void *src, size_t size)
{
	printf ("try write\n");

	if (rb == NULL)
		return RINGBUFFER_ERR_NULL;

	if ((rb->writeptr  == rb->readptr)&&rb->full)
		return RINGBUFFER_ERR_FULL;

	memcpy (rb->writeptr, src, size); //memcpy запрещена microsoft

	void *tmp = rb->writeptr + size;

	if (tmp >= rb->end)
		tmp = rb->start;

	if (tmp==rb->readptr)
		rb->full=-1;

	rb->writeptr = tmp;

	return RINGBUFFER_OK;
}

EXPORT
int ringbuffer_try_read (ringbuffer *rb, void *dst, size_t size)
{
	if (rb == NULL)
		return RINGBUFFER_ERR_NULL;

	if ((rb->readptr == rb->writeptr)&& (!rb->full))
		return RINGBUFFER_ERR_EMPTY;

	memcpy (dst, rb->readptr, size);

	void *tmp = rb->readptr + size;
	printf ("end: %u, tmp: %u, size: %u\n", rb->end, tmp, size);

	if (tmp >= rb->end)
	{
		printf ("set start\n");
		tmp = rb->start;
	};

	if (tmp==rb->writeptr)
	{
		printf ("set empty\n");
		rb->full=0;
	};

	rb->readptr = tmp;

	return RINGBUFFER_OK;
}
