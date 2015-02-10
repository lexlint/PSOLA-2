#ifndef RULE_H
#define RULE_H

#include "planmap.h"

int neighbors_has(Cell* cell, int value, int radius);

bool core_edge_operator(Cell* cell, double p);

void neighbors_operator(Cell* cell, int level);

#endif