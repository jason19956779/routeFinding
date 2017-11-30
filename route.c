#include <stdio.h>
#include <stdint.h>

/* Total node number in route map */
#define NODENUM 4

/* Node that has reached flag in markTable */
#define CHECKED 1

/* Route type define */
#define UNREACHABLE 0
#define UNKNOWN -1

typedef uint32_t node_t;

node_t node = 0;
const int32_t route[NODENUM][NODENUM] = {
    {0, 3, 1, 0},
    {0, 0, 0, 3},
    {0, 0, 0, 6},
    {0, 0, 0, 0}
};

int32_t markTable[NODENUM][NODENUM*2] = {};
void initMarkTable() {
    for(int i=0; i<NODENUM; i+=1) {
        for(int j=0; j<NODENUM*2; j+=1) {
            markTable[i][j] = (j%2 == 0)? UNKNOWN : 0;
        }
    }
}

/* Test function Section */
void printMarkTable() {
    for(int i=0; i<NODENUM; i+=1) {
        for(int j=0; j<NODENUM*2; j+=1) {
            printf("%d ", markTable[i][j]);
        }
        printf("\n");
    }
}

uint32_t counter = 0; /* Find path counter */

void setMarkedDistance(node_t node, int32_t distance) {
    markTable[node][counter*2] = distance;
}

/* Mark this node as checked node */
void nodeChecked(node_t node, uint32_t counter) {
    markTable[node][counter*2+1] = CHECKED;
}

void setStartingPoint() {
    counter = 0;
    setMarkedDistance(0, 0);
    nodeChecked(0, (uint32_t)counter);
    counter += 1;
}

int32_t getDistance(node_t a, node_t b) {
    return route[a][b];
}

int32_t getMarkedDistance(node_t node, uint32_t counter) {
    return markTable[node][counter*2];
}

int32_t min(int32_t a, int32_t b) {
    return (a == UNKNOWN || a > b)? b : a;
}

node_t nearestNode(node_t current) {
    node_t nearest = current;
    int32_t minDis = UNKNOWN;
    for(int i=0; i<NODENUM; i+=1) {
        int32_t dis = getDistance(current, i);
        if(dis > 0) {
            setMarkedDistance(i, min(getMarkedDistance(i, counter), getMarkedDistance(current, counter-1) + dis));
            if(getMarkedDistance(i, counter) < minDis) nearest = i;
            minDis = getMarkedDistance(i, counter);
        }
        else {
            setMarkedDistance(i, 0);
        }
        printf("loop %d min %d\n", i, minDis);
        printMarkTable();
    }

    counter += 1;
    return nearest;
}

int main() {
    node_t current = 0;
    node_t next = 0;

    initMarkTable();
    setStartingPoint();
    printMarkTable();
    
    next = nearestNode(current);
    
    printf("Next: %d\n", next);
    
    return 0;
}