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
	int room_num;
	friend class Hotel;

public:
	Person() {
		age = room_num = 0;
		name = "";
		citizen_id = "";
	}

};

class Hotel {
private:
	int room_num;
	int people_num;
	int days;
	bool n_rooms[N_ROOMS];

	std::vector<std::pair<int[2], Person>> guests; // int[2] for days and room_num

public:
	Hotel() {
		room_num = 0;
		people_num = 0;
		days = 0;

		for (int i = 0; i < N_ROOMS; ++i) n_rooms[i] = false;

	}
	void menu();
	void book();
	void list_of_guests();
	void room_info();
	void edit();
	void guest_info();

};


void Hotel::book() {
	system("cls");
	std::ofstream file("info.txt", std::ios::app);
	std::string name;
	std::string citizen_id;
	int age;
	
	if (file.is_open()) {
		std::cout << "Number of people: ";
		std::cin >> people_num;
		
		for (int i = 0; i < people_num; i++) {
			std::cout << "Name of guest: ";
			std::cin >> name;
			file << "NAME (" << i + 1 << "): " << name << std::endl;

			std::cout << "Citizen ID: ";
			std::cin >> citizen_id;
			file << "CITIZEN ID (" << i + 1 << "): " << citizen_id << std::endl;

			std::cout << "Age: ";
			std::cin >> age;
			file << "AGE (" << i + 1 << "): " << age << std::endl;

		}

		std::cout << "Days booked: ";
		std::cin >> days;
		file << "DAYS BOOKED: " << days << std::endl;

		do {
			std::cout << "Room number: ";
			std::cin >> room_num;
			if (n_rooms[room_num]) std::cout << "The room is not available!" << std::endl;
		} while (n_rooms[room_num]);

		file << "ROOM NUMBER: " << room_num << std::endl;

		n_rooms[room_num] = true;
		file << "---------------------------------------------------" << std::endl;
		file.close();
		std::cout << "Booking completed. Press any key to continue...\n" << std::endl;
	}
	else std::cout << "Unable to open file" << std::endl;

	

	if(_getch()) {} //ignore return value
}


void Hotel::list_of_guests() {
	std::string line;
	std::ifstream file("info.txt");
	std::pair<int[2], Person> temp;
	Person person;

	int days_of_room[] = { 0, 0 };

	if (file.is_open()) {
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
					
					n_rooms[days_of_room[1]] = true;
				}
				else {
					while (i < line.size()) {
						person.citizen_id.push_back(line[i]);
						i++;
					}
					
				}
				
			}
			
		}
		file.close();
	}
}



void Hotel::room_info() {
	// show guests info in one room
	system("cls");
	int room_number;
	std::cout << "\n\t\t\t\tEnter room number: ";
	std::cin >> room_number;
	
	for (int i = 0; i < guests.size(); i++) {
		if (room_number == guests[i].first[1]) {
			std::cout << "\n\t\t\t\tNAME:"  << guests[i].second.name << std::endl;
			std::cout << "\n\t\t\t\tCITIZEN_ID:"  << guests[i].second.citizen_id << std::endl;
			std::cout << "\n\t\t\t\tAGE:"  << guests[i].second.age << std::endl;
			std::cout << "\n\t\t\t\t---------------------------------" << std::endl;

		}
	}
	if (_getch()) {}
}


void Hotel::guest_info() {
	system("cls");

	std::string guest_name;
	std::cout << "\n\t\t\t\tEnter guest's name: ";
	std::cin >> guest_name;
	bool res = false;

	for (int i = 0; i < guests.size(); i++) {
		for (int j = 0; j < guests[i].second.name.size(); j++) {
			if (guests[i].second.name[j] == guest_name[0]) {
				
				int k = 0;
				int g = j;
				while (guests[i].second.name[g] == guest_name[k]) {
					k++; g++;
					
				}
				
				if (k == guest_name.size()) {
					res = true;
					std::cout << "\n\t\t\t\tNAME: " << guests[i].second.name << std::endl;
					std::cout << "\n\t\t\t\tCITIZEN_ID: " << guests[i].second.citizen_id << std::endl;
					std::cout << "\n\t\t\t\tAGE: " << guests[i].second.age << std::endl;
					std::cout << "\n\t\t\t\tROOM: " << guests[i].first[1] << std::endl;
					std::cout << "\n\t\t\t\t---------------------------------" << std::endl;
				}
			}
		}
	}
	if (res == false) std::cout << "\t\t\t\tNone matches your result!";

	if (_getch()) {}
}



void Hotel::edit() {}


void Hotel::menu() {
	while (true) {
		system("cls");
		list_of_guests();
		std::cout << "\n\t\t\t\t*************";
		std::cout << "\n\t\t\t\t* MAIN MENU *";
		std::cout << "\n\t\t\t\t*************";
		std::cout << "\n\n\n\t\t\t1. Book A Room";
		std::cout << "\n\t\t\t2. Guest's Information";
		std::cout << "\n\t\t\t3. Edit Record";
		std::cout << "\n\t\t\t4. Room's Information";
		std::cout << "\n\t\t\t5. Exit";
		std::cout << "\n\n\t\t\tEnter Your Choice: ";

		switch (_getch()) {
		case '1':
			book();
			break;
		case '2':
			guest_info();
			break;
		case '3':
			edit();
			break;
		case '4':
			room_info();
			break;
		case '5':
			exit(0);
		default:
			break;
		}
	}
}


