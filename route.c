#include <stdio.h>
#include <stdint.h>

/* Total node number in route map */
#define NODENUM 7

/* Node that has reached flag in markTable */
#define CHECKED 1

/* Define route type */
#define UNREACHABLE 0
#define UNKNOWN -1

typedef uint32_t node_t;

node_t node = 0;
const int32_t route[NODENUM][NODENUM] = {
    {0, 3, 2, 0, 0, 0, 0},
    {0, 0 ,0, 2, 0, 0, 0},
    {0, 0, 0, 3, 0, 0, 0},
    {0, 0, 0, 0, 3, 2, 0},
    {0, 0, 0, 0, 0, 0, 3},
    {0, 0, 0, 0, 0, 0, 6},
    {0, 0, 0, 0, 0, 0, 0}
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
    printf("*");
    for(int i=0; i<NODENUM; i+=1) {
        for(int j=0; j<NODENUM*2; j+=1) {
            printf("%d ", markTable[i][j]);
        }
        printf("\n");
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
            setMarkedDistance(i, min(getMarkedDistance(i, counter), getMarkedDistance(current, counter-1) + dis));
            if(getMarkedDistance(i, counter)>0 && getMarkedDistance(i, counter) == min(minDis, getMarkedDistance(i, counter)) && getCheckedNode(i, counter) == 0) {
                minDis = getMarkedDistance(i, counter);
            }
            pred[i] = current;
        }
        if(dis == 0) {
            if(getMarkedDistance(i, counter) == UNKNOWN)
                markTable[i][counter*2] = 0;
            if(getMarkedDistance(i, counter)>0 && getMarkedDistance(i, counter) == min(minDis, getMarkedDistance(i, counter)) && getCheckedNode(i, counter) == 0)
                minDis = getMarkedDistance(i, counter);
        }
        printf("counter %d i %d minDis %d dis %d\n", counter, i, minDis, dis);
        printMarkTable();
    }
    for(int i=0; i<NODENUM; i+=1) {
        if(getMarkedDistance(i, counter)>0 && getMarkedDistance(i, counter) == min(minDis, getMarkedDistance(i, counter)) && getCheckedNode(i, counter) == 0) {
            next = i;
        }
    }
    setNodeChecked(next);
    counter += 1;
    printMarkTable();
    return next;
}

int32_t getMinDistance() {
    return markTable[NODENUM-1][(NODENUM-1)*2];
}

void printRoute() {
    int i = NODENUM-1;
    printf("%d<-", (uint32_t)NODENUM);
    while(pred[i]!=0) {
        printf("%d<-", pred[i]);
        i = pred[i];
    }
    printf("0\n");
}

int main() {
    node_t current = 0;
    node_t next = 0;

    initMarkTable();
    setStartingPoint();
    
    while(counter < (uint32_t)NODENUM) {
        next = nextNode(current);
        printf("Next: %d\n\n", next);
        current = next;
    }

    printf("The shortest Path is: ");
    printRoute();
    printf("It's distance is: %d\n", getMinDistance());
    
    return 0;
}