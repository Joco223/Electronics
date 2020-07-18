#include "chunk.h"

chunk::chunk() : pos_x(0), pos_y(0), size(0) {}

chunk::chunk(const int pos_x_, const int pos_y_, const int size_)
		 : pos_x(pos_x_), pos_y(pos_y_), size(size_) {}