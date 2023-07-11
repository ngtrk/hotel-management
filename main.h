#include <fstream>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <process.h>
#include <dos.h>
#include <vector>


#define N_ROOMS 100

class Person {
private:
	std::string name;
	std::string citizen_id;
	int age;

	friend class Hotel;

public:
	Person() {
		age = 0;
		name = "";
		citizen_id = "";
	}

};

class Hotel {
private:
	int days;
	int n_rooms[N_ROOMS];

	std::vector<std::pair<int[2], Person>> guests; // int[2] for days and room_num

public:
	Hotel() {
		days = 0;

		for (int i = 0; i < N_ROOMS; ++i) n_rooms[i] = 0;

	}


	void menu();
	void book();
	void list_of_guests();
	void room_info();
	void remove_room();
	void guest_info();
	void save_info();
	void edit_info();

};




void Hotel::save_info() {
	std::ofstream file("temp.txt");
	if (file.is_open()) {
		for (int i = 0; i < guests.size(); i++) {
			file << "NAME: " << guests[i].second.name << std::endl;
			file << "CITIZEN ID: " << guests[i].second.citizen_id << std::endl;
			file << "AGE: " << guests[i].second.age << std::endl;
			file << "DAYS BOOKED: " << guests[i].first[0] << std::endl;
			file << "ROOM NUMBER: " << guests[i].first[1] << std::endl;
			file << "---------------------------------------------------" << std::endl;
		}
		
		file.close();
	}
	else std::cout << "\n\t\t\t\t Unable to open file" << std::endl;


	remove("info.txt");
	if (rename("temp.txt", "info.txt")) {}
}



void Hotel::book() {
	system("cls");
	std::ofstream file("info.txt", std::ios::app);

	std::pair<int[2], Person> temp;
	
	if (file.is_open()) {

		std::cout << "\n\t\t\t\t Days booked: ";
		std::cin >> temp.first[0];
		
		int room_num;
		do {
			std::cout << "\n\t\t\t\t Room number: ";
			std::cin >> room_num;
			if (n_rooms[room_num - 1] > 0) std::cout << "\n\t\t\t\t The room is not available." << std::endl;
			else if (1 > room_num || room_num >= 101) std::cout << "\n\t\t\t\t The room is not correct." << std::endl;
		} while (1 > room_num || room_num >= 101 || n_rooms[room_num - 1] > 0);


		temp.first[1] = room_num;

		int people_num;
		std::cout << "\n\t\t\t\t Number of people: ";
		std::cin >> people_num;
		
		for (int i = 0; i < people_num; i++) {
			std::cout << "\n\t\t\t\t Name of guest: ";
			std::cin >> temp.second.name;
			

			std::cout << "\n\t\t\t\t Citizen ID: ";
			std::cin >> temp.second.citizen_id;
			

			std::cout << "\n\t\t\t\t Age: ";
			std::cin >> temp.second.age;


			file << "NAME: " << temp.second.name << std::endl;
			file << "CITIZEN ID: " << temp.second.citizen_id << std::endl;
			file << "AGE: " << temp.second.age << std::endl;
			file << "DAYS BOOKED: " << temp.first[0] << std::endl;
			file << "ROOM NUMBER: " << room_num << std::endl;
			file << "---------------------------------------------------" << std::endl;
			
			guests.push_back(temp);
			
		}

		n_rooms[room_num - 1] += people_num;
		file.close();


		std::cout << "\n\t\t\t\t Booking completed. Press any key to continue...\n" << std::endl;
	}
	else std::cout << "\n\t\t\t\t Unable to open file" << std::endl;


	if (_getch()) {} //ignore return value
}



