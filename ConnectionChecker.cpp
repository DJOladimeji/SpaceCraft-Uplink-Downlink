//Place holder file no longer in use

/*#include "out/ConnectionChecker.h"
//#include "internalCounter.h" // Include the header where internalCounter is defined

int checkConnection(bool &is_4_minute_timer, auto &start_time, string from) { 
	seconds four_minutes(240);
	seconds ten_minutes(600);
	auto current_time = steady_clock::now();     
	auto elaspased_time = duration_cast<seconds>(current_time - start_time);

	if (is_4_minute_timer == true && elaspased_time >= four_minutes) {
		is_4_minute_timer = false;
		start_time = steady_clock::now();

		cout << endl;
		cout << "====================================" << endl;
		cout << "4 minutes timer is up, switching to 10 minutes timer" << endl;
		cout << "No connection with the " << from << endl;
		cout << "====================================" << endl;
		cout << endl;

		return 0;
	}

	else if (is_4_minute_timer == false && elaspased_time >= ten_minutes) {
		is_4_minute_timer = true; 
		start_time = steady_clock::now();

		cout << endl;
		cout << "====================================" << endl;
		cout << "10 minute timer expired, switching to 4 minutes" << endl;
		cout << "====================================" << endl;
		cout << endl;

		return 1;
	}

	else if (is_4_minute_timer == true && elaspased_time <= four_minutes) {

		cout << endl;
		cout << "====================================" << endl;
		cout << "Recieved messages from " << from << endl;
		cout << "====================================" << endl;
		cout << endl;

		return 2;
	}

	else if (is_4_minute_timer == false && elaspased_time <= ten_minutes) {

		cout << endl;
		cout << "====================================" << endl;
		cout << "Recieved messages from " << from << endl; 
		cout << "====================================" << endl;
		cout << endl;

		cout << endl;
		cout << "====================================" << endl;
		cout << "No connection with ground in 10 minute section" << endl;
		cout << "====================================" << endl;
		cout << endl;

		return 3;
	}

	else {
		cout << endl;
		cout << "====================================" << endl;
		cout << "Error in checking timer" << endl;
		cout << "====================================" << endl;
		cout << endl;

		return 4;
	}
}*/