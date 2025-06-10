#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

// Abstract class Event
class Event {
protected:
    int startTime, endTime;
    double profit;
public:
    Event (int startTime, int endTime) : startTime(startTime), endTime(endTime) {}
    virtual void calculateProfit () = 0;
    // Getter functions
    double getProfit () { return profit; }
    int getEndTime() { return endTime; }
    int getStartTime() { return startTime; }
    // Overloaded stream extraction operator
    friend void operator >> (istream& stream, Event &E) {
        stream >> E.startTime >> E.endTime;
    }
};

// Inherited class Concert
class Concert : public Event{
    int TicketPrice, TicketsSold, ArtistFee, LogisticCost;
public:
    Concert(int startTime, int endTime, int TicketPrice, int TicketsSold, int ArtistFee, int LogisticCost) : Event(startTime, endTime), TicketPrice(TicketPrice), TicketsSold(TicketsSold), ArtistFee(ArtistFee), LogisticCost(LogisticCost) {
        calculateProfit();
    }
    void calculateProfit() override {
        double iprofit = 0.82 * TicketPrice * TicketsSold - (ArtistFee + LogisticCost);
        profit = iprofit > 2 * (ArtistFee + LogisticCost) ? 0.7 * iprofit : iprofit;
    }
};

// Inherited class TheatreShow
class TheatreShow : public Event{
    int BaseTicketPrice, TotalSeats, VenueCost;
public:
    TheatreShow(int startTime, int endTime, int BasePrice, int TotalSeats, int VenueCost) : Event(startTime, endTime),  BaseTicketPrice(BasePrice), TotalSeats(TotalSeats), VenueCost(VenueCost) {
        calculateProfit();
    }
    void calculateProfit() override {
        profit = 0.82 * 1.25 * TotalSeats * BaseTicketPrice + 37.5 * TotalSeats - VenueCost;
    }
};

// Inherited class Wedding
class Wedding : public Event{
    int BaseAmount, DecorationCost, GuestCount, VenueCost;
public:
    Wedding(int startTime, int endTime, int BaseAmount, int DecorationCost, int GuestCount, int VenueCost) : Event(startTime, endTime), BaseAmount(BaseAmount), DecorationCost(DecorationCost), GuestCount(GuestCount), VenueCost(VenueCost) {
        calculateProfit();
    }
    void calculateProfit() override {
        double TotalVenueCost, CateringCost;
        TotalVenueCost = (GuestCount > 200) ? VenueCost * 3 : VenueCost;
        CateringCost = (GuestCount > 100) ? GuestCount * 70 : GuestCount * 100;
        profit = BaseAmount - TotalVenueCost - DecorationCost - CateringCost;
    }
};

// Comparator functor for sorting the vector of events in EventScheduler
class comparator {
public:
    bool operator () (Event* A, Event* B) {
        return A->getEndTime() < B->getEndTime();
    }
};

class EventScheduler {
    vector<Event*> events;
public:
    // Add an event to the vector of events
    void addEvent (Event* E) {
        events.push_back(E);
    }
    double calculateNetProfit() {
        int n = events.size();
        // Sort the vector using the comparator
        sort(events.begin(), events.end(), comparator());
        vector<double> dp(n, -1); // Use a memoization vector to store previously computed return values of function calls
        vector<int> prev(n, -1); // This vector stores for each event, the greatest index of the previous events with endTime les than or equal to that of the startTime of the event in consideration
        // Use binary search to compute greatest non overlapping previous event of the current event
        for (int i = 0; i < n; i++) {
            int a = 0, b = i - 1;
            while (a <= b) {
                int mid = (a + b) / 2;
                if (events[mid]->getEndTime() <= events[i]->getStartTime() && events[mid + 1]->getEndTime() > events[i]->getStartTime()) {
                    prev[i] = mid;
                    break;
                } else if (events[mid]->getEndTime() > events[i]->getStartTime()) 
                    b = mid - 1;
                else
                    a = mid + 1;
            }
        }
        return calculateNetProfit(n - 1, dp, prev);
    }
    double calculateNetProfit(int i, vector<double> &dp, vector<int> &prev) {
        if (i < 0)
            return 0; // Base case when i < 0
        if (i == 0)
            return events[i]->getProfit(); // Base case when i == 0
        if (dp[i] != -1)
            return dp[i]; // When the value has already been computed by an earlier function call
        // Either we conduct the event or don't
        // When we conduct, all other events which overlap with the current event are not considered
        // When we don't, we can consider the maxprofit obtained until the immediately previous event
        return dp[i] = max(calculateNetProfit(i - 1, dp, prev), events[i]->getProfit() + calculateNetProfit(prev[i], dp, prev));
    }
};

int main () {
    EventScheduler eventscheduler;
    int n, type, start, end;
    cin >> n;
    for (int i = 0; i < n; i++) {
        Event* event; // Base pointer
        cin >> type;
        if (type == 1) {
            int TicketPrice, TicketsSold, ArtisteFee, LogisticCost;
            cin >> start >> end >> TicketPrice >> TicketsSold >> ArtisteFee >> LogisticCost;
            event = new Concert(start, end, TicketPrice, TicketsSold, ArtisteFee, LogisticCost); // Base pointer points to Concert class
        } else if (type == 2) {
            int BasePrice, TotalSeats, VenueCost;
            cin >> start >> end >> BasePrice >> TotalSeats >> VenueCost;
            event = new TheatreShow(start, end, BasePrice, TotalSeats, VenueCost); // // Base pointer points to TheatreShow class
        } else {
            int BaseAmount, DecorationCost, GuestCount, VenueCost;
            cin >> start >> end >> BaseAmount >> DecorationCost >> GuestCount >> VenueCost;
            event = new Wedding(start, end, BaseAmount, DecorationCost, GuestCount, VenueCost); // Base pointer points to Wedding class
        }
        eventscheduler.addEvent(event); // Add the event to the eventscheduler
    }
    cout << fixed << setprecision(2) << eventscheduler.calculateNetProfit() << "\n";
}
