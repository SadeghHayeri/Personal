//
// Created by Sadegh on 1/9/18.
//
#ifndef CA5_CONFIG_H
#define CA5_CONFIG_H

#define DATA_SIZE 8
#define FRAME_SIZE 256
#define NUM_OF_FRAMES 256
#define PAGE_TABLE_SIZE 256
#define TLB_SIZE 16
#define FIFO 0
#define LRU 1
#define SECOND_CHANCE 2
#define RANDOM_REPLACEMENT 3

#define OFFSET_MASK 255
#define PAGE_NUMBER_MASK 255 << 8

#define TLB_DELAY .5 * 10
#define MEM_DELAY 100 * 10
#define DISK_DELAY 250000 * 10

#endif //CA5_CONFIG_H
