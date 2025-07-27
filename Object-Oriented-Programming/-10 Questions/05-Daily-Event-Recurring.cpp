/*
==========================================
DAILY EVENT RECURRING SYSTEM QUESTION
==========================================

PROBLEM STATEMENT:
------------------
Create a comprehensive Daily Event Recurring System with the following requirements:

1. Base Class: Event (eventId, title, description, startTime, endTime, priority)
2. Derived Classes:
   - DailyEvent (recurrencePattern, lastOccurrence, nextOccurrence)
   - WeeklyEvent (dayOfWeek, weekInterval)
   - MonthlyEvent (dayOfMonth, monthInterval)
   - YearlyEvent (month, day, yearInterval)
3. EventScheduler Class: (events vector, currentDate)
4. Features:
   - Create different types of recurring events
   - Schedule and manage events
   - Calculate next occurrence dates
   - Handle event conflicts
   - Generate event reports
   - Export/Import event data

IMPLEMENTATION REQUIREMENTS:
- Use inheritance hierarchy with virtual functions
- Implement encapsulation with proper access modifiers
- Use constructors and destructors
- Implement static members for tracking
- Use friend functions for cross-class operations
- Implement operator overloading for comparisons
- Use templates for generic operations
- Handle exceptions for invalid operations
- Use smart pointers for memory management
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <stdexcept>
using namespace std;

// ==========================================
// EXCEPTION CLASSES
// ==========================================

class EventException : public exception {
private:
    string message;
public:
    EventException(string msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class SchedulerException : public exception {
private:
    string message;
public:
    SchedulerException(string msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// ==========================================
// DATE/TIME UTILITY CLASS
// ==========================================

class DateTime {
private:
    int year, month, day, hour, minute;

public:
    DateTime(int y = 2024, int m = 1, int d = 1, int h = 0, int min = 0)
        : year(y), month(m), day(d), hour(h), minute(min) {
        validate();
    }

    // Copy constructor
    DateTime(const DateTime& other)
        : year(other.year), month(other.month), day(other.day), 
          hour(other.hour), minute(other.minute) {}

    // Getters
    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
    int getHour() const { return hour; }
    int getMinute() const { return minute; }

    // Setters
    void setYear(int y) { year = y; validate(); }
    void setMonth(int m) { month = m; validate(); }
    void setDay(int d) { day = d; validate(); }
    void setHour(int h) { hour = h; validate(); }
    void setMinute(int m) { minute = m; validate(); }

    // Validation
    void validate() {
        if (year < 1900 || year > 2100) {
            throw EventException("Invalid year");
        }
        if (month < 1 || month > 12) {
            throw EventException("Invalid month");
        }
        if (day < 1 || day > 31) {
            throw EventException("Invalid day");
        }
        if (hour < 0 || hour > 23) {
            throw EventException("Invalid hour");
        }
        if (minute < 0 || minute > 59) {
            throw EventException("Invalid minute");
        }
    }

    // Add days
    DateTime addDays(int days) const {
        DateTime result = *this;
        result.day += days;
        
        // Simple day adjustment (not accounting for different month lengths)
        while (result.day > 31) {
            result.day -= 31;
            result.month++;
            if (result.month > 12) {
                result.month = 1;
                result.year++;
            }
        }
        
        return result;
    }

    // Add hours
    DateTime addHours(int hours) const {
        DateTime result = *this;
        result.hour += hours;
        
        while (result.hour >= 24) {
            result.hour -= 24;
            result = result.addDays(1);
        }
        
        return result;
    }

    // Add minutes
    DateTime addMinutes(int minutes) const {
        DateTime result = *this;
        result.minute += minutes;
        
        while (result.minute >= 60) {
            result.minute -= 60;
            result = result.addHours(1);
        }
        
        return result;
    }

    // Get day of week (0 = Sunday, 1 = Monday, ..., 6 = Saturday)
    int getDayOfWeek() const {
        // Simple calculation (not accounting for leap years properly)
        int days = day + (month - 1) * 31 + (year - 1900) * 365;
        return days % 7;
    }

    // Comparison operators
    bool operator==(const DateTime& other) const {
        return year == other.year && month == other.month && day == other.day &&
               hour == other.hour && minute == other.minute;
    }

    bool operator!=(const DateTime& other) const {
        return !(*this == other);
    }

    bool operator<(const DateTime& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        if (day != other.day) return day < other.day;
        if (hour != other.hour) return hour < other.hour;
        return minute < other.minute;
    }

    bool operator>(const DateTime& other) const {
        return other < *this;
    }

    bool operator<=(const DateTime& other) const {
        return !(other < *this);
    }

    bool operator>=(const DateTime& other) const {
        return !(*this < other);
    }

    // Display date/time
    void display() const {
        cout << setfill('0') << setw(4) << year << "-"
             << setw(2) << month << "-" << setw(2) << day << " "
             << setw(2) << hour << ":" << setw(2) << minute;
    }

    // Friend function for output
    friend ostream& operator<<(ostream& os, const DateTime& dt);
};

ostream& operator<<(ostream& os, const DateTime& dt) {
    os << setfill('0') << setw(4) << dt.year << "-"
       << setw(2) << dt.month << "-" << setw(2) << dt.day << " "
       << setw(2) << dt.hour << ":" << setw(2) << dt.minute;
    return os;
}

// ==========================================
// BASE CLASS: EVENT
// ==========================================

class Event {
protected:
    int eventId;
    string title;
    string description;
    DateTime startTime;
    DateTime endTime;
    int priority; // 1-10 scale
    static int eventCounter;

public:
    Event(string t, string desc, DateTime start, DateTime end, int p = 5)
        : title(t), description(desc), startTime(start), endTime(end), priority(p) {
        eventCounter++;
        eventId = eventCounter;
        
        if (priority < 1 || priority > 10) {
            throw EventException("Priority must be between 1 and 10");
        }
        
        if (startTime >= endTime) {
            throw EventException("Start time must be before end time");
        }
    }

    virtual ~Event() {
        eventCounter--;
    }

    // Virtual functions for polymorphism
    virtual void display() const {
        cout << "Event ID: " << eventId << endl;
        cout << "Title: " << title << endl;
        cout << "Description: " << description << endl;
        cout << "Start Time: ";
        startTime.display();
        cout << endl;
        cout << "End Time: ";
        endTime.display();
        cout << endl;
        cout << "Priority: " << priority << "/10" << endl;
    }

    virtual DateTime getNextOccurrence() const {
        return startTime; // Base class returns original start time
    }

    virtual bool isRecurring() const {
        return false; // Base class is not recurring
    }

    // Getters
    int getEventId() const { return eventId; }
    string getTitle() const { return title; }
    string getDescription() const { return description; }
    DateTime getStartTime() const { return startTime; }
    DateTime getEndTime() const { return endTime; }
    int getPriority() const { return priority; }

    // Setters
    void setTitle(string t) { title = t; }
    void setDescription(string desc) { description = desc; }
    void setStartTime(DateTime start) { 
        if (start >= endTime) {
            throw EventException("Start time must be before end time");
        }
        startTime = start; 
    }
    void setEndTime(DateTime end) { 
        if (startTime >= end) {
            throw EventException("End time must be after start time");
        }
        endTime = end; 
    }
    void setPriority(int p) { 
        if (p < 1 || p > 10) {
            throw EventException("Priority must be between 1 and 10");
        }
        priority = p; 
    }

    // Static function
    static int getEventCounter() { return eventCounter; }

    // Operator overloading
    bool operator==(const Event& other) const {
        return eventId == other.eventId;
    }

    bool operator!=(const Event& other) const {
        return !(*this == other);
    }

    bool operator<(const Event& other) const {
        return startTime < other.startTime;
    }

    bool operator>(const Event& other) const {
        return startTime > other.startTime;
    }

    // Friend function for output
    friend ostream& operator<<(ostream& os, const Event& event);
};

int Event::eventCounter = 0;

ostream& operator<<(ostream& os, const Event& event) {
    os << "Event[" << event.eventId << "]: " << event.title << " at " << event.startTime;
    return os;
}

// ==========================================
// DERIVED CLASS: DAILY EVENT
// ==========================================

class DailyEvent : public Event {
private:
    int recurrencePattern; // Days between occurrences
    DateTime lastOccurrence;
    DateTime nextOccurrence;

public:
    DailyEvent(string t, string desc, DateTime start, DateTime end, int pattern = 1, int p = 5)
        : Event(t, desc, start, end, p), recurrencePattern(pattern), 
          lastOccurrence(start), nextOccurrence(start) {
        if (pattern < 1) {
            throw EventException("Recurrence pattern must be at least 1 day");
        }
    }

    // Override display function
    void display() const override {
        Event::display();
        cout << "Type: Daily Recurring" << endl;
        cout << "Recurrence Pattern: Every " << recurrencePattern << " day(s)" << endl;
        cout << "Last Occurrence: ";
        lastOccurrence.display();
        cout << endl;
        cout << "Next Occurrence: ";
        nextOccurrence.display();
        cout << endl;
    }

    // Override get next occurrence
    DateTime getNextOccurrence() const override {
        return nextOccurrence;
    }

    // Override is recurring
    bool isRecurring() const override {
        return true;
    }

    // Update next occurrence
    void updateNextOccurrence() {
        lastOccurrence = nextOccurrence;
        nextOccurrence = nextOccurrence.addDays(recurrencePattern);
    }

    // Getters
    int getRecurrencePattern() const { return recurrencePattern; }
    DateTime getLastOccurrence() const { return lastOccurrence; }

    // Setters
    void setRecurrencePattern(int pattern) {
        if (pattern < 1) {
            throw EventException("Recurrence pattern must be at least 1 day");
        }
        recurrencePattern = pattern;
    }

    friend ostream& operator<<(ostream& os, const DailyEvent& event);
};

ostream& operator<<(ostream& os, const DailyEvent& event) {
    os << "DailyEvent[" << event.getEventId() << "]: " << event.getTitle() 
       << " (Every " << event.recurrencePattern << " days)";
    return os;
}

// ==========================================
// DERIVED CLASS: WEEKLY EVENT
// ==========================================

class WeeklyEvent : public Event {
private:
    int dayOfWeek; // 0 = Sunday, 1 = Monday, ..., 6 = Saturday
    int weekInterval; // Weeks between occurrences

public:
    WeeklyEvent(string t, string desc, DateTime start, DateTime end, int day, int interval = 1, int p = 5)
        : Event(t, desc, start, end, p), dayOfWeek(day), weekInterval(interval) {
        if (day < 0 || day > 6) {
            throw EventException("Day of week must be between 0 and 6");
        }
        if (interval < 1) {
            throw EventException("Week interval must be at least 1");
        }
    }

    // Override display function
    void display() const override {
        Event::display();
        cout << "Type: Weekly Recurring" << endl;
        string days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        cout << "Day of Week: " << days[dayOfWeek] << endl;
        cout << "Week Interval: Every " << weekInterval << " week(s)" << endl;
    }

    // Override get next occurrence
    DateTime getNextOccurrence() const override {
        DateTime current = startTime;
        int currentDay = current.getDayOfWeek();
        
        // Calculate days to add to reach the target day
        int daysToAdd = (dayOfWeek - currentDay + 7) % 7;
        if (daysToAdd == 0) daysToAdd = 7 * weekInterval;
        else daysToAdd += 7 * (weekInterval - 1);
        
        return current.addDays(daysToAdd);
    }

    // Override is recurring
    bool isRecurring() const override {
        return true;
    }

    // Getters
    int getDayOfWeek() const { return dayOfWeek; }
    int getWeekInterval() const { return weekInterval; }

    // Setters
    void setDayOfWeek(int day) {
        if (day < 0 || day > 6) {
            throw EventException("Day of week must be between 0 and 6");
        }
        dayOfWeek = day;
    }

    void setWeekInterval(int interval) {
        if (interval < 1) {
            throw EventException("Week interval must be at least 1");
        }
        weekInterval = interval;
    }

    friend ostream& operator<<(ostream& os, const WeeklyEvent& event);
};

ostream& operator<<(ostream& os, const WeeklyEvent& event) {
    string days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    os << "WeeklyEvent[" << event.getEventId() << "]: " << event.getTitle() 
       << " (Every " << event.weekInterval << " week(s) on " << days[event.dayOfWeek] << ")";
    return os;
}

// ==========================================
// DERIVED CLASS: MONTHLY EVENT
// ==========================================

class MonthlyEvent : public Event {
private:
    int dayOfMonth; // 1-31
    int monthInterval; // Months between occurrences

public:
    MonthlyEvent(string t, string desc, DateTime start, DateTime end, int day, int interval = 1, int p = 5)
        : Event(t, desc, start, end, p), dayOfMonth(day), monthInterval(interval) {
        if (day < 1 || day > 31) {
            throw EventException("Day of month must be between 1 and 31");
        }
        if (interval < 1) {
            throw EventException("Month interval must be at least 1");
        }
    }

    // Override display function
    void display() const override {
        Event::display();
        cout << "Type: Monthly Recurring" << endl;
        cout << "Day of Month: " << dayOfMonth << endl;
        cout << "Month Interval: Every " << monthInterval << " month(s)" << endl;
    }

    // Override get next occurrence
    DateTime getNextOccurrence() const override {
        DateTime current = startTime;
        DateTime next = current;
        
        // Simple calculation (not accounting for different month lengths)
        next.setMonth(current.getMonth() + monthInterval);
        if (next.getMonth() > 12) {
            next.setMonth(next.getMonth() - 12);
            next.setYear(next.getYear() + 1);
        }
        
        return next;
    }

    // Override is recurring
    bool isRecurring() const override {
        return true;
    }

    // Getters
    int getDayOfMonth() const { return dayOfMonth; }
    int getMonthInterval() const { return monthInterval; }

    // Setters
    void setDayOfMonth(int day) {
        if (day < 1 || day > 31) {
            throw EventException("Day of month must be between 1 and 31");
        }
        dayOfMonth = day;
    }

    void setMonthInterval(int interval) {
        if (interval < 1) {
            throw EventException("Month interval must be at least 1");
        }
        monthInterval = interval;
    }

    friend ostream& operator<<(ostream& os, const MonthlyEvent& event);
};

ostream& operator<<(ostream& os, const MonthlyEvent& event) {
    os << "MonthlyEvent[" << event.getEventId() << "]: " << event.getTitle() 
       << " (Every " << event.monthInterval << " month(s) on day " << event.dayOfMonth << ")";
    return os;
}

// ==========================================
// DERIVED CLASS: YEARLY EVENT
// ==========================================

class YearlyEvent : public Event {
private:
    int month; // 1-12
    int day; // 1-31
    int yearInterval; // Years between occurrences

public:
    YearlyEvent(string t, string desc, DateTime start, DateTime end, int m, int d, int interval = 1, int p = 5)
        : Event(t, desc, start, end, p), month(m), day(d), yearInterval(interval) {
        if (m < 1 || m > 12) {
            throw EventException("Month must be between 1 and 12");
        }
        if (d < 1 || d > 31) {
            throw EventException("Day must be between 1 and 31");
        }
        if (interval < 1) {
            throw EventException("Year interval must be at least 1");
        }
    }

    // Override display function
    void display() const override {
        Event::display();
        cout << "Type: Yearly Recurring" << endl;
        string months[] = {"", "January", "February", "March", "April", "May", "June",
                          "July", "August", "September", "October", "November", "December"};
        cout << "Date: " << months[month] << " " << day << endl;
        cout << "Year Interval: Every " << yearInterval << " year(s)" << endl;
    }

    // Override get next occurrence
    DateTime getNextOccurrence() const override {
        DateTime current = startTime;
        DateTime next = current;
        next.setYear(current.getYear() + yearInterval);
        return next;
    }

    // Override is recurring
    bool isRecurring() const override {
        return true;
    }

    // Getters
    int getMonth() const { return month; }
    int getDay() const { return day; }
    int getYearInterval() const { return yearInterval; }

    // Setters
    void setMonth(int m) {
        if (m < 1 || m > 12) {
            throw EventException("Month must be between 1 and 12");
        }
        month = m;
    }

    void setDay(int d) {
        if (d < 1 || d > 31) {
            throw EventException("Day must be between 1 and 31");
        }
        day = d;
    }

    void setYearInterval(int interval) {
        if (interval < 1) {
            throw EventException("Year interval must be at least 1");
        }
        yearInterval = interval;
    }

    friend ostream& operator<<(ostream& os, const YearlyEvent& event);
};

ostream& operator<<(ostream& os, const YearlyEvent& event) {
    string months[] = {"", "January", "February", "March", "April", "May", "June",
                      "July", "August", "September", "October", "November", "December"};
    os << "YearlyEvent[" << event.getEventId() << "]: " << event.getTitle() 
       << " (Every " << event.yearInterval << " year(s) on " << months[event.month] << " " << event.day << ")";
    return os;
}

// ==========================================
// EVENT SCHEDULER CLASS
// ==========================================

class EventScheduler {
private:
    vector<shared_ptr<Event>> events;
    DateTime currentDate;
    static int schedulerCounter;

public:
    EventScheduler(DateTime date = DateTime()) : currentDate(date) {
        schedulerCounter++;
    }

    ~EventScheduler() {
        schedulerCounter--;
    }

    // Add event
    void addEvent(shared_ptr<Event> event) {
        events.push_back(event);
    }

    // Remove event
    void removeEvent(int eventId) {
        auto it = find_if(events.begin(), events.end(),
            [eventId](const shared_ptr<Event>& e) { return e->getEventId() == eventId; });
        
        if (it != events.end()) {
            events.erase(it);
        } else {
            throw SchedulerException("Event not found");
        }
    }

    // Find event by ID
    shared_ptr<Event> findEvent(int eventId) {
        for (auto& event : events) {
            if (event->getEventId() == eventId) {
                return event;
            }
        }
        return nullptr;
    }

    // Find events by title
    vector<shared_ptr<Event>> findEventsByTitle(string title) {
        vector<shared_ptr<Event>> found;
        for (auto& event : events) {
            if (event->getTitle() == title) {
                found.push_back(event);
            }
        }
        return found;
    }

    // Get upcoming events
    vector<shared_ptr<Event>> getUpcomingEvents(int days = 7) {
        vector<shared_ptr<Event>> upcoming;
        DateTime futureDate = currentDate.addDays(days);
        
        for (auto& event : events) {
            DateTime nextOccurrence = event->getNextOccurrence();
            if (nextOccurrence >= currentDate && nextOccurrence <= futureDate) {
                upcoming.push_back(event);
            }
        }
        
        // Sort by start time
        sort(upcoming.begin(), upcoming.end(),
            [](const shared_ptr<Event>& a, const shared_ptr<Event>& b) {
                return a->getStartTime() < b->getStartTime();
            });
        
        return upcoming;
    }

    // Get recurring events
    vector<shared_ptr<Event>> getRecurringEvents() {
        vector<shared_ptr<Event>> recurring;
        for (auto& event : events) {
            if (event->isRecurring()) {
                recurring.push_back(event);
            }
        }
        return recurring;
    }

    // Check for conflicts
    vector<pair<shared_ptr<Event>, shared_ptr<Event>>> checkConflicts() {
        vector<pair<shared_ptr<Event>, shared_ptr<Event>>> conflicts;
        
        for (size_t i = 0; i < events.size(); i++) {
            for (size_t j = i + 1; j < events.size(); j++) {
                DateTime start1 = events[i]->getStartTime();
                DateTime end1 = events[i]->getEndTime();
                DateTime start2 = events[j]->getStartTime();
                DateTime end2 = events[j]->getEndTime();
                
                // Check for overlap
                if ((start1 < end2) && (start2 < end1)) {
                    conflicts.push_back({events[i], events[j]});
                }
            }
        }
        
        return conflicts;
    }

    // Display all events
    void displayAllEvents() const {
        cout << "\n=== ALL EVENTS ===" << endl;
        cout << "Current Date: ";
        currentDate.display();
        cout << endl;
        cout << "Total Events: " << events.size() << endl;
        cout << "================================" << endl;
        
        for (const auto& event : events) {
            event->display();
            cout << "------------------------" << endl;
        }
    }

    // Display upcoming events
    void displayUpcomingEvents(int days = 7) {
        cout << "\n=== UPCOMING EVENTS (Next " << days << " days) ===" << endl;
        vector<shared_ptr<Event>> upcoming = getUpcomingEvents(days);
        
        if (upcoming.empty()) {
            cout << "No upcoming events" << endl;
            return;
        }
        
        for (const auto& event : upcoming) {
            event->display();
            cout << "------------------------" << endl;
        }
    }

    // Display recurring events
    void displayRecurringEvents() {
        cout << "\n=== RECURRING EVENTS ===" << endl;
        vector<shared_ptr<Event>> recurring = getRecurringEvents();
        
        if (recurring.empty()) {
            cout << "No recurring events" << endl;
            return;
        }
        
        for (const auto& event : recurring) {
            event->display();
            cout << "------------------------" << endl;
        }
    }

    // Display conflicts
    void displayConflicts() {
        cout << "\n=== EVENT CONFLICTS ===" << endl;
        vector<pair<shared_ptr<Event>, shared_ptr<Event>>> conflicts = checkConflicts();
        
        if (conflicts.empty()) {
            cout << "No conflicts found" << endl;
            return;
        }
        
        for (const auto& conflict : conflicts) {
            cout << "Conflict between:" << endl;
            cout << "1. " << conflict.first->getTitle() << " (";
            conflict.first->getStartTime().display();
            cout << " - ";
            conflict.first->getEndTime().display();
            cout << ")" << endl;
            cout << "2. " << conflict.second->getTitle() << " (";
            conflict.second->getStartTime().display();
            cout << " - ";
            conflict.second->getEndTime().display();
            cout << ")" << endl;
            cout << "------------------------" << endl;
        }
    }

    // Generate statistics
    void generateStatistics() const {
        cout << "\n=== EVENT SCHEDULER STATISTICS ===" << endl;
        cout << "Total Events: " << events.size() << endl;
        
        int recurringCount = 0;
        int highPriorityCount = 0;
        int lowPriorityCount = 0;
        
        for (const auto& event : events) {
            if (event->isRecurring()) {
                recurringCount++;
            }
            if (event->getPriority() >= 8) {
                highPriorityCount++;
            }
            if (event->getPriority() <= 3) {
                lowPriorityCount++;
            }
        }
        
        cout << "Recurring Events: " << recurringCount << endl;
        cout << "High Priority Events (8-10): " << highPriorityCount << endl;
        cout << "Low Priority Events (1-3): " << lowPriorityCount << endl;
    }

    // Getters
    DateTime getCurrentDate() const { return currentDate; }
    int getEventCount() const { return events.size(); }

    // Setters
    void setCurrentDate(DateTime date) { currentDate = date; }

    // Static function
    static int getSchedulerCounter() { return schedulerCounter; }

    // Operator overloading
    EventScheduler& operator+=(shared_ptr<Event> event) {
        addEvent(event);
        return *this;
    }

    EventScheduler& operator-=(int eventId) {
        removeEvent(eventId);
        return *this;
    }

    // Friend function for output
    friend ostream& operator<<(ostream& os, const EventScheduler& scheduler);
};

int EventScheduler::schedulerCounter = 0;

ostream& operator<<(ostream& os, const EventScheduler& scheduler) {
    os << "EventScheduler: " << scheduler.events.size() << " events, Current Date: " << scheduler.currentDate;
    return os;
}

// ==========================================
// TEMPLATE CLASS FOR GENERIC OPERATIONS
// ==========================================

template<typename T>
class EventManager {
private:
    vector<shared_ptr<T>> items;

public:
    void addItem(shared_ptr<T> item) {
        items.push_back(item);
    }

    void removeItem(shared_ptr<T> item) {
        auto it = find(items.begin(), items.end(), item);
        if (it != items.end()) {
            items.erase(it);
        }
    }

    void displayAll() {
        for (const auto& item : items) {
            item->display();
            cout << "------------------------" << endl;
        }
    }

    int getCount() const { return items.size(); }
};

// ==========================================
// DEMONSTRATION FUNCTION
// ==========================================

void demonstrateEventScheduler() {
    cout << "DAILY EVENT RECURRING SYSTEM DEMONSTRATION" << endl;
    cout << "==========================================" << endl;

    EventScheduler scheduler(DateTime(2024, 1, 15, 9, 0));

    // Create different types of events
    auto dailyEvent = make_shared<DailyEvent>(
        "Daily Standup", "Team meeting", 
        DateTime(2024, 1, 15, 9, 0), DateTime(2024, 1, 15, 9, 30), 1, 8
    );

    auto weeklyEvent = make_shared<WeeklyEvent>(
        "Weekly Review", "Project review meeting", 
        DateTime(2024, 1, 15, 14, 0), DateTime(2024, 1, 15, 15, 0), 1, 1, 7
    );

    auto monthlyEvent = make_shared<MonthlyEvent>(
        "Monthly Report", "Generate monthly report", 
        DateTime(2024, 1, 15, 16, 0), DateTime(2024, 1, 15, 17, 0), 15, 1, 6
    );

    auto yearlyEvent = make_shared<YearlyEvent>(
        "Annual Review", "Annual performance review", 
        DateTime(2024, 1, 15, 10, 0), DateTime(2024, 1, 15, 12, 0), 1, 15, 1, 9
    );

    auto regularEvent = make_shared<Event>(
        "One-time Meeting", "Important client meeting", 
        DateTime(2024, 1, 16, 11, 0), DateTime(2024, 1, 16, 12, 0), 10
    );

    // Add events to scheduler
    scheduler += dailyEvent;
    scheduler += weeklyEvent;
    scheduler += monthlyEvent;
    scheduler += yearlyEvent;
    scheduler += regularEvent;

    // Display all events
    scheduler.displayAllEvents();

    // Display upcoming events
    scheduler.displayUpcomingEvents(30);

    // Display recurring events
    scheduler.displayRecurringEvents();

    // Display conflicts
    scheduler.displayConflicts();

    // Generate statistics
    scheduler.generateStatistics();

    // Demonstrate operator overloading
    cout << "\n=== OPERATOR OVERLOADING DEMONSTRATIONS ===" << endl;
    
    // Comparison operators
    if (*dailyEvent < *weeklyEvent) {
        cout << "Daily event is before weekly event" << endl;
    }
    
    if (*yearlyEvent > *monthlyEvent) {
        cout << "Yearly event is after monthly event" << endl;
    }
    
    // Assignment operators
    EventScheduler scheduler2 = scheduler;
    cout << "Copied scheduler: " << scheduler2 << endl;
}

// ==========================================
// TRICKY DRY RUN PROBLEMS
// ==========================================

/*
Problem 1: What will be the output?
class Event {
    static int count;
    int id;
public:
    Event() { id = ++count; cout << "Event" << id; }
    ~Event() { cout << "~Event" << id; }
};
int Event::count = 0;
int main() {
    Event e1, e2;
    { Event e3; }
    return 0;
}
Answer: Event1Event2Event3~Event3~Event2~Event1

Problem 2: What will be the output?
class DateTime {
    int day;
public:
    DateTime(int d = 1) : day(d) {}
    DateTime operator+(int days) {
        return DateTime(day + days + 1);
    }
    friend ostream& operator<<(ostream& os, const DateTime& dt) {
        return os << "Day" << dt.day;
    }
};
int main() {
    DateTime dt(5);
    cout << dt + 3;
    return 0;
}
Answer: Day9

Problem 3: What will be the output?
class Scheduler {
    int events;
public:
    Scheduler(int e = 0) : events(e) {}
    Scheduler operator+=(int e) {
        events += e + 1;
        return *this;
    }
    friend ostream& operator<<(ostream& os, const Scheduler& s) {
        return os << "Events:" << s.events;
    }
};
int main() {
    Scheduler s(5);
    s += 3;
    cout << s;
    return 0;
}
Answer: Events:9
*/

int main() {
    demonstrateEventScheduler();
    return 0;
} 