/**
 * @file ringbuffer_any.c
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

#include "lib/ringbuffer_any.h"

/**
 * @file
 * Implementation of ring buffer functions.
 */

void ring_buffer_any_init(ring_buffer_any_t *buffer, void *buf, size_t buf_size)
{
    RING_BUFFER_ANY_ASSERT(RING_BUFFER_ANY_IS_POWER_OF_TWO(buf_size) == 1);
    buffer->buffer = buf;
    buffer->buffer_mask = buf_size - 1;
    buffer->tail_index = 0;
    buffer->head_index = 0;
}

void ring_buffer_any_queue(ring_buffer_any_t *buffer, void *src, size_t len)
{
    /* Is buffer full? */
    if (ring_buffer_any_is_full(buffer)) {
        /* Is going to overwrite the oldest byte */
        /* Increase tail index */
        buffer->tail_index = ((buffer->tail_index + 1) & RING_BUFFER_ANY_MASK(buffer));
    }

    /* Place data in buffer */
    memcpy((buffer->buffer + buffer->head_index * len), src, len);
    buffer->head_index = ((buffer->head_index + 1) & RING_BUFFER_ANY_MASK(buffer));
}

// void ring_buffer_any_queue_arr(ring_buffer_any_any_t *buffer, const char *data, ring_buffer_any_size_t size) {
//   /* Add bytes; one by one */
//   ring_buffer_any_size_t i;
//   for(i = 0; i < size; i++) {
//     ring_buffer_any_queue(buffer, data[i]);
//   }
// }

uint8_t ring_buffer_any_dequeue(ring_buffer_any_t *buffer, void *dst, size_t len)
{
    if (ring_buffer_any_is_empty(buffer)) {
        /* No items */
        return 0;
    }

    memcpy(dst, (buffer->buffer + buffer->tail_index  * len), len);
    buffer->tail_index = ((buffer->tail_index + 1) & RING_BUFFER_ANY_MASK(buffer));
    return 1;
}

// ring_buffer_any_size_t ring_buffer_any_dequeue_arr(ring_buffer_any_any_t *buffer, char *data, ring_buffer_any_size_t len) {
//   if(ring_buffer_any_is_empty(buffer)) {
//     /* No items */
//     return 0;
//   }

//   char *data_ptr = data;
//   ring_buffer_any_size_t cnt = 0;
//   while((cnt < len) && ring_buffer_any_dequeue(buffer, data_ptr)) {
//     cnt++;
//     data_ptr++;
//   }
//   return cnt;
// }

// uint8_t ring_buffer_any_peek(ring_buffer_any_any_t *buffer, char *data, ring_buffer_any_size_t index) {
//   if(index >= ring_buffer_any_num_items(buffer)) {
//     /* No items at index */
//     return 0;
//   }

//   /* Add index to pointer */
//   ring_buffer_any_size_t data_index = ((buffer->tail_index + index) & RING_BUFFER_MASK(buffer));
//   *data = buffer->buffer[data_index];
//   return 1;
// }

extern inline uint8_t ring_buffer_any_is_empty(ring_buffer_any_t *buffer);
extern inline uint8_t ring_buffer_any_is_full(ring_buffer_any_t *buffer);
extern inline ring_buffer_any_size_t ring_buffer_any_num_items(ring_buffer_any_t *buffer);

