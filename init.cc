#include <cstdlib>
#include "init.h"
#include "option.h"

int get_land_use(int x, int y);
CellType get_cell_type(int x, int y);


PlanMap* init_map()
{
    PlanMap* map = new PlanMap(g_xsize, g_ysize, 0);
    for (int y = 0; y < g_ysize; ++y) {
        for (int x = 0; x < g_xsize; ++x) {	
            Cell* cell = map->at(x, y);
            cell->value = get_land_use(x, y);
            cell->type = get_cell_type(x, y)
            cell->transP.assign(g_max, 1.0 / g_max);
        }
    }
    map->updateFitness();

    return map;
}

Particle* init_particle()
{
    Particle* particle = new Particle();
    particle->current = init_map();
    particle->pbest = particle->current->clone();

    return particle;
}

Swarm* init_swarm(int size, int id)
{
    RND = new Random( g_seed + id );

    Swarm* swarm = new Swarm();
    swarm->momentum = g_momentum;
    swarm->c1 = g_c1;
    swarm->c2 = g_c2;
    swarm->r1 = new Random( g_r1 + id );
    swarm->r2 = new Random( g_r2 + id );

    for (int i = 0; i < size; ++i) {
        Particle* particle = init_particle();
        particle->swarm = swarm;
        swarm->particles.push_back(particle);
    }

    swarm->gbest = swarm->particles[0]->current->clone();
    swarm->updateGbest();

    return swarm;
}
