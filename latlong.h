#ifndef LATLONG_H
#define LATLONG_H

class LatLong
{
public:
    static int Getlinepixel(double lat, double lon, int *line, int *pixel);
    static int Getlatlon(double *dlat, double *dlon, int line, int pixel);
private:
    static int nint(double val);
    static int pixcoord2geocoord(int column, int row, int coff, int loff, double *latitude, double *longitude);
    static int geocoord2pixcoord(double latitude, double longitude, int coff, int loff, int *column, int *row);
};

#endif // LATLONG_H
