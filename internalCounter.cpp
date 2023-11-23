//Place holder file no longer in use

/*#include <iostream>
#include <thread>
#include <chrono>
#include <future> 

using namespace std;

Timer::Timer() {
	this->start_time = steady_clock::now(); 
	this->is_4_minute_timer = true; 
	this->four_minutes = 240;
	this->ten_minutes = 600;
}
void Timer::start_10_minute_timer() {
	is_4_minute_timer = false;
	start_time = steady_clock::now();
}

void Timer::start_4_minute_timer() {
	this->is_4_minute_timer = true;
	this->start_time = steady_clock::now();
}

auto Timer::get_Start_Time() {
	return this->start_time;
}

seconds Timer::get_duration_4_minutes() {
	return this->four_minutes;
}
seconds Timer::get_duration_10_minutes() {
	return this->ten_minutes; 
}

bool Timer::get_is_4_minute_timer() {
	return this->is_4_minute_timer; 
}*/