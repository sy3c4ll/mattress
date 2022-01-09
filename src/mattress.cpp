#include "mattress.h"
#include <cstdio>
#include <memory.h>
#include <random>
#include <stdexcept>

#define MAX_STR_LEN 0x7f

Mattress::Mattress() : r(0), c(0) {}
Mattress::Mattress(size_t row, size_t column) : r(row), c(column) {}
Mattress::Mattress(double value[], size_t row, size_t column)
    : r(row), c(column) {
  for (size_t i = 0; i < r; i++)
    for (size_t j = 0; j < c; j++)
      v[i][j] = value[i * c + j];
}
Mattress Mattress::zero(size_t row, size_t column) {
  Mattress a(row, column);
  a.set_zero();
  return a;
}
Mattress Mattress::eye(size_t row) {
  Mattress a(row, row);
  a.set_eye();
  return a;
}
Mattress Mattress::random(size_t row, size_t column, random_conf conf) {
  Mattress a(row, column);
  a.set_random(conf);
  return a;
}
Mattress Mattress::normal(size_t row, size_t column, normal_conf conf) {
  Mattress a(row, column);
  a.set_normal(conf);
  return a;
}
Mattress Mattress::copy() {
  Mattress n(r, c);
  for (size_t i = 0; i < r; i++)
    memcpy(n.at(i), v[i], c);
  return n;
}
void Mattress::copy(Mattress &a) {
  r = a.get_row(), c = a.get_column();
  for (size_t i = 0; i < r; i++)
    memcpy(a.v[i], a.at(i), c);
}
void Mattress::set_zero() {
  for (size_t i = 0; i < r; i++)
    memset(v[i], 0, c * sizeof(double));
}
void Mattress::set_eye() {
  if (!(r == c))
    throw std::runtime_error("Invalid matrix dimensions");
  for (size_t i = 0; i < r; i++) {
    memset(v[i], 0, c * sizeof(double));
    v[i][i] = 1;
  }
}
void Mattress::set_random(random_conf conf) {
  std::mt19937 gen((std::random_device())());
  std::uniform_real_distribution<double> dis(conf.min, conf.max);
  for (size_t i = 0; i < r; i++)
    for (size_t j = 0; j < c; j++)
      v[i][j] = dis(gen);
}
void Mattress::set_normal(normal_conf conf) {
  std::mt19937 gen((std::random_device())());
  std::normal_distribution<double> dis(conf.mean, conf.std);
  for (size_t i = 0; i < r; i++)
    for (size_t j = 0; j < c; j++)
      v[i][j] = dis(gen);
}

double *Mattress::at(size_t x) {
  if (!(x < r))
    throw std::out_of_range("Index out of range");
  return v[x];
}
double Mattress::at(size_t x, size_t y) {
  if (!(x < r && y < c))
    throw std::out_of_range("Index out of range");
  return v[x][y];
}
void Mattress::print(FILE *fp, to_string_conf conf) {
  for (size_t i = 0; i < r; i++) {
    for (size_t j = 0; j < c; j++) {
      fprintf(fp, conf.fmt, v[i][j]);
      fprintf(fp, "%s", conf.sep);
    }
    fprintf(fp, "%s", conf.newl);
  }
}
void Mattress::set(double value, size_t x, size_t y) {
  if (!(x < r && y < c))
    throw std::out_of_range("Index out of range");
  v[x][y] = value;
}

size_t Mattress::get_row() { return r; }
size_t Mattress::get_column() { return c; }
void Mattress::set_row(size_t row) {
  for (size_t i = r; i < row; i++)
    memset(v[i], 0, c);
  r = row;
}
void Mattress::set_column(size_t column) {
  for (size_t i = 0; i < r; i++)
    memset(v[i] + c, 0, column - c);
  c = column;
}
void Mattress::resize(size_t row, size_t column) {
  set_row(row);
  set_column(column);
}

