//
// Created by kugimasa on 2019-08-14.
//
#include <iostream>
#include <fstream>
#include "float.h"
#include "../sphere.h"
#include "../hitable_list.h"
#include "../camera.h"
#include "../material.h"


using namespace std;

vec3 color(const ray& r, hitable *world, int depth) {
    hit_record rec;
    if(world->hit(r, 0.001, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attenuation;
        ///recursive
        if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)){
            return attenuation*color(scattered, world, depth+1);
        }else{
            return vec3(0, 0, 0);
        }
    }
        ///Drawing blue sky
    else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
}

vec3 tapioca_position(){
    vec3 p;
    p = vec3(2.0-4.0*drand48(), 1.5 - 3.0*drand48(), -10*drand48());
    return p;
}

int main() {
    int nx = 800;
    int ny = 400;
    int ns = 100;
    ofstream outputfile("tapioca.ppm");
    outputfile << "P3\n" << nx << " " << ny << " " << "255\n";
    ///list of sphere objects

    int n = 100;
    hitable *list[n+1];
    list[0] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.4, 0.0)));
    for(int i = 1; i <= n; i++){
        list[i] = new sphere(tapioca_position(), 0.2, new metal(vec3(0.1, 0.1, 0.1), 1.0));
    }
    hitable *world = new hitable_list(list, n+1);
    camera cam;
    for(int j = ny-1; j >= 0; j--){
        for(int i = 0; i < nx; i++){
            vec3 col(0, 0, 0);
            for(int s = 0; s < ns; s++) {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                ray r = cam.get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world, 0);
            }
            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            outputfile << ir << " " << ig << " " << ib << "\n";
        }
    }
}

