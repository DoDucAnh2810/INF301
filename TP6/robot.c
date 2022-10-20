#include "robot.h"
#include <stdio.h>

void init_robot(Robot *r, int x, int y, Orientation o){
  r->x = x;
  r->y = y;
  r->o = o;
}

void avancer(Robot *r){
  switch (r->o)
  {
  case Nord:
    r->y--;
    break;
  case Sud:
    r->y++;
    break;
  case Ouest:
    r->x--;
    break;
  case Est:
    r->x++;
  default:;
  }
}

void tourner_a_gauche(Robot *r){
  switch (r->o)
  {
  case Nord:
    r->o = Ouest;
    break;
  case Sud:
    r->o = Est;
    break;
  case Ouest:
    r->o = Sud;
    break;
  case Est:
    r->o = Nord;
  default:;
  }
}

void tourner_a_droite(Robot *r){
  switch (r->o)
  {
  case Nord:
    r->o = Est;
    break;
  case Sud:
    r->o = Ouest;
    break;
  case Ouest:
    r->o = Nord;
    break;
  case Est:
    r->o = Sud;
  default:;
  }
}

void position(Robot *r, int *x, int *y){
  *x = r->x;
  *y = r->y;
}

int abscisse(Robot *r){
  return r->x;
}

int ordonnee(Robot *r){
  return r->y;
}

Orientation orient(Robot *r){
  return r->o;
}

void position_devant(Robot *r, int *x, int *y){
  int p_x = abscisse(r);
  int p_y = ordonnee(r);
  Orientation o = orient(r);
  switch (o)
  {
  case Nord:
    *y = p_y--;
    break;
  case Sud:
    *y = p_y++;
    break;
  case Ouest:
    *x = p_x--;
    break;
  case Est:
    *x = p_x++;
  default:;
  }
}