void Hotel::list_of_guests() {
	std::string line;
	std::ifstream file("info.txt");
	std::pair<int[2], Person> temp;
	Person person;

	int days_of_room[] = { 0, 0 };


	if (file.is_open()) {
		if (file.peek() != std::ifstream::traits_type::eof()) {
			while (std::getline(file, line)) {

				if (line[0] == '-') {
					temp.first[0] = days_of_room[0];
					temp.first[1] = days_of_room[1];
					temp.second = person;

					guests.push_back(temp);
					person = Person();
					days_of_room[0] = days_of_room[1] = 0;


				}
				else {

					int i = 0;
					while (line[i] != ':') i++;
					i += 2;

					if (line[0] == 'A' && line[1] == 'G') {
						int k = 1;
						while (i < line.size()) {

							person.age = person.age * k + (int(line[i]) - '0');
							i++;
							k *= 10;
						}

					}
					else if (line[0] == 'N' && line[1] == 'A') {
						while (i < line.size()) {
							person.name.push_back(line[i]);
							i++;
						}

					}
					else if (line[0] == 'D' && line[1] == 'A') {
						int k = 1;
						while (i < line.size()) {
							days_of_room[0] = days_of_room[0] * k + (int(line[i]) - '0');
							i++;
							k *= 10;
						}

					}
					else if (line[0] == 'R' && line[1] == 'O') {
						int k = 1;
						while (i < line.size()) {
							days_of_room[1] = days_of_room[1] * k + (int(line[i]) - '0');
							i++;
							k *= 10;
						}


						if (0 <= days_of_room[1] - 1 && days_of_room[1] - 1 < 100) n_rooms[days_of_room[1] - 1] += 1;
					}
					else {
						while (i < line.size()) {
							person.citizen_id.push_back(line[i]);
							i++;
						}

					}

				}

			}
		}
		file.close();
	}
}



void Hotel::room_info() {
	int room_number;

	do {
		system("cls");
		std::cout << "\n\t\t\t\t Enter room number: ";
		std::cin >> room_number;

		if (1 > room_number || room_number >= 101) std::cout << "\n\t\t\t\t The room is not found!" << std::endl;
	} while (1 > room_number || room_number >= 101);

	if (n_rooms[room_number - 1] > 0) {
		for (int i = 0; i < guests.size(); i++) {
			if (room_number == guests[i].first[1]) {
				std::cout << "\n\t\t\t\t NAME: " << guests[i].second.name << std::endl;
				std::cout << "\n\t\t\t\t CITIZEN_ID: " << guests[i].second.citizen_id << std::endl;
				std::cout << "\n\t\t\t\t AGE: " << guests[i].second.age << std::endl;
				std::cout << "\n\t\t\t\t ---------------------------------" << std::endl;

			}
		}
	}
	else std::cout << "\n\t\t\t\t The room is empty." << std::endl;
	
	if (_getch()) {}
}



void Hotel::guest_info() {
	system("cls");

	std::string guest_name;
	std::cout << "\n\t\t\t\t Enter guest's name: ";
	std::cin >> guest_name;
	bool res = false;

	for (int i = 0; i < guests.size(); i++) {

		for (int j = 0; j < guests[i].second.name.size(); j++) {

			if (guests[i].second.name[j] == guest_name[0]) {
				int k = 0;
				int g = j;
				
				while (k < guest_name.size() && g < guests[i].second.name.size() && guests[i].second.name[g] == guest_name[k]) {
					k++; g++;	
				}
				
				if (k == guest_name.size()) {
					res = true;

					std::cout << "\n\t\t\t\t NAME: " << guests[i].second.name << std::endl;
					std::cout << "\t\t\t\t CITIZEN_ID: " << guests[i].second.citizen_id << std::endl;
					std::cout << "\t\t\t\t AGE: " << guests[i].second.age << std::endl;
					std::cout << "\t\t\t\t ROOM: " << guests[i].first[1] << std::endl;
					std::cout << "\t\t\t\t ---------------------------------" << std::endl;
					break;
				}

			}
		}
	}
	if (!res) std::cout << "\n\n\t\t\t\t None matches your result!";

	if (_getch()) {}
}



void Hotel::remove_room() {	
	int room_number;

	do {
		system("cls");
		std::cout << "\n\t\t\t\t Enter room number: ";
		std::cin >> room_number;

		if (1 > room_number || room_number >= 101) std::cout << "\n\t\t\t\t The room is not found!" << std::endl;
	} while (1 > room_number || room_number >= 101);

	
	if (n_rooms[room_number - 1] > 0) {
		for (int i = 0; i < guests.size(); i++) {
			if (room_number == guests[i].first[1]) {
				std::iter_swap(guests.begin() + i, guests.end()-1);
				guests.pop_back();
				n_rooms[room_number - 1] -= 1;
				
			}
		}
	}

	else std::cout << "\n\t\t\t\t The room is empty." << std::endl;

	save_info();

	std::cout << "\n\t\t\t\t Remove room complete..." << std::endl;

	if (_getch()) {}

}


