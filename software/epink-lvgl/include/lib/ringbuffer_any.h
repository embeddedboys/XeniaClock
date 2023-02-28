/**
 * @file ringbuffer_any.h
 * @author IotaHydrae (writeforever@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2023-02-20
 *
 * MIT License
 *
 * Copyright 2022 IotaHydrae(writeforever@foxmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *
 */

#include <inttypes.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
/**
 * @file
 * Prototypes and structures for the ring buffer module.
 */

#ifndef RINGBUFFER_ANY_H
#define RINGBUFFER_ANY_H

#ifdef __cplusplus
extern "C"
{
#endif

#define RING_BUFFER_ANY_ASSERT(x) assert(x)

/**
 * Checks if the buffer_size is a power of two.
 * Due to the design only <tt> RING_BUFFER_SIZE-1 </tt> items
 * can be contained in the buffer.
 * buffer_size must be a power of two.
*/
#define RING_BUFFER_ANY_IS_POWER_OF_TWO(buffer_size) ((buffer_size & (buffer_size - 1)) == 0)

/**
 * The type which is used to hold the size
 * and the indicies of the buffer.
 */
typedef size_t ring_buffer_any_size_t;

/**
 * Used as a modulo operator
 * as <tt> a % b = (a & (b − 1)) </tt>
 * where \c a is a positive index in the buffer and
 * \c b is the (power of two) size of the buffer.
 */
#define RING_BUFFER_ANY_MASK(rb) (rb->buffer_mask)


/**
 * @brief
 * `rb` - the ring buffer object
 * `src` - any struct node, not a pointer
 */
#define ring_buffer_any_push(rb, src) \
    ring_buffer_any_queue(rb, &src, sizeof(__typeof(src)));

#define ring_buffer_any_pop(rb, dst) \
    ring_buffer_any_dequeue(rb, &dst, sizeof(__typeof(dst)));

/**
 * Simplifies the use of <tt>struct ring_buffer_any_t</tt>.
 */
typedef struct ring_buffer_any_t ring_buffer_any_t;

/**
 * Structure which holds a ring buffer.
 * The buffer contains a buffer array
 * as well as metadata for the ring buffer.
 */
struct ring_buffer_any_t {
    /** Buffer memory. */
    void *buffer;
    /** Buffer mask. */
    ring_buffer_any_size_t buffer_mask;
    /** Index of tail. */
    ring_buffer_any_size_t tail_index;
    /** Index of head. */
    ring_buffer_any_size_t head_index;
};

#define RINGBUFFER_ANY_INIT(name, buf) \
    struct ring_buffer_any_t name = {     \
        .buffer = buf,                  \
        .buffer_mask = sizeof(buf)/sizeof(buf[0]) - 1,  \
        .tail_index = 0,  \
        .head_index = 0,  \
    }

/**
 * Initializes the ring buffer pointed to by <em>buffer</em>.
 * This function can also be used to empty/reset the buffer.
 * @param buffer The ring buffer to initialize.
 * @param buf_size The size of the allocated ringbuffer.
 */
void ring_buffer_any_init(ring_buffer_any_t *buffer, void *buf,  size_t buf_size);

/**
 * Adds a byte to a ring buffer.
 * @param buffer The buffer in which the data should be placed.
 * @param src The byte to place.
 */
void ring_buffer_any_queue(ring_buffer_any_t *buffer, void *src, size_t len);

/**
 * Adds an array of bytes to a ring buffer.
 * @param buffer The buffer in which the data should be placed.
 * @param data A pointer to the array of bytes to place in the queue.
 * @param size The size of the array.
 */
void ring_buffer_any_queue_arr(ring_buffer_any_t *buffer, const char *data,
                           ring_buffer_any_size_t size);

/**
 * Returns the oldest byte in a ring buffer.
 * @param buffer The buffer from which the data should be returned.
 * @param data A pointer to the location at which the data should be placed.
 * @return 1 if data was returned; 0 otherwise.
 */
uint8_t ring_buffer_any_dequeue(ring_buffer_any_t *buffer, void *dst, size_t len);

/**
 * Returns the <em>len</em> oldest bytes in a ring buffer.
 * @param buffer The buffer from which the data should be returned.
 * @param data A pointer to the array at which the data should be placed.
 * @param len The maximum number of bytes to return.
 * @return The number of bytes returned.
 */
ring_buffer_any_size_t ring_buffer_any_dequeue_arr(ring_buffer_any_t *buffer, char *data,
                                           ring_buffer_any_size_t len);
/**
 * Peeks a ring buffer, i.e. returns an element without removing it.
 * @param buffer The buffer from which the data should be returned.
 * @param data A pointer to the location at which the data should be placed.
 * @param index The index to peek.
 * @return 1 if data was returned; 0 otherwise.
 */
uint8_t ring_buffer_any_peek(ring_buffer_any_t *buffer, char *data, ring_buffer_any_size_t index);


/**
 * Returns whether a ring buffer is empty.
 * @param buffer The buffer for which it should be returned whether it is empty.
 * @return 1 if empty; 0 otherwise.
 */
inline uint8_t ring_buffer_any_is_empty(ring_buffer_any_t *buffer)
{
    return (buffer->head_index == buffer->tail_index);
}

/**
 * Returns whether a ring buffer is full.
 * @param buffer The buffer for which it should be returned whether it is full.
 * @return 1 if full; 0 otherwise.
 */
inline uint8_t ring_buffer_any_is_full(ring_buffer_any_t *buffer)
{
    return ((buffer->head_index - buffer->tail_index) & RING_BUFFER_ANY_MASK(
                        buffer)) == RING_BUFFER_ANY_MASK(buffer);
}

/**
 * Returns the number of items in a ring buffer.
 * @param buffer The buffer for which the number of items should be returned.
 * @return The number of items in the ring buffer.
 */
inline ring_buffer_any_size_t ring_buffer_any_num_items(ring_buffer_any_t *buffer)
{
    return ((buffer->head_index - buffer->tail_index) & RING_BUFFER_ANY_MASK(buffer));
}

#ifdef __cplusplus
}
#endif

#endif /* RINGBUFFER_ANY_H */
