#include <iostream>
#include <map>
#include <ctime>


using namespace std;

long int dateToEpoch(int year, int month, int day, int hour = 0, int minute = 0, int second = 0) {
    tm time_in = {0, 0, 0, day, month - 1, year - 1900};
    return mktime(&time_in);
}


void extractEvents(map<long int, string>& events, long int startEpoch) {
    auto it = events.lower_bound(startEpoch);
    if (it == events.end()) {
        cout << "Key not found and no greater key in the map." << endl;
        return;
    }

    for (auto iter = it; iter != events.end(); ++iter) {
        cout << "Epoch Time: " << iter->first << ", Event: " << iter->second << endl;
    }
}

int main() {
    map<long int, string> events;
    events[dateToEpoch(2023, 1, 1)] = "New Year Event";
    events[dateToEpoch(2023, 2, 14)] = "Valentine's Day";
    events[dateToEpoch(2023, 3, 17)] = "St. Patrick's Day";
    events[dateToEpoch(2023, 7, 4)] = "Independence Day";
    events[dateToEpoch(2023, 10, 31)] = "Halloween";
    events[dateToEpoch(2023, 12, 25)] = "Christmas";


    long int startEpoch = dateToEpoch(2023, 3, 16);

    printEventsFromEpoch(events, startEpoch);

    return 0;
}
