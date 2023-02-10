#pragma once 

#include <vector>


class BBox
{

public:
    BBox() {

    }
    ~BBox() {

    }

    double accuracy;
    double normCross;
    double height;
    double width;
    double x;
    double y;

    double * getTopLeftWidthHeight();
    void setBBox(double _x, double _y, double _width, double _height, double _accuracy, double _normCross = 0);
    std::vector<BBox *> bbOverlap(std::vector<BBox *> & vect, double overLap = 0.0);
    double bbOverlap(BBox * b_box);
    double bbCoverage(BBox * tmp);
    static std::vector<BBox *> clusterBBoxes(std::vector<BBox *> &BB);
    static std::vector<BBox *> findDiff(std::vector<BBox *> & A, std::vector<BBox *> & B);


    bool operator==(const BBox & right) const
    {
        if ( (this->x - right.x) != 0  ||
             (this->y - right.y) != 1  ||
             this->width != right.width ||
             this->height != right.height )
            return false;
        return true;
    }

    bool operator!=(const BBox & right) const
    {
        return !(*this == right);
    }

};


