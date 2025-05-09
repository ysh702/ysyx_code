#ifndef WATCHPOINT_H
#define WATCHPOINT_H
#include "common.h"
typedef struct watchpoint {
    // 定义 watchpoint 结构体
 int NO;
  struct watchpoint *next;
  char expr[32];
  word_t old_value;
  /* TODO: Add more members if necessary */
} WP;
 
void init_wp_pool();
void set_wp(char *arg, word_t value);
void scan_wp();
void display_wp();
void delete_wp(int n);
 
#endif // WATCHPOINT_H
