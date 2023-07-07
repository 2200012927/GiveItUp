#ifndef MACRO_H
#define MACRO_H

#define WID 800
#define HEI 450

struct stock{
    int type;
    int height;

    stock() {}
    stock(int t, int h): type(t), height(h) {}

    int revSpurHeight;
};

#endif // MACRO_H
