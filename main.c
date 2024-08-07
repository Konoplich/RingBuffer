#include "ringbuffer.h"
#include <stdio.h>
#include <stdlib.h>

struct test
{
	int index;
	char msg[255];
};

void main (int argc, char **argv)
{
	int ret;
	printf ("start\n");
	struct test t1 = {.index=0, .msg = "msg1"};
	struct test t2 = {.index=1, .msg = "msg2"};
	struct test t3 = {.index=3, .msg = "msg3"};
	struct test t4 = {.index=4, .msg = "msg4"};


	struct test dst;

	printf ("init\n");
	printf ("t1: %d, %s\n", t1.index, t1.msg);
	printf ("t2: %d, %s\n", t2.index, t2.msg);

	ringbuffer *buf;
	buf = ringbuffer_new (2, sizeof (struct test));
	ringbuffer_try_write (buf, &t1, sizeof (struct test));
	ringbuffer_try_write (buf, &t2, sizeof (struct test));
	ringbuffer_try_read (buf, &dst, sizeof (struct test));
	printf ("%d, %s\n", dst.index, dst.msg);
	ringbuffer_try_read (buf, &dst, sizeof (struct test));
	printf ("%d, %s\n", dst.index, dst.msg);
	ringbuffer_try_read (buf, &dst, sizeof (struct test));
	printf ("%d, %s\n", dst.index, dst.msg);
	ringbuffer_try_read (buf, &dst, sizeof (struct test));
	printf ("%d, %s\n", dst.index, dst.msg);
	ringbuffer_try_read (buf, &dst, sizeof (struct test));
	printf ("%d, %s\n", dst.index, dst.msg);
	ret = 0;
	ringbuffer_try_write (buf, &t3, sizeof (struct test));
	printf ("res %d\n", ret);
	ringbuffer_try_read (buf, &dst, sizeof (struct test));
	printf ("%d, %s\n", dst.index, dst.msg);
	ret = 0;
	ringbuffer_try_write (buf, &t4, sizeof (struct test));
	printf ("res %d\n", ret);
	ringbuffer_try_read (buf, &dst, sizeof (struct test));
	printf ("%d, %s\n", dst.index, dst.msg);

	return 0;
}
