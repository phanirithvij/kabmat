#pragma once

#include <functional>
#include <ncurses.h>
#include <vector>

#include "../../helpers/win_center_text/win_center_text.h"

#include <iostream>

using namespace std;

template <typename T> class ScrollableWindow {
public:
  ScrollableWindow(int height, int width, int start_y, int start_x,
                   vector<T> *items, size_t *items_count,
                   function<void(vector<T>, WINDOW *)> draw_callback) {
    this->height = height;
    this->width = width;
    this->start_y = start_y;
    this->start_x = start_x;
    this->draw_callback = draw_callback;

    this->items = items;
    this->items_count = items_count;

    this->window =
        newwin(this->height, this->width, this->start_y, this->start_x);
  }

  void draw() {
    werase(this->window);

    if (*this->items_count > 0) {
      vector<T> shown_items = vector<T>(this->window_start, this->window_end);
      this->draw_callback(shown_items, this->window);
    } else {
      this->draw_callback({}, this->window);
    }
  }

  void scroll_up() {
    this->window_start = max(this->items->begin(), this->window_start - 1);
    this->window_end =
        this->window_start + min(*this->items_count, (size_t)this->height);
    this->draw();
  }

  void scroll_down() {
    this->window_end = min(this->items->end(), this->window_end + 1);
    this->window_start =
        this->window_end - min(*this->items_count, (size_t)this->height);
    this->draw();
  }

  void scroll_to_top() {
    if (*this->items_count > 0) {
      this->window_start = this->items->begin();
      this->window_end =
          this->window_start + min(*this->items_count, (size_t)this->height);
    }
    this->draw();
  }

  void scroll_to_bottom() {
    this->window_end = this->items->end();
    this->window_start =
        this->window_end - min(*this->items_count, (size_t)this->height);
    this->draw();
  }

  void scroll_to_offset(size_t offset) {
    this->window_start = this->items->begin() + offset;
    this->window_end =
        this->window_start + min(*this->items_count, (size_t)this->height);
    this->draw();
  }

  int height;
  int width;
  int start_y;
  int start_x;
  WINDOW *window;
  function<void(vector<T>, WINDOW *)> draw_callback;

  vector<T> *items;
  size_t *items_count;

  typename vector<T>::iterator window_start;
  typename vector<T>::iterator window_end;
};
