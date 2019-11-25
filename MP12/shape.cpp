#include "shape.hpp"
//This mp is to implement several functions to get the max volume
//and max area among several shapes. In order to achevive that, we would
//like to use inheritance, multiphorism to implement the member funtions.

//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable
Shape::Shape(string name){
  name_=name;
}
string Shape::getName(){
  return name_;                     //set the constructors
}

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Rectangle::Rectangle(double width,double length):Shape("Rectangle"){
  width_=width;
  length_=length;
}
double Rectangle::getArea() const{
  return (width_*length_);
}
double Rectangle::getVolume() const{
  return 0.0;                                   //set the basic member functions
}
Rectangle Rectangle::operator +(const Rectangle& rec){
  Rectangle c(width_+rec.width_,length_+rec.length_);
  return c;                                     // define plus
}
Rectangle Rectangle::operator -(const Rectangle& rec){
  Rectangle c(max(0.0,width_-rec.width_),max(0.0,length_-rec.length_));
    return c;
}                                                //define minus

double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}


//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Circle::Circle(double radius):Shape("Circle"){
   radius_=radius;
}
double Circle::getArea() const{
  return (M_PI*radius_*radius_);
}
double Circle::getVolume() const{
  return 0.0;
}                                          //set the basic functions
Circle Circle::operator +(const Circle& cir){
  Circle c((radius_)+(cir.radius_));
  return c;                                  //define plus
}
Circle Circle::operator -(const Circle& cir){
  Circle c(max(0.0,(radius_)-(cir.radius_)));
  return c;
}                                          //define minus

double Circle::getRadius()const{return radius_;}

//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Sphere::Sphere(double radius):Shape("Sphere"){
   radius_=radius;
}
double Sphere::getArea() const{
  return(4*M_PI*radius_*radius_);
}
double Sphere::getVolume() const{
  return ((4.0/3.0)*M_PI*radius_*radius_*radius_);
}                                                      //set the basic funtions
Sphere Sphere::operator +(const Sphere& sph){
  Sphere c((radius_)+(sph.radius_));
  return c;                                          //define plus
}
Sphere Sphere::operator -(const Sphere& sph){
  Sphere c(max(0.0,(radius_)-(sph.radius_)));
  return c;                                            //define minus
}

double Sphere::getRadius()const{return radius_;}

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

RectPrism::RectPrism(double width,double length,double height):Shape("RectPrism"){
  width_=width;
  length_=length;
  height_=height;
}
double RectPrism::getArea() const{
  return (2*(width_*length_+width_*height_+length_*height_));
}
double RectPrism::getVolume() const{
  return (width_*height_*length_);                              //set the basic funtions
}
RectPrism RectPrism::operator +(const RectPrism& rectp){
  RectPrism c((width_)+(rectp.width_),(length_)+(rectp.length_),(height_)+(rectp.height_));
  return c;                                                 //define plus
}
RectPrism RectPrism::operator -(const RectPrism& rectp){
  RectPrism c(max(0.0,(width_)-(rectp.width_)),max(0.0,(length_)-(rectp.length_)),max(0.0,(height_)-(rectp.height_)));
    return c;
}
                                                       //define minus
double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}



// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
vector<Shape*> CreateShapes(char* file_name){
	//@@Insert your code here
  int num,i;
  ifstream ifs(file_name,std::ifstream::in);
  ifs>>num;
  std::vector<Shape*> array(num,NULL);
  for(i=0;i<num;i++){                                //use the for loop to check each condition
    string name;                                       // and load that value to appropriate
    ifs>>name;                                         //derived constructs and store them in order
    if(name=="Rectangle"){
      double width, length;
      ifs>>width>>length;
      array[i]=new Rectangle(width,length);
    }
    if(name=="Circle"){
      double radius;
      ifs>>radius;
      array[i]=new Circle(radius);
    }
    if(name=="Sphere"){
      double radius;
      ifs>>radius;
      array[i]=new Sphere(radius);
    }
    if(name=="RectPrism"){
      double width, length,height;
      ifs>>width>>length>>height;
      array[i]=new RectPrism(width,length,height);
  }
}
ifs.close();                          //close the file and return the vector pointer
return array; // please remeber to modify this line to return the correct value
}
// call getArea() of each object
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
int n=shapes.size();
int i;
for(i=0;i<n;i++){
  if(shapes[i]->getArea()>max_area){
    max_area=shapes[i]->getArea();                     //use the for loop every time meet a larger value
  }                                                   //just to modify the current value to it
}
	return max_area;
}


// call getVolume() of each object
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
  int n=shapes.size();
  int i;
  for(i=0;i<n;i++){                                      //use the for loop every time meet a larger value
    if(shapes[i]->getVolume()>max_volume){              ////just to modify the current value to i
      max_volume=shapes[i]->getVolume();
    }
  }

	return max_volume;
}
