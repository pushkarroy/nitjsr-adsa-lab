#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

Point points[1000], hull[1000];
int n;

int orientation(Point a, Point b, Point c) {
    int val = (b.y - a.y) * (c.x - b.x) -
              (b.x - a.x) * (c.y - b.y);
    if (val == 0) return 0;  // collinear
    return (val > 0) ? 1 : 2;
}

int distSq(Point a, Point b) {
    return (a.x - b.x)*(a.x - b.x) +
           (a.y - b.y)*(a.y - b.y);
}

Point p0;

// Compare function for qsort
int compare(const void *vp1, const void *vp2) {
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return distSq(p0, *p2) >= distSq(p0, *p1) ? -1 : 1;

    return (o == 2) ? -1 : 1;
}

void grahamScan() {
	int i;
    int ymin = points[0].y, min = 0;
    for ( i = 1; i < n; i++) {
        if ((points[i].y < ymin) ||
           (points[i].y == ymin && points[i].x < points[min].x)) {
            ymin = points[i].y;
            min = i;
        }
    }

    Point temp = points[0];
    points[0] = points[min];
    points[min] = temp;

    p0 = points[0];
    qsort(&points[1], n - 1, sizeof(Point), compare);

    int m = 1;
    for ( i = 1; i < n; i++) {
        while (i < n - 1 &&
               orientation(p0, points[i], points[i+1]) == 0)
            i++;

        points[m] = points[i];
        m++;
    }

    if (m < 3) {
        printf("Convex hull not possible.");
        return;
    }

    int top = 2;
    hull[0] = points[0];
    hull[1] = points[1];
    hull[2] = points[2];

    for ( i = 3; i < m; i++) {
        while (orientation(hull[top-1], hull[top], points[i]) != 2)
            top--;
        hull[++top] = points[i];
    }

    printf("Convex Hull points:\n");
    for ( i = 0; i <= top; i++)
        printf("(%d, %d)\n", hull[i].x, hull[i].y);
}

int main() {
    printf("Enter number of points: ");
    scanf("%d", &n);
int i;
    for ( i = 0; i < n; i++)
        scanf("%d %d", &points[i].x, &points[i].y);

    grahamScan();
    return 0;
}

