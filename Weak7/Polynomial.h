#ifndef WEAK7_POLYNOMIAL_H
#define WEAK7_POLYNOMIAL_H

typedef struct polyNode *polyPointer;

struct polyNode {
    float coef;
    int expon;
    polyPointer link;
};

polyPointer cpadd(polyPointer a, polyPointer b);

void attach(float coefficient, int exponent, polyPointer *rear);

void cerase(polyPointer *ptr);

polyPointer getNode(void);

void retNode(polyPointer ptr);

void print_polynomial(polyPointer C);

polyPointer single_cpmul(polyNode Ai, polyPointer B);

polyPointer cpmul(polyPointer A, polyPointer B);

void lsot(polyPointer *rear);

polyPointer create_polynomial();

int compare(int aExpon, int bExpon);

#endif //WEAK7_POLYNOMIAL_H