Mattress Mattress::neg(Mattress &a) {
  Mattress n(a.get_row(), a.get_column());
  for (size_t i = 0; i < a.get_row(); i++)
    for (size_t j = 0; j < a.get_column(); j++)
      n.set(-a.at(i, j), i, j);
  return n;
}
Mattress Mattress::add(Mattress &a, Mattress &b) {
  if (!(a.get_row() == b.get_row() && a.get_column() == b.get_column()))
    throw std::runtime_error("Invalid matrix dimensions");
  Mattress n(a.get_row(), a.get_column());
  for (size_t i = 0; i < a.get_row(); i++)
    for (size_t j = 0; j < a.get_column(); j++)
      n.set(a.at(i, j) + b.at(i, j), i, j);
  return n;
}
Mattress Mattress::sub(Mattress &a, Mattress &b) {
  if (!(a.get_row() == b.get_row() && a.get_column() == b.get_column()))
    throw std::runtime_error("Invalid matrix dimensions");
  Mattress n(a.get_row(), a.get_column());
  for (size_t i = 0; i < a.get_row(); i++)
    for (size_t j = 0; j < a.get_column(); j++)
      n.set(a.at(i, j) - b.at(i, j), i, j);
  return n;
}
Mattress Mattress::mul(Mattress &a, double b) {
  Mattress n(a.get_row(), a.get_column());
  for (size_t i = 0; i < a.get_row(); i++)
    for (size_t j = 0; j < a.get_column(); j++)
      n.set(a.at(i, j) * b, i, j);
  return n;
}
Mattress Mattress::mul(Mattress &a, Mattress &b) {
  if (!(a.get_column() == b.get_row()))
    throw std::runtime_error("Invalid matrix dimensions");
  Mattress n = Mattress::zero(a.get_row(), b.get_column());
  for (size_t i = 0; i < a.get_row(); i++)
    for (size_t j = 0; j < b.get_column(); j++)
      for (size_t k = 0; k < a.get_column(); k++)
        n.set(n.at(i, j) + a.at(i, k) * b.at(k, j), i, j);
  return n;
}
Mattress Mattress::transpose(Mattress &a) {
  Mattress n(a.get_column(), a.get_row());
  for (size_t i = 0; i < a.get_column(); i++)
    for (size_t j = 0; j < a.get_row(); j++)
      n.set(a.at(j, i), i, j);
  return n;
}
Mattress Mattress::kronecker(Mattress &a, Mattress &b) {
  Mattress n(a.get_row() * b.get_row(), a.get_column() * b.get_column());
  for (size_t ib = 0; ib < b.get_row(); ib++)
    for (size_t ia = 0; ia < a.get_row(); ia++)
      for (size_t jb = 0; jb < b.get_column(); jb++)
        for (size_t ja = 0; ja < a.get_column(); ja++)
          n.set(a.at(ia, ja) * b.at(ib, jb), ia * b.get_row() + ib,
                ja * b.get_column() + jb);
  return n;
}

Mattress Mattress::neg() { return Mattress::neg(*this); }
Mattress Mattress::add(Mattress &a) { return Mattress::add(*this, a); }
Mattress Mattress::sub(Mattress &a) { return Mattress::sub(*this, a); }
Mattress Mattress::mul(double a) { return Mattress::mul(*this, a); }
Mattress Mattress::mul(Mattress &a) { return Mattress::mul(*this, a); }
Mattress Mattress::transpose() { return Mattress::transpose(*this); }
Mattress Mattress::kronecker(Mattress &a) {
  return Mattress::kronecker(*this, a);
}

Mattress Mattress::operator-() { return Mattress::neg(*this); }
Mattress Mattress::operator+(Mattress &a) { return Mattress::add(*this, a); }
Mattress Mattress::operator-(Mattress &a) { return Mattress::sub(*this, a); }
Mattress Mattress::operator*(double a) { return Mattress::mul(*this, a); }
Mattress Mattress::operator*(Mattress &a) { return Mattress::mul(*this, a); }
Mattress Mattress::operator~() { return Mattress::transpose(*this); }
Mattress Mattress::operator^(Mattress &a) {
  return Mattress::kronecker(*this, a);
}
double *Mattress::operator[](size_t x) { return at(x); }
