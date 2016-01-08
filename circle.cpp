#include <cmath>     
#include "color.h"
#include "circle.h"

		Circle::Circle(){
			xPos = 0;
			yPos = 0;
			radius = 0;
			Color circleColor();
		};
		Circle::Circle(double xPosInput, double yPosInput, double radiusInput, Color circleColorInput){
			xPos = xPosInput;
			yPos = yPosInput;
			radius = radiusInput;
			Color circleColor(circleColorInput.getR(), circleColorInput.getG(), circleColorInput.getB());			
		};
		double Circle::getXPos() const {
			return xPos;
		};
		double Circle::getYPos() const {
			return yPos;
		};
		Color Circle::getColor() const {
			return circleColor;
		};
		double Circle::getRadius() const {
			return radius;
		};
		void Circle::setXPos(double xPosInput) { 
			xPos = xPosInput;
		};
		void Circle::setYPos(double yPosInput) { 
			yPos = yPosInput;
		};
		void Circle::setColor(Color circleColorInput) { 
			circleColor.setR(circleColorInput.getR());
			circleColor.setG(circleColorInput.getG());
			circleColor.setB(circleColorInput.getB());
		};
		void Circle::setRadius(double radiusInput) {
			radius = radiusInput;
		};
		void Circle::translate(double dx, double dy) { 
			xPos += dx;
			yPos += dy;
		};
		bool Circle::isWithinRadius(double xPosInput, double yPosInput) {
			double x = (xPos-xPosInput);
			double y = (yPos-yPosInput);
			return (sqrt(x*x + y*y) <= radius);
    };
