/* Standard template for all kind of interval merge problems.
 * Core idea is to have a current interval and keep adjusting it
 * as you encounter different intervals while walking left to right.
 *
 * Author : Manish Katiyar <mkatiyar@gmail.com>
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Interval {
public:
	int start, end;
};

bool mycomp(Interval& A, Interval& B) {
    if (A.start == B.start) return A.end < B.end;
    return A.start < B.start;
}

/* Given a set of balloons where each balloon is represented
 * as diameters in interval form [x1, x2], find the minimum number
 * of arrows required to burst all balloons. Arrows are shot vertically.
 */
int findMinArrowShots(vector<Interval>& points) {
        if (points.size() == 0) return 0;

        sort(points.begin(), points.end(), mycomp);

        Interval current = points[0];
        int count = 0;

        for (int i = 0; i < points.size(); i++) {
            if (points[i].start > current.end) {
                count++;
                current = points[i];
            } else {
                current.end = min(current.end, points[i].end);
                current.start = max(current.start, points[i].start);
            }
        }
        return count + 1;
}

/* Given a set of intervals, merge overlapping ones and return
 * the result
 */
vector<Interval> merge_intervals(vector<Interval>& intervals) {

	vector <Interval> result;

	if (intervals.size() == 0) return result;
	sort(intervals.begin(), intervals.end(), mycomp);
	Interval current = intervals[0];

	for (auto x : intervals) {
		if (x.start <= current.end) {
			current.end = max(x.end, current.end);
		} else {
			result.emplace_back(current);
			current = x;
		}
	}
	result.emplace_back(current);
	return result;
}

/* Given a set of intervals, insert a new interval in between */
vector<Interval> insert_interval(vector<Interval>& intervals, Interval newInterval)
{
	bool merged = false;
	vector <Interval> result;

	for (auto i : intervals) {
		if (i.end < newInterval.start || i.start > newInterval.end) {
			if (!merged && i.start > newInterval.end) {
				result.emplace_back(newInterval);
				merged = true;
			}
			result.emplace_back(i);
		} else {
			newInterval.start = min(i.start, newInterval.start);
			newInterval.end = max(i.end, newInterval.end);
		}
	}

	if (!merged) {
		result.emplace_back(newInterval);
	}

	return result;
}

void generate_balloons(vector <Interval>& input, int n)
{
	Interval I;
	for (int i = 0; i < n; i++) {
		I.start = random() % (2 * n);
		I.end = I.start + random() % n;
		input.emplace_back(I);
	}
}

void print_vector(vector <Interval> I)
{
	printf("{");
	for (auto i : I) {
		printf("[%d - %d] ", i.start, i.end);
	}
	printf("}\n");
}
int main()
{
	int n;
	cout << "Enter the number of balloons : ";
	cin >> n;

	srand(time(NULL));

	vector <Interval> B;
	generate_balloons(B, n);
	sort(B.begin(), B.end(), mycomp);

	printf("Balloons : ");
	print_vector(B);

	printf("Minimum arrows needed = %d\n",
			findMinArrowShots(B));

	printf("Merged intervals :\n");
	print_vector(merge_intervals(B));

	Interval I;
	I.start = random() % (2 * n);
	I.end = I.start + random() % n;
	printf("Inserting interval [%d - %d] in between :\n", I.start, I.end);
	print_vector(insert_interval(B, I));

	return 0;
}
