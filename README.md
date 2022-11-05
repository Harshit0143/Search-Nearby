# Search-Nearby
Answering 2-Dimensional Range Queries <br/>


# ℓ∞ distance between 2 points 
ℓ∞-distance ***p1 = (x1, y1)*** and ***p2 = (x2, y2)***, denoted by ***||p1 − p2||∞***, is defined as
***max(|x1 − x2|, |y1 − y2|)***. <br/>
# Specifications
* Given a list ***S*** (called pointlist)  of ***n*** points in the Cartesian Plane of the form ***(x,y)*** {We take ***x,y*** Integers to avoid floating point error}<br/>
* A query point ***q*** <br/>
* non-negative number ***d****<br/>
# Goal

* To find the set ***{p ∈ S | ||p − q||∞ ≤ d}*** , the set of all points in ***S*** that are at most an
***ℓ∞-distance d*** away from the point q.<br/>

# Implementation
* ***n*** is the size of the pointlist<br/>
* Create a Data Structure ***PointDatabase*** , to store a set of data points.<br/>
* This construciton is done in ***O(nlog(n))*** time<br/>

*  An algorithm which, given the above ***Data Structure*** constructed, a query point ***q***, and a distance ***d***,
outputs the set<br/> ***{p ∈ S | ∥p − q∥∞ ≤ d}*** .<br/>
* See code for more implementation details

***searchNearby(self, q, d)***: <br/>
list of all points, in the set that self represents, that are at ***ℓ∞-distance*** at most ***d*** from ***q***.<br/>
Runs in time ***O(m + (log(n))^2) )*** time where m is the number of points returned.<br/>




# Example Test Cases
pointDbObject = PointDatabase([(1,6), (2,4), (3,7), (4,9), (5,1), (6,3), (7,8), (8,10),(9,2), (10,5)]) <br/><br/>
pointDbObject.searchNearby((5,5), 1)<br/>
[]<br/><br/>
pointDbObject.searchNearby((4,8), 2)<br/>
[(3,7), (4,9)]<br/><br/>
pointDbObject.searchNearby((10,2), 1.5)<br/>
[(9,2)]
