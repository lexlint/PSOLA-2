#include "stats.h"
#include <string>   // stod()
#include "option.h" // g_option
#include "parameter.h"  // g_land_use_map


double fitness(Map<int>& plan_map);
double compactness(Map<int>& plan_map);
double cost(Map<int>& plan_map);
double core_area_index(Map<int>& plan_map);

std::map<std::string, double> statistics(Map<int>& plan_map)
{
    double w1 = std::stod(g_option["social-benefit"]);
    double w2 = std::stod(g_option["economic-benefit"]);
    double w3 = std::stod(g_option["ecological-benefit"]);

    double o1 = compactness(plan_map);
    double o2 = cost(plan_map);
    double o3 = core_area_index(plan_map);
    double fitness = w1 * o1 + w2 * o2 + w3 *o3;

    std::map<std::string, double> stats;
    stats["social-benefit"] = o1;
    stats["economic-benefit"] = o2;
    stats["ecological-benefit"] = o3;
    stats["fitness"] = fitness;

    return stats;
}

double compactness(Map<int>& plan_map)
{
    double sum = 0.0;
    int count = 0;

    for (int y = 0; y < plan_map.ysize; ++y) {
        for (int x = 0; x < plan_map.xsize; ++x) {
            int value = plan_map.atxy(x, y);
            if (value == plan_map.nodata) continue;

            int cnt = 0;
            std::vector<int> neighbors = plan_map.neighbors(x, y, 1);
            for (int i = 0; i < neighbors.size(); ++i) {
                if (neighbors.at(i) == value) cnt++;
            }

            if (neighbors.size() != 0) {
                sum += (double)cnt / neighbors.size();
            }
            count++;
        }
    }

    return count != 0 ? sum / count : 0.0;
}

double cost(Map<int>& plan_map)
{
    int sum = 0;
    int count = 0;

    for (int i = 0; i < plan_map.size(); ++i) {
        int value = plan_map.at(i);
        if (value == plan_map.nodata) continue;

        int land_use = g_land_use_map.at(i);
        if (value == land_use) sum++;
        count++;
    }

    return count != 0 ? (double)sum / count : 0.0;
}

double core_area_index(Map<int>& plan_map)
{
    return 0.0;
}