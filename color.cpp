#include "color.h"

		Color::Color() {
			//3 values that set color of pixel 
			r = 0;
			g = 0;
			b = 0;
		};
		Color::Color(double rInput, double gInput, double bInput) {
			r = rInput;
			g = gInput;
			b = bInput;
		};
		double Color::getR() const {
			return r;
		};
		double Color::getG() const {
			return g;
		};
		double Color::getB() const {
			return b;
		};
		void Color::setR(double rInput) {
			r = rInput;
		};
		void Color::setG(double gInput) {
			g = gInput;
		};
		void Color::setB(double bInput) {
			b = bInput;
		};

