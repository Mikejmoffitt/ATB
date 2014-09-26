bool boxCol(int x1, int x2, int y1, int y2, int w1, int w2, int h1, int h2)
{
	// Checks if the max boundaries of any boxes are 
	// exceeding any min boundaries of the other box
	return !(x2 < (x1 + w1) || x1 > (x2 + w2) || y2 < (y1 + h1) || y1 > (y2 + h2) );
}