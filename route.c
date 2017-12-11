#include <stdio.h>
#include <stdint.h>

/* Total node number in route map */
#define NODENUM 6

/* Node that has reached flag in markTable */
#define CHECKED 1

/* Define route type */
#define UNREACHABLE 0
#define UNKNOWN -1

typedef uint32_t node_t;

node_t node = 0;
const int32_t route[NODENUM][NODENUM] = {
    {0, 4, 7, 3, 0, 0},
    {0, 0, 3, 0, 6, 0},
    {0, 0, 0, 0, 0, 4},
    {0, 0, 0, 0, 3, 0},
    {0, 0, 0, 0, 0, 2},
    {0, 0, 0, 0, 0, 0}
};

int32_t markTable[NODENUM][NODENUM*2] = {};
void initMarkTable() {
    for(int i=0; i<NODENUM; i+=1) {
        for(int j=0; j<NODENUM*2; j+=1) {
            markTable[i][j] = (j%2 == 0)? UNKNOWN : 0;
        }
    }
}

uint32_t pred[NODENUM] = {};
uint32_t counter = 0; /* Find path counter */

void setMarkedDistance(node_t node, int32_t distance) {
    for(int i=counter; i<NODENUM; i+=1)
        markTable[node][i*2] = distance;
}

/* Mark this node as checked node */
void setNodeChecked(node_t node) {
    for(int i=counter; i<NODENUM; i+=1)
        markTable[node][i*2+1] = CHECKED;
}

void setStartingPoint() {
    counter = 0;
    setMarkedDistance(0, 0);
    pred[0] = 0;
    setNodeChecked(0);
    counter += 1;
}

int32_t getDistance(node_t a, node_t b) {
    return route[a][b];
}

int32_t getMarkedDistance(node_t node, uint32_t counter) {
    return markTable[node][counter*2];
}

int32_t getCheckedNode(node_t node, uint32_t counter) {
    return markTable[node][counter*2+1];
}

int32_t min(int32_t a, int32_t b) {
    return (a == UNKNOWN || a > b)? b : a;
}

node_t nextNode(node_t current) {
    node_t next = current;
    int32_t minDis = UNKNOWN;

    for(int i=0; i<NODENUM; i+=1) {
        int32_t dis = getDistance(current, i);

        if(dis > 0) {
            if(getMarkedDistance(current, counter-1) + dis == min(getMarkedDistance(i, counter), getMarkedDistance(current, counter-1) + dis)) {
                setMarkedDistance(i, getMarkedDistance(current, counter-1) + dis);
                pred[i] = current;
            }
            if(getMarkedDistance(i, counter)>0 && getMarkedDistance(i, counter) == min(minDis, getMarkedDistance(i, counter)) && getCheckedNode(i, counter) == 0) {
                minDis = getMarkedDistance(i, counter);
            }
        }
        if(dis == 0) {
            if(getMarkedDistance(i, counter) == UNKNOWN)
                markTable[i][counter*2] = 0;
            if(getMarkedDistance(i, counter)>0 && getMarkedDistance(i, counter) == min(minDis, getMarkedDistance(i, counter)) && getCheckedNode(i, counter) == 0)
                minDis = getMarkedDistance(i, counter);
        }
    }
    for(int i=0; i<NODENUM; i+=1) {
        if(getMarkedDistance(i, counter)>0 && getMarkedDistance(i, counter) == min(minDis, getMarkedDistance(i, counter)) && getCheckedNode(i, counter) == 0) {
            next = i;
        }
    }
    setNodeChecked(next);
    counter += 1;
    return next;
}

void printRouteMatrix() {
    int i=0, j=0;
    printf("Adjacency Matrix:\n");
    printf("  S ");
    for(i=1; i<NODENUM; i+=1) {
        if(i<NODENUM-1)
            printf("%d ", i);
        else
            printf("T");
    }
    printf("\n");

    for(i=0; i<NODENUM; i+=1) {
        if(i == 0)
            printf("S ");
        else if(i == NODENUM-1)
            printf("T ");
        else
            printf("%d ", i);
        for(j=0; j<NODENUM; j+=1) {
            printf("%d ", route[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printPath() {
    int i = NODENUM-1;
    printf("End <- ");
    while(pred[i]!=0) {
        printf("%d <- ", pred[i]);
        i = pred[i];
    }
    printf("Start\n");
}

int32_t getMinDistance() {
    return markTable[NODENUM-1][(NODENUM-1)*2];
}

int main() {
    node_t current = 0;
    node_t next = 0;

    printRouteMatrix();

    initMarkTable();
    setStartingPoint();
    
    while(counter < (uint32_t)NODENUM) {
        next = nextNode(current);
        current = next;
    }

    printf("The shortest Path is: ");
    printPath();
    printf("It's distance is: %d\n", getMinDistance());
    
    return 0;
}