//
// Created by kugimasa on 2019/07/07.
//
#include <iostream>
#include <vec3.h>
//file out puter
#include <fstream>

using namespace std;


int main()
{
    int nx = 200;
    int ny = 100;

    ofstream outputfile("Images/sample.ppm");

    outputfile << "P3\n" << nx << " " << ny << "\n255\n";
    for(int j = ny - 1; j >= 0; j--)
    {
        for(int i = 0; i < nx; i++)
        {
            vec3 col(float(i)/float(nx), float(j)/float(ny), 0.2);
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            outputfile <<  ir << " " << ig << " " << ib << "\n";
        }
    }
    outputfile.close();
}
