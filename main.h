#pragma once

#include <fstream>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <process.h>
#include <dos.h>

class Hotel {
private:
	int room_num;
	int people_num;
	std::string name;
	std::string citizen_id;
	int age;
	int days;

public:
	Hotel() {
		room_num = people_num = 0;
		name = "";
		citizen_id = "";
		age = 0;

	}
	void menu();
	void book();
	void customer_record();
	void booked_rooms();
	void edit();

};



void Hotel::book() {
	system("cls");
	std::ofstream file("info.txt", std::ios::app);

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
		std::cout << "Room number: ";
		std::cin >> room_num;
		file << "ROOM NUMBER: " << room_num << std::endl;


		file << "---------------------------------------------------" << std::endl;
		file.close();
	}
	
	
	else std::cout << "Unable to open file" << std::endl;
	if(_getch()) {} //ignore return value
}


void Hotel::customer_record() {
	system("cls");
	std::string line;
	std::ifstream file("info.txt");
	if (file.is_open()) {
		while (std::getline(file, line)) {
			age = 0;
			if (line[0] != '-') {

				int i = 0;
				while (line[i] != ':') i++;
				i += 2;
				std::string x;
				if (line[0] == 'A' && line[1] == 'G') {
					int k = 1;
					while (i < line.size()) {
						age = age * k + (int(line[i]) - '0');
						i++;
						k *= 10;
					}
					std::cout << age << std::endl;
				}
				else if (line[0] == 'N' && line[1] == 'A') {
					//name
				}
				else if (line[0] == 'D' && line[1] == 'A') {
					//days
				}
				else if (line[0] == 'R' && line[1] == 'O') {
					//room_number
				}
				else {
					while (i < line.size()) {
						x.push_back(line[i]);
						i++;
					}
					std::cout << x << std::endl;
				}
				
			}
			

		}
		file.close();
	}
	else std::cout << "Unable to open file" << std::endl;
	if (_getch()) {}
}



void Hotel::booked_rooms() {}

void Hotel::edit() {}


void Hotel::menu() {
	while (true) {
		system("cls");
		std::cout << "\n\t\t\t\t*************";
		std::cout << "\n\t\t\t\t* MAIN MENU *";
		std::cout << "\n\t\t\t\t*************";
		std::cout << "\n\n\n\t\t\t1.Book A Room";
		std::cout << "\n\t\t\t2.Customer Record";
		std::cout << "\n\t\t\t3.Rooms Allotted";
		std::cout << "\n\t\t\t4.Edit Record";
		std::cout << "\n\t\t\t5.Exit";
		std::cout << "\n\n\t\t\tEnter Your Choice: ";

		switch (_getch()) {
		case '1':
			book();
			break;
		case '2':
			customer_record();
			break;
		case '3':
			edit();
			break;
		case '4':
			booked_rooms();
			break;
		case '5':
			EXIT_SUCCESS;
		default:
			break;
		}
	}
}


