# polygonRoundness
1. Read the data line by line from file (one line is a roundess element)
2. Create Point by data -> x and y coordinate pair
3. Calculate radius between point and origo (0,0)
4. Calculate and check the max/min/avarage value of radius
5. Calculate error of radius: abs((orig - calculate)/orig)*100 [%]
6. Check the value of error and the original radius value
7. Sort the roundness
8. Print the result in ascending order