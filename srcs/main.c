#include <stdio.h>

int main(int argc, char **argv) {
  (void)argv;

  if (argc != 2) {
    fprintf(stderr, "-------------------------------\n");
    fprintf(stderr, " Please use only 2 arguments !\n");
    fprintf(stderr, " Exemple : './fdf maps/42.fdf'\n");
    fprintf(stderr, "-------------------------------\n");
  }
}
