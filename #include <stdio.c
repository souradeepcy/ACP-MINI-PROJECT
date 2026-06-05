#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 20
#define COLS 40
char canvas[ROWS][COLS];

// Initialize canvas
void initialize_canvas() {
  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLS; j++)
      canvas[i][j] = '_';
}

// Display canvas
void display_canvas() {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++)
      printf("%c", canvas[i][j]);
    printf("\n");
  }
}

// Draw rectangle
void draw_rectangle(int x, int y, int w, int h) {
  for (int i = x; i < x + h && i < ROWS; i++)
    for (int j = y; j < y + w && j < COLS; j++)
      canvas[i][j] = '*';
}

// Draw line (simple version)
void draw_line(int x1, int y1, int x2, int y2) {
  int dx = abs(x2 - x1), dy = abs(y2 - y1);
  int sx = (x1 < x2) ? 1 : -1;
  int sy = (y1 < y2) ? 1 : -1;
  int err = dx - dy;

  while (1) {
    if (x1 >= 0 && x1 < ROWS && y1 >= 0 && y1 < COLS)
      canvas[x1][y1] = '*';
    if (x1 == x2 && y1 == y2)
      break;
    int e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      x1 += sx;
    }
    if (e2 < dx) {
      err += dx;
      y1 += sy;
    }
  }
}

// Draw circle
void draw_circle(int xc, int yc, int r) {
  for (int x = -r; x <= r; x++) {
    for (int y = -r; y <= r; y++) {
      if (x * x + y * y <= r * r + 1) {
        int px = xc + x, py = yc + y;
        if (px >= 0 && px < ROWS && py >= 0 && py < COLS)
          canvas[px][py] = '*';
      }
    }
  }
}

// Draw triangle
void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
  draw_line(x1, y1, x2, y2);
  draw_line(x2, y2, x3, y3);
  draw_line(x3, y3, x1, y1);
}

// Delete object (replace region with '_')
void delete_object(int x, int y, int w, int h) {
  for (int i = x; i < x + h && i < ROWS; i++)
    for (int j = y; j < y + w && j < COLS; j++)
      canvas[i][j] = '_';
}

// Menu
int main() {
  int choice;
  initialize_canvas();

  while (1) {
    printf("\nMenu:\n");
    printf("1. Draw Rectangle\n");
    printf("2. Draw Line\n");
    printf("3. Draw Circle\n");
    printf("4. Draw Triangle\n");
    printf("5. Delete Object\n");
    printf("6. Display Canvas\n");
    printf("7. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
      int x, y, w, h;
      printf("Enter x y w h: ");
      scanf("%d%d%d%d", &x, &y, &w, &h);
      draw_rectangle(x, y, w, h);
    } else if (choice == 2) {
      int x1, y1, x2, y2;
      printf("Enter x1 y1 x2 y2: ");
      scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
      draw_line(x1, y1, x2, y2);
    } else if (choice == 3) {
      int xc, yc, r;
      printf("Enter center x y and radius: ");
      scanf("%d%d%d", &xc, &yc, &r);
      draw_circle(xc, yc, r);
    } else if (choice == 4) {
      int x1, y1, x2, y2, x3, y3;
      printf("Enter three points: ");
      scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3);
      draw_triangle(x1, y1, x2, y2, x3, y3);
    } else if (choice == 5) {
      int x, y, w, h;
      printf("Enter x y w h: ");
      scanf("%d%d%d%d", &x, &y, &w, &h);
      delete_object(x, y, w, h);
    } else if (choice == 6) {
      display_canvas();
    } else if (choice == 7) {
      break;
    } else {
      printf("Invalid choice!\n");
    }
  }
  return 0;
}