void Hotel::edit_info() {
	int room_number;
	do {
		system("cls");
		std::cout << "\n\t\t\t\t Enter room number: ";
		std::cin >> room_number;

		if (1 > room_number || room_number >= 101) std::cout << "\n\t\t\t\t The room is not found." << std::endl;
		else if (n_rooms[room_number - 1] == 0) std::cout << "\n\t\t\t\t The room is empty." << std::endl;
	} while (1 > room_number || room_number >= 101 || n_rooms[room_number - 1] == 0);

	std::vector<int> find_rooms;

	for (int i = 0; i < guests.size(); i++) {
		if (room_number == guests[i].first[1]) {
			find_rooms.push_back(i);
			if (find_rooms.size() == n_rooms[room_number - 1]) break;

		}
	}


	int n = -1;

	if (find_rooms.size() > 1) {
		for (int i = 0; i < find_rooms.size(); i++) {
			std::cout << "\n\t\t\t\t ***NUMBER: " << i + 1 << std::endl;
			std::cout << "\t\t\t\t NAME: " << guests[find_rooms[i]].second.name << std::endl;
			std::cout << "\t\t\t\t CITIZEN_ID: " << guests[find_rooms[i]].second.citizen_id << std::endl;
			std::cout << "\t\t\t\t AGE: " << guests[find_rooms[i]].second.age << std::endl;
			std::cout << "\t\t\t\t ROOM: " << guests[find_rooms[i]].first[1] << std::endl;
			std::cout << "\t\t\t\t ---------------------------------" << std::endl;
		}

		
		do {
			std::cout << "\n\t\t\t\t Enter guest's number to edit info: ";
			std::cin >> n;
		} while (0 >= n || n > find_rooms.size());
	}
	

	system("cls");

	std::cout << "\n\t\t\t\t ***** CURRENT INFO *****" << std::endl;
	std::cout << "\t\t\t\t NAME: " << guests[find_rooms[n - 1]].second.name << std::endl;
	std::cout << "\t\t\t\t CITIZEN_ID: " << guests[find_rooms[n - 1]].second.citizen_id << std::endl;
	std::cout << "\t\t\t\t AGE: " << guests[find_rooms[n - 1]].second.age << std::endl;
	std::cout << "\t\t\t\t ROOM: " << guests[find_rooms[n - 1]].first[1] << std::endl;
	
	std::cout << "\n\t\t\t\t ***** NEW INFO *****" << std::endl;
	std::cout << "\t\t\t\t NAME: ";
	std::cin >> guests[find_rooms[n - 1]].second.name;

	std::cout << "\t\t\t\t CITIZEN_ID: ";
	std::cin >> guests[find_rooms[n - 1]].second.citizen_id;

	std::cout << "\t\t\t\t AGE: ";
	std::cin >> guests[find_rooms[n - 1]].second.age;

	int new_room;
	std::cout << "\t\t\t\t ROOM: ";
	std::cin >> new_room;

	int new_days;

	std::cout << "\t\t\t\t DAYS: ";
	std::cin >> new_days;

	if (new_room != guests[find_rooms[n - 1]].first[1]) {
		n_rooms[guests[find_rooms[n - 1]].first[1] - 1] -= 1;
		
		guests[find_rooms[n - 1]].first[1] = new_room;
		
		n_rooms[new_room - 1] += 1;
		
		for (int i = 0; i < guests.size(); i++) {
			if (guests[i].first[1] == new_room)
				guests[i].first[0] = new_days;
		}
		
		guests[find_rooms[n - 1]].first[0] = new_days;

	}
	else {

		for (int i = 0; i < find_rooms.size(); i++) {
			guests[find_rooms[i]].first[0] = new_days;
		}
	}


	save_info();

	std::cout << "\n\t\t\t\t Editing info complete..." << std::endl;
	if (_getch()) {}
}


void Hotel::menu() {
	list_of_guests();

	while (true) {
		system("cls");

		std::cout << "\n\t\t\t\t *************";
		std::cout << "\n\t\t\t\t * MAIN MENU *";
		std::cout << "\n\t\t\t\t *************";
		std::cout << "\n\n\n\t\t\t 1. Book A Room";
		std::cout << "\n\t\t\t 2. Guest's Information";
		std::cout << "\n\t\t\t 3. Remove Room";
		std::cout << "\n\t\t\t 4. Room's Information";
		std::cout << "\n\t\t\t 5. Edit Information";
		std::cout << "\n\t\t\t 6. Exit";
		std::cout << "\n\n\t\t\t Enter Your Choice: ";

		switch (_getch()) {
		case '1':
			book();
			break;
		case '2':
			guest_info();
			break;
		case '3':
			remove_room();
			break;
		case '4':
			room_info();
			break;
		case '5':
			edit_info();
			break;
		case '6':
			exit(0);
		default:
			break;
		}
	}
}


