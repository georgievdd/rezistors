#pragma once
class vec {
private:

public:
    long double x = 0;
    long double y = 0;
    long double z = 0;

    vec() {}

    vec(long double x, long double y, long double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    vec operator+(vec obj) {
        return vec(this->x + obj.x, this->y + obj.y, this->z + obj.z);
    }

    vec operator+(long double k) {
        return vec(this->x + k, this->y + k, this->z + k);
    }

    void operator+=(vec obj) {
        x += obj.x;
        y += obj.y;
        x += obj.z;
    }

    vec operator-(vec obj) {
        return vec(x - obj.x, y - obj.y, z - obj.z);
    }

    vec operator/(long double c) {
        return vec(x / c, y / c, z / c);
    }

    void operator/= (long double c) {
        x /= c;
        y /= c;
        z /= c;
    }

    vec operator*(long double c) {
        return vec(x * c, y * c, z * c);
    }

    void operator=(vec obj) {
        x = obj.x;
        y = obj.y;
        z = obj.z;
    }

    vec operator&(vec v) {
        return vec(v.z * y - v.y * z, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    vec VECT(vec v) {
        return vec(v.z * y - v.y * z, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    void print() {
        cout << x << " " << y << " " << z << endl;
    }

    float length() {
        return sqrt(x * x + y * y + z * z);
    }

    float cos_a(vec v) {
        return (x * v.x + y * v.y + z * v.z) / (sqrt(x * x + y * y + z * z) * v.length());
    }

    vec X(long double x) {
        return vec(x, y, z);
    }

    vec Y(long double y) {
        return vec(x, y, z);
    }
    vec Z(long double z) {
        return vec(x, y, z);
    }
};