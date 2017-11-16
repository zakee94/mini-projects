#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

GLint snake_x, snake_y = 240, del_x = 1, del_y = 0, arr_x[9999], arr_y[9999];
int direction = 0, rand_x, rand_y, rr_x, size = 1;
int j = 1, speed = 20, score = 0;

void window_init() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glColor3f(1.0f, 1.0f, 1.0f);
  glutSetCursor(GLUT_CURSOR_NONE);
  glPointSize(8.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0f, 640.0f, 480.0f, 0.0f);
}

int randomize() {
  int max_x = 639, max_y = 479;

  unsigned int
    // max <= RAND_MAX < Uint_MAX, so this is okay.
    num_bins_x = (unsigned int) max_x + 1,
    num_rand_x = (unsigned int) RAND_MAX + 1,
    bin_size_x = num_rand_x / num_bins_x,
    defect_x   = num_rand_x % num_bins_x,
    // max <= RAND_MAX < Uint_MAX, so this is okay.
    num_bins_y = (unsigned int) max_y + 1,
    num_rand_y = (unsigned int) RAND_MAX + 1,
    bin_size_y = num_rand_y / num_bins_y,
    defect_y   = num_rand_y % num_bins_y;


  int x, y;
  do {
   x = random();
  }
  // This is carefully written not to overflow
  while (num_rand_x - defect_x <= (unsigned int)x);
  do {
   y = random();
  }
  // This is carefully written not to overflow
  while (num_rand_y - defect_y <= (unsigned int)y);

  // Truncated division is intentional
  rand_x = x/bin_size_x;
  rr_x = rand_x;
  rand_y = y/bin_size_y;
  //printf("yy = %d\n", rand_y);
}

void food(GLint x, GLint y) {
  int i;
  glBegin(GL_POINTS);
  rand_x = rr_x;
  glVertex2i(rand_x, rand_y);
  /*printf("ry = %d\n", rand_y);
  printf("rx = %d\n", rand_x);*/

  for (i = 0; i < 9; i++) {
    if (x == rand_x + i && y == rand_y+i) {
      size = size + 10;
      randomize();
      score = score + 30/speed;
      //printf("speed = %d\n", speed);
      printf("SCORE = %d & SPEED = x%d\n", score, 30/speed);
    }
    if (x == rand_x-i && y == rand_y-i) {
      size = size + 10;
      randomize();
      score = score + 30/speed;
      printf("SCORE = %d & SPEED = x%d\n", score, 30/speed);
    }
  }
  glEnd();
}

void collide(GLint x, GLint y) {
  int i;

  for (i = 2; i < size; i++) {
    if (x == arr_x[i] && y == arr_y[i]){
    printf("\nYOU LOSE. YOU CRASHED INTO YOURSELF !!!\n");
    printf("YOUR FINAL SCORE IS :- %d\n", score);
    exit(1);
    }
  }
}

void block(GLint x, GLint y) {
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
}

void snake_motor(GLint x, GLint y) {
  int i, k;
  //printf("curr_x = %d & curr_y = %d\n", x, y);
  //printf("%d\n", j);
  if (size > 40)
  collide(x, y);

  glClear(GL_COLOR_BUFFER_BIT);
  for (i = 0; i < size; i++) {
    if (i == 0)
      block(x, y);
    else
      block(arr_x[i], arr_y[i]);
  }
  //glVertex2i(x+20,y);
  arr_x[j] = x;
  arr_y[j] = y;
  j++;

  if (j > size){
    for (k = size; k > 1; k--) {
      arr_x[k] = arr_x[k-1];
      arr_y[k] = arr_y[k-1];
    }
    j = 1;
  }



  food(x, y);
  glFlush();
  //printf("prev_x = %d & prev_y = %d\n", prev_x, prev_y);
  //glEnd();

}

void snake_position(int direction) {
  if (direction == 1) {
    del_x = 0;
    del_y = 1;
  }
  if (direction == 2) {
    del_x = 1;
    del_y = 0;
  }
  if (direction == 3) {
    del_x = 0;
    del_y = -1;
  }
  if (direction == 4) {
    del_x = -1;
    del_y = 0;
  }

  if (snake_x > 640)
  snake_x = 0;
  if (snake_y < 0)
  snake_y = 480;
  if (snake_x < 0)
  snake_x = 640;
  if (snake_y > 480)
  snake_y = 0;

  snake_x = snake_x + del_x;
  snake_y = snake_y + del_y;

  //printf("x = %d & y = %d\n", snake_x, snake_y);
}

void keyPressed (unsigned char key, int x, int y) {
  if (direction != 3)
  if (key == 's' || key == 'S'){
  direction = 1;
  //printf("S");
  }
  if (direction != 4)
  if (key == 'd' || key == 'D'){
  direction = 2;
  //printf("D");
  }
  if (direction != 1)
  if (key == 'w' || key == 'W'){
  direction = 3;
  //printf("W");
  }
  if (direction != 2)
  if (key == 'a' || key == 'A'){
  direction = 4;
  //printf("A");
  }
  if (key == 'p' || key == 'P'){
    if (speed >= 2)
      speed--;
  //printf("P");
  }
  if (key == 'l' || key == 'L'){
    if (speed <= 30)
      speed++;
  //printf("L");
  }
}

void update(int value) {
  glutKeyboardFunc(keyPressed);
  //printf("%d", direction);
  snake_position(direction);
  glutTimerFunc(speed, update, 0);
  snake_motor(snake_x, snake_y);
  //glutPostRedisplay();
}

void myDisplay() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);
  glEnd();
  glFlush();
}

void main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(1024, 768);
  glutInitWindowPosition(100, 50);
  glutCreateWindow("Snakes");
  randomize();
  glutDisplayFunc(myDisplay);
  glutTimerFunc(speed, update, 0);
  window_init();
  glutMainLoop();
}
