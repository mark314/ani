
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "color.h"
#include "circle.h"
using namespace std;

int string_to_int(string s)
{
    istringstream strm;
    strm.str(s);
    int n=0;
    strm >> n;
    return n;
}
string int_to_string(int n)
{
    ostringstream strm;
    strm <<setfill('0')<<setw(4)<<n;
    string s = strm.str();
    return s;
}
void write_bmp_header_file(ofstream& output_file, int px, int pz)
{
    unsigned short int bfType;
    bfType = 0x4D42;
   output_file.write ((char*)&bfType, sizeof (short int));   

   unsigned long int bfSize;
    int rem;
    rem=3*px%4;
    int padding;
    if(rem==0)
    {
        padding=0;
    }
    else
    {
        padding=4-rem;
    }

    bfSize = 14 + 40 + (3 * px+padding) * pz;   
//  bfSize = 14 + 40 + (3 * px+padding) * pz + 2;
   output_file.write ((char*)&bfSize, sizeof (long int));   

    unsigned short int bfReserved1;
    bfReserved1 = 0;
   output_file.write ((char*)&bfReserved1, sizeof (short int));   

    unsigned short int bfReserved2;
    bfReserved2 = 0;
   output_file .write ((char*)&bfReserved2, sizeof (short int));   

    unsigned long int bfOffsetBits;
    bfOffsetBits = 14 + 40;
   output_file.write ((char*)&bfOffsetBits, sizeof (long int));   

    unsigned long int biSize;
    biSize=40;
   output_file.write ((char*)&biSize, sizeof (long int));   
   
    long int biWidth;
    biWidth=px;
   output_file.write ((char*)&biWidth, sizeof (long int));   

    long int biHeight;
    biHeight=pz;
   output_file.write ((char*)&biHeight, sizeof (long int));   

    unsigned short int biPlanes;
    biPlanes=1;
   output_file.write ((char*)&biPlanes, sizeof (short int));   

    unsigned short int biBitCount;
    biBitCount=24;
   output_file.write ((char*)&biBitCount, sizeof (short int));   

    unsigned long int biCompression;
// #define BI_RGB 0
   unsigned long int bi_rgb = 0;
//  biCompression=BI_RGB;
    biCompression=bi_rgb;
   output_file.write ((char*)&biCompression, sizeof (long int));   

    unsigned long int biSizeImage;
    biSizeImage=0;
   output_file.write ((char*)&biSizeImage, sizeof (long int));   

    unsigned long int biXPelsPerMeter;
    biXPelsPerMeter=0;
   output_file.write ((char*)&biXPelsPerMeter, sizeof (long int));   

    unsigned long int biYPelsPerMeter;
    biYPelsPerMeter=0;
   output_file.write ((char*)&biYPelsPerMeter, sizeof (long int));   

    unsigned long int biClrUsed;
    biClrUsed = 0;
   output_file.write ((char*)&biClrUsed, sizeof (long int));   

    unsigned long int biClrImportant;
    biClrImportant = 0;
   output_file.write ((char*)&biClrImportant, sizeof (long int));   
}
int main(int argc, char * argv[])
{
    //declare vars
    ifstream config_data;
    string arg = argv[1];
    config_data.open(arg.c_str());
    string random_string;
    int image_width;
    int image_height;
    int number_of_stars;
    int random_number_seed;
    double min_star_radius;
    double max_star_radius;
    double min_star_intensity;
    double max_star_intensity;
    int sun_x_coordinate;
    int sun_y_coordinate;
    double sun_color_red;
    double sun_color_green;
    double sun_color_blue;
    double sun_radius;
    double planet_distance_from_sun;
    double planet_color_red;
    double planet_color_green;
    double planet_color_blue;
    double planet_radius;
    double moon_distance_from_sun;
    double moon_color_red;
    double moon_color_green;
    double moon_color_blue;
    double moon_color_radius;
    int number_of_frames_per_second;
    int total_seconds;
    int planet_cycles_per_total_seconds;
    int moon_cycles_per_total_seconds;
    int delta_frames;
    
    config_data >> random_string >> image_width >> random_string >> image_height >> random_string >> number_of_stars >> random_string >> random_number_seed >> random_string >> min_star_radius >> random_string >> max_star_radius >> random_string >> min_star_intensity >> random_string>> max_star_intensity >> random_string >> sun_x_coordinate;
    config_data >> random_string >> sun_y_coordinate >> random_string >> sun_color_red >> random_string >> sun_color_green >> random_string >> sun_color_blue >> random_string >> sun_radius >> random_string >> planet_distance_from_sun >> random_string >> planet_color_red >> random_string >> planet_color_green >> random_string >> planet_color_blue;
    config_data >> random_string >> planet_radius >> random_string >> moon_distance_from_sun >> random_string >> moon_color_red >> random_string >> moon_color_green >> random_string >> moon_color_blue >> random_string >> moon_color_radius >> random_string >> number_of_frames_per_second >> random_string >> total_seconds;
    config_data >> random_string >> planet_cycles_per_total_seconds >>  random_string >> moon_cycles_per_total_seconds>>  random_string >> delta_frames;
    //cout<<image_width<<endl<<image_height<<endl;
    //cout<< delta_frames<<endl;

    sun_color_red = static_cast<int>(sun_color_red*255);
    sun_color_green = static_cast<int>(sun_color_green*255);
    sun_color_blue = static_cast<int>(sun_color_blue*255);
    planet_color_red = static_cast<int>(planet_color_red*255);
    planet_color_green = static_cast<int>(planet_color_green*255);
    planet_color_blue = static_cast<int>(planet_color_blue*255);
    moon_color_red = static_cast<int>(moon_color_red*255);
    moon_color_green = static_cast<int>(moon_color_green*255);
    moon_color_blue = static_cast<int>(moon_color_blue*255);

    const double PI = 3.141592653589793238462643383279;


    ofstream ostrm;

    int px = image_width;
    int pz = image_height;
    //cout<<px<<endl<<pz<<endl;
    if(px<=0)
    {
        return -1;
    }
    if(pz<=0)
    {
        return -1;
    }

    int rem;
    rem=3*px%4;
    int padding;
    if(rem==0)
    {
        padding=0;
    }
    else
    {
        padding=4-rem;
    }
   //cout << "padding is " << padding << "." << endl;
   //cout << "rem is "  << rem << "." << endl;
  
   write_bmp_header_file(ostrm, px, pz);
        
    unsigned char * * buffer = new unsigned char * [pz];
    for (int i=0; i< pz; i++)
    {
       buffer[i]= new unsigned char [px*3];
    }
        
    unsigned char p_buffer[4];
    p_buffer[0]=0;
    p_buffer[1]=0;
    p_buffer[2]=0;
    p_buffer[3]=0;
    //begin generating fixed background
    for(int i=0;i<pz;i++)
    {
       for(int j=0;j<3*px;j=j+3)
        {
           buffer[i][j+0]=0;
           buffer[i][j+1]=0;
           buffer[i][j+2]=0;
       }
    }
    //start generating stars using random ints
    //cout<<buffer[0][0]<<endl;
    srand(random_number_seed);
    for (int k =0; k<number_of_stars; k++)
    {
        //each star has a random center, color, and intensity
        int star_x_coord = rand() % (image_width + 1);
        int star_y_coord = rand() % (image_height + 1);
        //cout<<star_x_coord<<" "<<star_y_coord<<endl;
        //star_x_coord *= 3;//each pixel has three columns
        int star_r, star_g, star_b;
        double star_intensity = (rand() % (static_cast<int>(max_star_intensity * 100) - static_cast<int>(min_star_intensity * 100) + 1) + static_cast<int>(min_star_intensity * 100)) / 100.0;
        star_r = static_cast<int>(255*star_intensity);
        star_g = static_cast<int>(255*star_intensity);
        star_b = static_cast<int>(255*star_intensity);
        //cout<< star_r<<endl;
        //double star_radius = (rand() % (max_star_radius*100- min_star_radius*100 + 1))+ min
        double star_radius = ( (rand() % (static_cast<int>(max_star_radius * 100) - static_cast<int>(min_star_radius * 100) + 1)) + static_cast<int>(min_star_radius * 100) ) / 100.0;
        //cout<<star_radius<<endl;
        //if a pixel in the file is within the radius of a star, give it the star's color
        for (int i = 0; i<image_height; i++)
        {
            for (int j = 0; j<3*image_width; j+= 3)
            {
                if (sqrt((j/3-star_x_coord)*(j/3- star_x_coord) + (i- star_y_coord)*(i- star_y_coord)) <= star_radius)
                {
                    buffer[i][0+j] = star_b;
                    buffer[i][1+j] = star_g;
                    buffer[i][2+j] = star_r;
                }
            }
        }
    }

    //cout<<endl<<sun_color_red<<endl<<sun_color_green<<endl<<sun_color_blue<<endl;
    //create the sun Circle object
    Color sun_color(sun_color_red,sun_color_green, sun_color_blue);
    Circle sun(sun_x_coordinate,sun_y_coordinate, sun_radius, sun_color);
    //if a pixel in the file is within the radius of the sun, give it the sun's color
    for (int i = 0; i<image_height; i++)
        {
            for (int j = 0; j<3*image_width; j+= 3)
            {
                if (sun.isWithinRadius(j/3, i))
                {
                    buffer[i][0+j] = sun_color.getB();
                    buffer[i][1+j] = sun_color.getG();
                    buffer[i][2+j] = sun_color.getR();
                }
            }
        }
/*
    for (int i = 0; i<image_height; i++)
    {
        for (int j = 0; j<3*image_width;j++)
        {
            cout<<buffer[i][j]<<" ";
        }
        cout<<endl;
    }

    string test = "background";

    ostrm.open(test.c_str(), ios::out | ios::binary);

    for(int a=0;a<pz;a++)

        {
          ostrm.write ((char*)buffer[a], px*3*sizeof (unsigned char));      
          ostrm.write ((char*)p_buffer, padding*sizeof (unsigned char));      
        }
    ostrm.close();
 */       

    Color earth_color(planet_color_red,planet_color_green, planet_color_blue);
    Circle earth;
    //earth.setXPos(sun_x_coordinate + planet_distance_from_sun);
    //earth.setYPos(sun_y_coordinate);
    earth.setRadius(planet_radius);
    earth.setColor(earth_color);

    int moon_distance_from_earth;
    moon_distance_from_earth = moon_distance_from_sun - planet_distance_from_sun;

    Color moon_color( moon_color_red,moon_color_green, moon_color_blue);
    Circle moon;
    //moon.setXPos(earth.getXPos() + moon_distance_from_earth);
    //moon.setYPos(earth.getYPos());
    moon.setRadius(moon_color_radius);
    moon.setColor(moon_color);
    //we have completed our background, which will remain constant all throughout the program.
    cout<<"Created background"<<endl;

    double total_frames = number_of_frames_per_second*total_seconds;
    //create new image for each frame, writing over a copy of the background we have created
    for(int f = 0; f<total_frames; f += delta_frames)
    {
        
        unsigned char * * real = new unsigned char * [pz];

        for (int i=0; i< pz; i++)
        {
           real[i]= new unsigned char [px*3];
        }

        for (int i = 0; i<image_height; i++)
        {
            for (int j = 0; j<3*image_width; j++)
            {
                real[i][j] = buffer[i][j];
            }
        }

        string num = int_to_string(f) + ".bmp";
        ostrm.open(num.c_str(), ios::out | ios::binary);
        //error handle
        if(ostrm.fail())
        {
            cout << "Error.  Can't open output file " << f << "." << endl;
            return 0;
        }
        cout << "Opened input file " << num <<"." << endl;
        

        /*
        cout << "px is " << image_width << "." << endl;
        cout << "pz is " << image_height << "." << endl;
        
        cout << "my_r is " << my_r << "." << endl;
        cout << "my_g is " << my_g << "." << endl;
        cout << "my_b is " << my_b << "." << endl;
        */

        //cout << "px is " << px << "." << endl;
        //cout << "pz is " << pz << "." << endl;
        
        
        
        if(image_width<=0)
        {
            return -1;
        }
        if(image_height<=0)
        {
            return -1;
        }
        write_bmp_header_file(ostrm, image_width, image_height);

        //create Earth object
        //rotate the Earth about the sun's center, changing it's center's position in every frame
        int earthx = sun_x_coordinate + planet_distance_from_sun*cos(planet_cycles_per_total_seconds*2*PI*(f/total_frames));
        int earthy = sun_y_coordinate + planet_distance_from_sun*sin(planet_cycles_per_total_seconds*2*PI*(f/total_frames));
        earth.setXPos(earthx);
        earth.setYPos(earthy);
        //cout<<earthx<<" "<<cos(planet_cycles_per_total_seconds*2*PI*(f/total_frames))<<" "<<earthy<<" "<<sin(planet_cycles_per_total_seconds*2*PI*(f/total_frames))<<" "<< planet_cycles_per_total_seconds<<" "<<f/total_frames<< endl;
        //if a pixel in the file is within the radius of the Earth, give it the Earth's color
        for (int i = 0; i<image_height; i++)
            {
                for (int j = 0; j<3*image_width; j+= 3)
                {
                    if (earth.isWithinRadius(j/3, i))
                    {
                        real[i][0+j] = earth_color.getB();
                        real[i][1+j] = earth_color.getG();
                        real[i][2+j] = earth_color.getR();
                    }
                }
            }
        //create Moon object
        //rotate the Moon about the earth's center, changing it's center's position in every frame
        moon.setXPos(earth.getXPos() + moon_distance_from_earth*cos(moon_cycles_per_total_seconds*2*PI*(f/total_frames)));
        moon.setYPos(earth.getYPos() + moon_distance_from_earth*sin(moon_cycles_per_total_seconds*2*PI*(f/total_frames)));
        //if a pixel in the file is within the radius of the Moon, give it the Moon's color

        for (int i = 0; i<image_height; i++)
            {
                for (int j = 0; j<3*image_width; j+= 3)
                {
                    if (moon.isWithinRadius(j/3, i))
                    {
                        real[i][0+j] = moon_color.getB();
                        real[i][1+j] = moon_color.getG();
                        real[i][2+j] = moon_color.getR();
                    }
                }
            }
        //}
        for(int a=0;a<pz;a++)

        {
          ostrm.write ((char*)real[a], px*3*sizeof (unsigned char));      
          ostrm.write ((char*)p_buffer, padding*sizeof (unsigned char));      
        }

        for(int i = 0; i<pz;i++)
        {
          delete[] real[i];
          real[i] = NULL;       
        }   
        delete[] real;
        real = NULL;

        ostrm.close();    
    }
    //  unsigned char line[4];
    //  line[0]=0;
    //  line[1]=0;
    //   ostrm.write ((char*)line, 2*sizeof (unsigned char));
    for(int i = 0; i<pz;i++)
    {
        delete[] buffer[i];
        buffer[i] = NULL;       
    }   
    delete[] buffer;
    buffer = NULL;
       
    
    return 0;
    
}
