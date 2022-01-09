#ifndef MATTRESS_H
#define MATTRESS_H

#include <cstdio>

#define MATTRESS_MAX_AXIS_SIZE 0xff
typedef unsigned long size_t;

class Mattress {

private:
  double v[MATTRESS_MAX_AXIS_SIZE][MATTRESS_MAX_AXIS_SIZE];
  size_t r, c;

public:
  struct random_conf {
    double min = -1, max = 1;
  };
  struct normal_conf {
    double mean = 0, std = 1;
  };
  struct to_string_conf {
    const char *fmt = "%lf", *sep = "\t", *newl = "\n";
  };

  Mattress();
  Mattress(size_t row, size_t column);
  Mattress(double value[], size_t row, size_t column);
  static Mattress zero(size_t row, size_t column);
  static Mattress eye(size_t row);
  static Mattress random(size_t row, size_t column, random_conf conf);
  static Mattress normal(size_t row, size_t column, normal_conf conf);
  Mattress copy();
  void copy(Mattress &a);
  void set_zero();
  void set_eye();
  void set_random(random_conf conf);
  void set_normal(normal_conf conf);

  double *at(size_t x);
  double at(size_t x, size_t y);
  void set(double value, size_t x, size_t y);
  void print(FILE *fp, to_string_conf conf);

  size_t get_row();
  size_t get_column();
  void set_row(size_t row);
  void set_column(size_t column);
  void resize(size_t row, size_t column);

  static Mattress neg(Mattress &a);
  static Mattress add(Mattress &a, Mattress &b);
  static Mattress sub(Mattress &a, Mattress &b);
  static Mattress mul(Mattress &a, double b);
  static Mattress mul(Mattress &a, Mattress &b);
  static Mattress transpose(Mattress &a);
  static Mattress kronecker(Mattress &a, Mattress &b);

  Mattress neg();
  Mattress add(Mattress &a);
  Mattress sub(Mattress &a);
  Mattress mul(double a);
  Mattress mul(Mattress &a);
  Mattress transpose();
  Mattress kronecker(Mattress &a);

  Mattress operator-();
  Mattress operator+(Mattress &a);
  Mattress operator-(Mattress &a);
  Mattress operator*(double a);
  Mattress operator*(Mattress &a);
  Mattress operator~();
  Mattress operator^(Mattress &a);
  double *operator[](size_t x);
};

#endif
