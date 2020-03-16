//
// Created by omer on 21/06/18.
//

#ifndef SEASIMULATOR_EXCEPTIONS_H
#define SEASIMULATOR_EXCEPTIONS_H

#include <exception>
using namespace std;

class WrongCommandException : public exception {
public: const char* what() const noexcept override {return "ERROR: Wrong command.";}
};

class WrongBoardSizeException : public exception {
public: const char* what() const noexcept override {return "ERROR: Wrong board size. (30<=size>6)";}
};

class UnsignedSizeExeption : public exception {
public: const char* what() const noexcept override {return "ERROR: Unsigned size.";}
};

class tooFewArgumentsException : public exception {
public: const char* what() const noexcept override {return "ERROR: Too few arguments.";}
};

class OpenFileException : public exception {
public: const char* what() const noexcept override {return "ERROR: Opening the specified file.";}
};

class WrongInputException : public exception {
public: const char* what() const noexcept override {return "ERROR: Wrong input.";}
};

class WrongSpeedException : public exception {
public: const char* what() const noexcept override {return "ERROR: Wrong speed.";}
};

class UnsignedCourseException : public exception {
public: const char* what() const noexcept override {return "ERROR: Wrong course. course has to be between 0 to 360";}
};

class WrongCruiserCommandException : public exception {
public: const char* what() const noexcept override {return "ERROR: Wrong cruiser command. only \"course\" or \"attack\" commands are valid.";}
};

class WrongPatrolBoatCommandException : public exception {
public: const char* what() const noexcept override {return "ERROR: Wrong patrol-boat command.";}
};

class WrongFreighterCommandException : public exception {
public: const char* what() const noexcept override {return "ERROR: Wrong freighter command.";}
};

class WrongPortNameException : public exception {
public: const char* what() const noexcept override {return "ERROR: Wrong port name.";}
};

class WrongShipNameException : public exception {
public: const char* what() const noexcept override {return "ERROR: Wrong ship name.";}
};

class NotEnoughContainersException : public exception {
public: const char* what() const noexcept override {return "ERROR: You asked to unload more containers than the ship have. maximum containers unloaded.";}
};

class LoadAndUnloadException : public exception {
public: const char* what() const noexcept override {return "ERROR: Can't use the same port for load and also unload containers.";}
};

class DockAtPortException : public exception {
public: const char* what() const noexcept override {return "ERROR: Can't dock at this port. distance is to big. you can set your destination to this port.";}
};


class AttackCruiserException : public exception {
public: const char* what() const noexcept override {return "ERROR: Cruiser cannot attack another cruiser.";}
};

class AttackTooFarException : public exception {
public: const char* what() const noexcept override {return "ERROR: Cannot attack. ship is too far.";}
};

class ShipAlreadyExistException : public exception {
public: const char* what() const noexcept override {return "ERROR: Ship name already exist. Please choose another name.";}
};

class WrongShipDetailsException : public exception {
public: const char* what() const noexcept override {return "ERROR: some of your ship details are incorect. Please check it and try again.";}
};


#endif //SEASIMULATOR_EXCEPTIONS_H
