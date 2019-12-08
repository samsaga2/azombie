#pragma once

#include <stdint.h>

void msxhal_init();

// to assign a module to a segment
#define USING_PAGE_A(module) extern const uint8_t K5_SEGMENT_TO_PAGE_A_ ## module
#define USING_PAGE_B(module) extern const uint8_t K5_SEGMENT_TO_PAGE_B_ ## module
#define USING_PAGE_C(module) extern const uint8_t K5_SEGMENT_TO_PAGE_C_ ## module
#define USING_PAGE_D(module) extern const uint8_t K5_SEGMENT_TO_PAGE_D_ ## module

// to get the page of a module
#define SEGMENT_TO_PAGE_A(module) ((const uint8_t)&K5_SEGMENT_TO_PAGE_A_ ## module)
#define SEGMENT_TO_PAGE_B(module) ((const uint8_t)&K5_SEGMENT_TO_PAGE_B_ ## module)
#define SEGMENT_TO_PAGE_C(module) ((const uint8_t)&K5_SEGMENT_TO_PAGE_C_ ## module)
#define SEGMENT_TO_PAGE_D(module) ((const uint8_t)&K5_SEGMENT_TO_PAGE_D_ ## module)

extern volatile uint8_t current_segment_a;
extern volatile uint8_t current_segment_b;
extern volatile uint8_t current_segment_c;
extern volatile uint8_t current_segment_d;

inline uint8_t load_page_a(const uint8_t newSegment) { uint8_t oldSegment = current_segment_a;
  *(uint8_t *)0x5000 = current_segment_a = (uint8_t)newSegment; return oldSegment; }

inline uint8_t load_page_b(const uint8_t newSegment) { uint8_t oldSegment = current_segment_b;
  *(uint8_t *)0x7000 = current_segment_b = (uint8_t)newSegment; return oldSegment; }

inline uint8_t load_page_c(const uint8_t newSegment) { uint8_t oldSegment = current_segment_c;
  *(uint8_t *)0x9000 = current_segment_c = (uint8_t)newSegment; return oldSegment; }

inline uint8_t load_page_d(const uint8_t newSegment) { uint8_t oldSegment = current_segment_d;
  *(uint8_t *)0xB000 = current_segment_d = (uint8_t)newSegment; return oldSegment; }

inline void restore_page_a(uint8_t oldSegment) { *(uint8_t *)0x5000 = current_segment_a = oldSegment; }
inline void restore_page_b(uint8_t oldSegment) { *(uint8_t *)0x7000 = current_segment_b = oldSegment; }
inline void restore_page_c(uint8_t oldSegment) { *(uint8_t *)0x9000 = current_segment_c = oldSegment; }
inline void restore_page_d(uint8_t oldSegment) { *(uint8_t *)0xB000 = current_segment_d = oldSegment; }

inline void fast_load_page_a(uint8_t segment) { *(uint8_t *)0x5000 = current_segment_a = segment; }
inline void fast_load_page_b(uint8_t segment) { *(uint8_t *)0x7000 = current_segment_b = segment; }
inline void fast_load_page_c(uint8_t segment) { *(uint8_t *)0x9000 = current_segment_c = segment; }
inline void fast_load_page_d(uint8_t segment) { *(uint8_t *)0xB000 = current_segment_d = segment; }

#define LOAD_PAGE_A(module) load_page_a((const uint8_t)&K5_SEGMENT_TO_PAGE_A_ ## module)
#define LOAD_PAGE_B(module) load_page_b((const uint8_t)&K5_SEGMENT_TO_PAGE_B_ ## module)
#define LOAD_PAGE_C(module) load_page_c((const uint8_t)&K5_SEGMENT_TO_PAGE_C_ ## module)
#define LOAD_PAGE_D(module) load_page_d((const uint8_t)&K5_SEGMENT_TO_PAGE_D_ ## module)

#define RESTORE_PAGE_A(module) restore_page_a((const uint8_t)&K5_SEGMENT_TO_PAGE_A_ ## module)
#define RESTORE_PAGE_B(module) restore_page_b((const uint8_t)&K5_SEGMENT_TO_PAGE_B_ ## module)
#define RESTORE_PAGE_C(module) restore_page_c((const uint8_t)&K5_SEGMENT_TO_PAGE_C_ ## module)
#define RESTORE_PAGE_D(module) restore_page_d((const uint8_t)&K5_SEGMENT_TO_PAGE_D_ ## module)

#define FAST_LOAD_PAGE_A(module) fast_load_page_a((const uint8_t)&K5_SEGMENT_TO_PAGE_A_ ## module)
#define FAST_LOAD_PAGE_B(module) fast_load_page_b((const uint8_t)&K5_SEGMENT_TO_PAGE_B_ ## module)
#define FAST_LOAD_PAGE_C(module) fast_load_page_c((const uint8_t)&K5_SEGMENT_TO_PAGE_C_ ## module)
#define FAST_LOAD_PAGE_D(module) fast_load_page_d((const uint8_t)&K5_SEGMENT_TO_PAGE_D_ ## module)

