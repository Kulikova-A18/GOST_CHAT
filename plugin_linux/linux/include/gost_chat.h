#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <ctime>
#include <time.h>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <stdio.h>
#include <clocale> 

#ifdef _WIN32
#include <Windows.h> 
#include <conio.h>
#endif

#include "json.hpp"

std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace);
void entrance_audit(std::string login, std::string password, std::string message);
void entrance_person_audit(int id, std::string surname, std::string name, std::string patronymic, std::string message);
std::string find_json(std::string _login, std::string _password);
int find(std::string argv1, std::string argv2);

int _cleaning_logger_linux();
const std::string currentDateTime();
int _logger_linux(char* argv1, char* argv2);
